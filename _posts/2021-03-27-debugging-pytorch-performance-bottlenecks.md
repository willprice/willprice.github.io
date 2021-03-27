---
layout: post
title: "Diagnosing and Debugging PyTorch Data Starvation"
mathjax: yes
---

One of the things I repeatedly see with new-comers to PyTorch, or computer vision
in general, is a lack of awareness of how they can improve the performance of
their code. In video understanding, my field, this is a particularly thorny
issue as video is so computationally demanding to work with. Surprisingly often
we are not bottle-necked by our GPUs, but instead by our ability to feed those
GPU with data when training models. This is known as *data starvation*.
This blog post will cover a simple and quick method to diagnose whether this is
a problem you suffer from, and if so how you can address it through a variety of
techniques.


## Am I suffering from data starvation?
Determining whether you suffer from data starvation is actually pretty easy, you
can just watch the output of `nvidia-smi` whilst your code is running.
If you find your GPUs' utilisation drop to 0% for a short period of time and
then jump back up to their previous levels then data starvation is likely.
This test tells us is whether or not there is a period of time spent where the
GPUs are not running anything, and this most often is caused by data starvation,
although not always.
So let's say that you do observe these periodic drops to 0% utilisation, what
now? How can we tell where the issue lies? There are two potential causes of
this behaviour:

1. Doing time-consuming work in your training loop that is blocking and doesn't
   run on the GPU (e.g. CPU intensive processing, network operations).
2. Waiting on a batch of data.

Most training loops look something like this:

```python
for data, target in dataloader:
    data = data.to(device)
    target = target.to(device)
    optimizer.zero_grad()

    y_hat = model(x)
    loss = loss_fn(y_hat, y)
    loss.backward()
    optimizer.step()

    # log some stuff with tensorboard
    ...
```

If the time it takes to go from the bottom of the loop to the first line takes
more than a negligible amount of time, then we're suffering from data starvation.
Adding some timers in allows us to quantify this:

```python
from time import time
end = time()
for data, target in dataloader:
    data_loading_duration_ms = (time() - end) * 1e3

    torch.cuda.synchronize()
    pre_forward_time = time()
    data = data.to(device)
    target = target.to(device)
    optimizer.zero_grad()

    y_hat = model(x)
    loss = loss_fn(y_hat, y)
    torch.cuda.synchronize()
    post_forward_time = time()

    loss.backward()
    torch.cuda.synchronize()
    post_backward_time = time()
    optimizer.step()

    # log some stuff with tensorboard
    ...
    forward_duration_ms = (post_forward_time - pre_forward_time) * 1e3
    backward_duration_ms = (post_backward_time - post_forward_time) * 1e3
    print("forward time (ms) {:.2f} | backward time (ms) {:.2f} | dataloader time (ms) {:.2f}".format(
        forward_duration_ms, backward_duration_ms, data_loading_duration_ms
    ))
    end = time()
```

You have to be a bit careful when measuring time in PyTorch programs as most
PyTorch operations are non-blocking, that is they schedule the work and return
immediately, this allows more efficient scheduling of CUDA kernels. However, it
also means that your timing isn't going to be accurate. You can either sprinkle
your code with `torch.cuda.synchronize()` calls which act as a barrier and will
block until all previous kernel invocations have completed. Alternatively, you
can drop the `torch.cuda.synchronize()` statements and set the environment
variable `CUDA_LAUNCH_BLOCKING=1` when you run your code. This makes all previously
non-blocking calls blocking.

What you want to see once you've augmented your code with this timing
information is that the time spent loading data is tiny compared to the time
spent doing forward or backward passes. You should also remove the
`torch.cuda.synchronize()` calls once you've finished profiling--ops are
asynchronous by default for a reason, they allow better overlapping of
host/device computation.

What you'll typically observe is the dataloader duration will be ~0s for several
batches of data, then for one batch it will block and take seconds to load. This
is down to the use of workers for dataloading. If you have more workers than
your batch size, those workers will be busy loading a sufficient number of
examples for *multiple* batches. It looks as if the first batch takes ages to
load, but in fact we're loading enough data for multiple batches, hence why the
subsequent batches look as if they take 0s to load, that's because the data was
already retrieved previously.

## Mitigating data starvation

There are two approaches for solving your data starvation problem: throw more
resources at it, or make better use of what you have. We'll first cover the
former approach in *Scaling dataloading* as these knobs are easy to twiddle and
you want to make sure you're fully utilising the resources you have available
(quite often people aren't). The second topic we'll dive into more depth, this
approach typically requires code changes and knowledge of the systems you'll be
running on, what hardware they have and their performance characteristics as
well as thinking about your data and what representation is most suitable for
training.

### Scaling dataloading

PyTorch was designed to hide the cost of data loading through the [`DataLoader`
class](https://pytorch.org/docs/stable/data.html#torch.utils.data.DataLoader)
which spins up a number of worker processes, each of which is tasked with 
loading a single element of data.

This class has a bunch of arguments that will have an impact on dataloading
performance. I've ordered these from most important to least:

* `num_workers`: The number of worker processes that you fork to load data. Each
  one of these processes is tasked with loading a single data item from your
  dataset class. The rule of thumb is to push this up as high as you can without
  1. Overloading your CPU: watch `htop` in a terminal whilst running your code
     and stop increasing the number of workers once all your cores are at 100%
     utilisation (or your GPUs are no longer starved). One thing to watch out
     for is if a lot of the CPU core utilisation bars are red, this means that
     the cores are waiting on a syscall, this is typically a `read` from a
     storage device (getting the bytes of an HDD or SSD into memory), in which
     case you're bottlenecked by your ability to read data rather than
     processing it (e.g. decoding/augmentation).
  2. Running out of RAM: For large data items (e.g. video) it can be quite easy
     to fill up all your RAM. `htop` is your friend again here. Keep increasing
     the number of workers until you're close to the limit of how much RAM you
     have (or your GPUs are no longer starved).
* `batch_size`: the smaller the batch size, the fewer the examples needed to be
  loaded for each forward pass. Obvious, but worth mentioning nonetheless.
* `shuffle`: if you're loading data from an HDD then reading non-contiguous
  blocks of data is costly. Shuffling causes non-contiguous reads and therefore
  will slow dataloading down. You can mitigate this to some extent through
  clever engineering of your dataloading pipeline. The key trick is to chop up
  your dataset into blocks and only randomly shuffle the blocks rather than all
  the data items. That way you get the benefit of some randomness in the order
  of training examples, but try to mitigate the number of non-sequential reads
  you're doing. If you're using SSDs then shuffling typically doesn't matter.
* `pin_memory`: this flag determines whether or not to use page-locked host memory
  for transferring tensors from the CPU to the GPU. Page-locked memory tends to
  improve performance as it prevents the memory page on the host from being
  paged out to swap (which would make things much slower, as the page would have
  to be restored from swap to later transfer data). It also facilitates concurrent
  execution of kernels and memory transfer. Check out the page-locked host
  memory section in [this blog](https://jhui.github.io/2017/03/06/CUDA/) for
  more technical details.
* `persistent_workers`: Each epoch PyTorch will tear down your dataset object and
  recreate it. This can actually be very expensive if your dataset class does a
  lot of set up (e.g. reads big JSON files) and your epochs are short. This flag
  disables this behaviour and keeps your dataset object around across multiple
  epochs.


### Making better use of hardware

Know your hardware. Does your system have HDDs/SSDs (SATA/NVMe?)? Are you stuck
with no node-local storage? How much RAM does your system have?
When you couple this system knowledge with knowledge of your use case (e.g. I have
50GB of JPEGs/250GB of h264 MP4) you can make a pretty good guess what
configuration will eek the highest performance from the hardware available.
All you really need to remember is that RAM > NVMe SSD > SATA SSD > HDD >
Networked file storage (there are exceptions to this when you're loading a large
blob of data, but most ML workloads have nasty random access patterns where this
hierarchy holds true).
Let's consider the use case of training a model on a set of images, say 50GB of
them.
If you've got enough RAM such that you can copy your dataset into memory and
also have enough space left over to decompress your dataset and perform
augmentations then do this! Copy your data over to `/dev/shm` and point your
training script to it. `/dev/shm` is a directory in linux exposing RAM through
the filesystem, when you copy data to that directory becomes resident in
RAM.

In most cases you can't fit your entire dataset into RAM leaving enough over to
decompress examples and do data augmentation. The next best step is to have your
dataset on an SSD (preferably NVMe). If you're on an HPC system, get an
interative session and run `df` to see what block devices are available on
compute nodes and have a look into `/sys/block/` to find out more about the
devices available to you (e.g.  `/sys/block/X/queue/rotational` tells you
whether the device is an HDD or SSD).

Your hands start getting tied when you're loading from HDDs or networked file
storage. You have to start getting quite clever with your data storage and
access patterns. HDDs have a spinning disk, it takes time to move the read head
in an HDD so you want to minimizing head movement as much as possible. One
approach you can take is to chunk your dataset into groups of data elements that
you lay out sequentially on disk and then you randomise the order of those
groups each epoch. This gives you the most of the benefits of random data
ordering but without the (very) high costs of random access. A similar approach
should be taken for a networked filesystem, try put data in as large a blocks as
you can.  An example of library doing this is GulpIO. It is designed for image
and video and stores images/frames as a contiguous sequence of compressed JPEGs
in blocks known as `GulpChunk`s.  The cost of the code changes and time spent
engineering at this level is extremely painful. I would suggest throwing money
at the problem if at all possible... SSDs aren't expensive yet bring a world of
benefit.

One pattern I've seen successfully employed where there has been a high
performance networked filesystem and sufficient RAM to hold the dataset in
memory, is to combine all the data files into an uncompressed zip and write your
dataset class to access data elements from the ZIP file. Do not use a tar file as their
random access cost is $$\mathcal{O}(n)$$ in the length of the tar file (go check
out the [wiki article on
tar](https://en.wikipedia.org/wiki/Tar_(computing)#Random_access) to understand why!).

Before wrapping up this section, we should briefly discuss the overhead of
filesystem calls like `open` and `read`, these syscalls aren't free and when
you're loading thousands of images a second they can add up. I often see people
dumping video frames into a single folder. If you're using filesystems like
EXT3/4 this can incur quite substantial overheads. Consider using a lightweight
database like [`lmdb`](https://symas.com/lmdb/) to store `(id, binary blob)`
pairs.



### Making wiser choices in your code

We've discussed tweaking PyTorch's dataloader to make the most of the CPU and
memory available, we've looked at how you should leverage the storage hardware
available to you. If those two things haven't brought you far enough in
mitigating data starvation, then it's time to look at your code. This is going
to be very domain specific. I'm making the decision to ignore everything but
image and video as these are the two representations I work with and have a lot
of experience solving data starvation problems for. They are also typically some
of the most computationally expensive data that is commonly used in ML.

What format do you store your media in? Is it something lossless like PNG or
TIFF? Do you really need the precision these formats afford? Can you use JPEG
instead? JPEG has the benefit of years and years work in producing highly
optimised decoders (e.g. libjpegturbo).
If you work with video, one of the main determinants of which storage format you
should use are your access patterns. If you sparsely sample frames then this
puts you into a similar regime as working with images (totally unpredictable
access patterns). If instead you work with clips of video, then your access
patterns are not quite as random, you'll be doing sequential reads of contiguous
frames.  For video the storage decision is not clear cut and you should
benchmark the options on your hardware

#### Images

Use JPEG. Don't use PNG. The JPEG compression rate is much higher and therefore
images take up a lot less space (and so are quicker to load off storage into
RAM) and we have fast decoders for JPEG (libjpeg-turbo and nvJPEG).

Loading, decoding and, augmenting on the CPU is still the norm (although [DALI](https://docs.nvidia.com/deeplearning/dali/user-guide/docs/) is
helping to push people towards doing some of this stuff on the GPU, and
torchvision looks set to go that way---they've been implementing their
transforms in torchscript so that they can run on the GPU). In this space the
main players loading JPEGs are `Pillow`, `Pillow-SIMD`, `opencv`, `accimage`.
Pretty much all these libraries also implement transformations as well, but just
because you use one library for loading, doesn't mean you have to use the same
one for transformations. `Pillow` is a no go, it's far too slow out of the box,
you should at least build it with libjpeg-turbo. Even then it's a bad choice
when `Pillow-SIMD` exists, a fork of `Pillow` that reimplements the underlying
operations to make use of SIMD intrinsics. This doesn't change JPEG decoding
time, but if you're using `Pillow` for image transforms then you should switch
to `Pillow-SIMD` instead. Some people seem to claim `opencv` is faster than
`Pillow-SIMD`, but I've never been able to reproduce it, at least not using the
`opencv-python` package on PyPI which is how most people get `opencv` in the
python community. The absolute fastest way I've found of loading JPEGs is
Joachim Folz's recent and wonderful [`simplejpeg`](https://gitlab.com/jfolz/simplejpeg)
library. It only contains 4 functions, and in [my tests](https://twitter.com/will_price_94/status/1365057412902891521) it was consistently the fastest.

For image transformations there are, again, a lot of options to choose from.
I've typically just used `Pillow-SIMD`, but [`albumationations`](https://github.com/albumentations-team/albumentations) looks interesting and their benchmarks seem compelling. 

Now I don't expect CPU image decoding and transformation to last that much
longer. We're moving to the GPU, I see that as inevitable, but the libraries and
tooling aren't as nice to use as the CPU counterparts. Up to my knowledge,
[DALI](https://docs.nvidia.com/deeplearning/dali/user-guide/docs/index.html) is
the only real player in this domain. It encompasses both GPU accelerated JPEG
decoding through [`nvJPEG`](https://developer.nvidia.com/nvjpeg) and comes out
of the box with GPU accelerated transforms. DALI is an all or nothing library,
you either adopt it for all your data needs or you don't, there aren't
particularly easy ways to plumb it up with your own existing data pipeline, and
if you do, you'll probably miss out on most of the benefits it provides.
If you're interested in DALI you should check out [Ceyda Cinarel's blog post on
it](https://cceyda.github.io/blog/dali/cv/image_processing/2020/11/10/nvidia_dali.html),
she clearly explains how to write your own python data source which is something
I found lacking in the docs last time I tried to use DALI.

Torchvision might also come to the rescue in future with `nvJPEG` decoding,
there's an [open PR](https://github.com/pytorch/vision/pull/2786) on adding it,
but it's not been merged yet.
Torchvision could be pretty speedy when this PR lands coupled with torchvision's existing GPU accelerated image transforms, so keep an eye on the release notes of new releases!


#### Video

The same approaches in images can be employed to store frames from a video, this
works quite well when you're sparsely sampling frames. For loading video *clips*
you can often do better by keeping the videos as video files instead of
expanding them out to a directory of images. If you have a lot of compute power
and your data storage is slow, keeping video as video files is especially
appealing as you can trade off the space to store a clip (using an encoder like
vp9) for compute (vp9 takes longer to decompress than simpler encodings).
If you're more constrained on compute (few cores) then you might still be better
off encoding the frames as JPEGs and using libjpegturbo backed library like
`simplejpeg`.

DALI has support for decoding video on the GPU via it's [`video`
reader](https://docs.nvidia.com/deeplearning/dali/user-guide/docs/supported_ops.html#nvidia.dali.fn.readers.video).
I've yet to try this out, but for training networks for action recognition or
other problems where you load full clips this certainly looks like it'd be very
quick.
DALI also supports computing optical flow on the fly using RTX20* series and above cards!
I've not tried this out, but it'd be a nice change from computing TV-L1 offline.


## Common Gotchas

A few mistakes I've seen repeatedly:

* When running on an HPC cluster they forget to request a decent quantity of
  memory or cores and data loading is bottlenecked by that (always request X
  cores and N GB of memory so you know what your runtime configuration is)
* Loading data from a networked filesystem when fast node-local storage is
  available (don't do that, first copy the data over and then train on it)
* Using too few workers in PyTorch's `DataLoader`.
* Writing bad dataset classes that are inefficient
* Storing data in a suboptimal way for reading it quickly.
* Inefficient data augmentation code that gobbles up CPU cycles


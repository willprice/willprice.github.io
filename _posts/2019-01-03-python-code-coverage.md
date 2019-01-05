---
layout: post
title: "Python code coverage"
---

I've set up code coverage tools for python many times before, but have always
found the process rather cumbersome and difficult to understand with fragmented
and frequently incorrect information out there. In an effort to improve this
situation, I decided to write this article focusing on producing coverage with
my usual tools of choice:  [`pytest`](https://docs.pytest.org/en/latest/) with
[`pytest-cov`](https://pytest-cov.readthedocs.io/en/latest/) (which uses [`coverage.py`](https://coverage.readthedocs.io/en))

Your mileage my vary with
different test runners, but the issues flagged up here will help debug coverage
collection issues for any test runner.

One of the main problems arising in collecting code coverage in python is
not knowing which version of the code you're running your tests against. Now you
might think this is ridiculous, and how could you not know which version of code
you're running tests against, but with tools like
[tox](https://tox.readthedocs.io/en/latest/) that install your package into a
virtualenv per python interpreter version, you'll not be testing against the
code in the root of your project folder, but rather that contained in
`.tox/pyXX/lib/pythonX.X/site-packages/mypackage`. This is quite easy to
overlook and can result in frustration when you end up 0% coverage metrics.

To aid your experimentation/debugging I've also put together a
[repo](https://github.com/willprice/pytest-coverage-examples) with example
project layouts showing the results of running `pytest` in different ways with
different coverage configurations

## Code coverage for development tests

The most common set up runs tests against the source code present in your
project root. For this, the tools work pretty well and you'll only encounter a
few hiccups.

We'll assume you have a package structure like this:

```
├── LICENSE
├── MANIFEST.in
├── README.rst
├── setup.py
├── tests
│   ├── test_blah.py
│   └── test_foo.py
└── mypackage
    ├── __init__.py
    ├── package_a
    ├── package_b
    └── module_c.py
```

Running your tests would be accomplished by executing `PYTHONPATH=. pytest`. The
reason for having to use `PYTHONPATH=.` is that be default `pytest` will remove
`$PWD` from `sys.path` to avoid testing against the in-src package. This
behaviour holds, unless your `tests` directory is a package, i.e. it contains a
`__init__.py`, quoting the `pytest` docs:

> ...
> But now this introduces a subtle problem: in order to load the test
> modules from the tests directory, pytest prepends the root of the
> repository to sys.path, which adds the side-effect that now mypkg is also
> importable. This is problematic if you are using a tool like tox to test
> your package in a virtual environment, because you want to test the
> installed version of your package, not the local code from the repository.

Coverage can be collected by invoking `pytest --cov=mypackage tests`.

Whilst these approaches are suitable if you're happy with collecting coverage against
your development install, you should probably be running your tests against an
installed version of your package to pick up any issues present in the packaging
phase of a build (e.g. missing files). We cover this approach in the next
section, but before moving on, a quick note about using a `src` project layout
which can help mitigate some of the confusing behaviour when attempting to test
against the installed package.


### Using a `src` layout

The benefit of using a `src` based layout is that your package is no longer
importable from the root project directory by default. This makes diagnosing
coverage collection issues considerably easier, especially when collecting
coverage against installed versions of your package.

If we modified the repository structure from the previous section to use a `src`
layout, we'd end with this:

```
├── LICENSE
├── MANIFEST.in
├── README.rst
├── setup.py
├── tests
│   ├── test_blah.py
│   └── test_foo.py
└── src
    └── mypackage
        ├── __init__.py
        ├── package_a
        ├── package_b
        └── module_c.py
```

Now running tests would explicitly require the setting of `PYTHONPATH` if we
wish to test against the development version we run `PYTHONPATH=src pytest`, and
to collect coverage: 
`PYTHONPATH=src pytest --cov mypackage`

Cristin Maries has a 
[good blog post](https://blog.ionelmc.ro/2014/05/25/python-packaging/#the-structure)
on the benefits of using a `src` based
project layout which is worth reading. I personally use `src` layouts for all my
new python projects as I've found it results in fewer headaches debugging
`sys.path` issues.


## Code coverage when testing installed packages

Whilst I've advocated testing against installed packages, there are a few issues
to be aware of in collecting coverage from an installed package.
The coverage paths (those reported by `coverage report` and present in the
`.coverage` file) will be those to the installed version of package.
To get nice reports that are like `package/module.py` rather than
`.../site-packages/mypackage-0.2.1/mypackage/module.py`
you'll need to tell `coverage.py` that these paths are equivalent, and then run
a `coverage combine` command after running tests with coverage collection to
rewrite the long paths to short paths. To do
this we leverage the
[`[paths]`](https://coverage.readthedocs.io/en/v4.5.x/config.html#paths) configuration section of `coverage.py`:

```
[paths]
source =
    mypackage
    **/site-packages/mypackage
```

Collecting coverage now and generating a report will go something like this:
```bash
$ pytest --cov mypackage
$ coverage combine
$ coverage report
```

The coverage report produced by `pytest` will have the long paths, but once
rewritten, `coverage report` will have the short paths.

## Conclusion

If you're having issues with collecting coverage, I urge you to check out the
[accompanying repository](https://github.com/willprice/pytest-coverage-examples)
to this post that has example projects with multiple layouts and shows common
mistakes in configuring coverage and their fixes.

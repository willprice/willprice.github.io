---
layout: post
title: "Packages and modules in Python"
---

Previously, and now currently, packages in Python have been a source of much woe
to me. Plagued by hundred of "No module named xxx", "Attempted relative import
in non-package" etc, it is now time to write myself a little guide to refer to
in future.

# Packages and Modules
A **package** is a collection of modules with a `__init__.py` file inside the
package directory and a **module** is simply a python file.

Say I have the layout:

```
* core:
    * __init__.py
    * queue.py
    * tests:
        * queue_tests.py
```

and I want the `Queue` class from `core.queue`. How do I import this in
`queue_tests.py`?

You'd think

{% highlight python %}
from ..queue import Queue

def blah():
    stuff()
{% endhighlight %}

would do it; and you'd be correct. But check how you're running the file. If
you're running it directly like `python tests/queue_tests.py`, then the name of the file will
be `__main__` which breaks relative imports. You have to run it like so: `python
-m tests.queue_tests`. This runs the module `queue_tests` as a script, but fixes
the `__name__` issue.

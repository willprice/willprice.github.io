---
layout: post
title: "Properties in python"
---

As we all know, it's important to wrap field access of an object in a function
e.g. `get_name` simply returns `self.name`. In python one can consider this an
antipattern since we have these wonderful things called `properties`.

`properties` allow you to add a getter (or setter) when you need one, rather
than from the get go. Imagine you'd written a tonne of client code where you're
accessing a password of a user: e.g. `user.password`, but you've now decided
that any time the user password is accessed it should be logged, you might be
thinking "Oh god no, why didn't I use a getter, I could have put the logging
call inside of that". Well no worries, you can transparently do this!

Go from this:

```python
class User(object):
    def __init__(self, name, password):
        self.name = name
        self.password = password

```
To this:

```python
class User(object):
    def __init__(self, name, password):
        self.name = name
        self._password = password

    @property
    def password(self):
        log("Password of user %s, was accessed" % self.name)
        return _password
```
Now any time someone calls `user.password`  it'll call the `password` function,
log the password access and then return the property.

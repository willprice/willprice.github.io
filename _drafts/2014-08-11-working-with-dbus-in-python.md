---
layout: post
title: "Working with DBus in Python"
---

As I am currently rewriting the
[pyomxplayer](https://github.com/jbaiter/pyomxplayer) module for python using
DBus, I thought it would be prudent to see which modules were available for DBus
communication. There are a few littered about, but the main choices seem to be:
* `dbus-python` a wrapper around `libdbus`
  * ~ 15,000 LOC
  * reference implementation
  * written by the DBus developers
  * quite old
  * doesn't integrate well with `virtualenv`s as they don't use `distutils`, so
    `pip` doesn't work to install it :(

* `txdbus` a native python implementation of the DBus protocol
  * ~ 2,000 LOC
  * wrapper around `libdbus`
  * under reasonably active development
  * more pythonic that `dbus-python`
  * developed for the _Twisted networking environment_
* `QtDBus`, Qt's implementation
  * have to install the whole Qt library for this
* `GDBus`, GLib's implementation
  * GLib is fairly ubiquitous

    
References:
----------
* [DBusBindings (freedesktop)](http://www.freedesktop.org/wiki/Software/DBusBindings/)
* [python-tdbus (github)](https://github.com/hmvp/python-tdbus)

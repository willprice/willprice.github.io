---
layout: post
title: "Errors pushing via git in PyCharm/IntelliJ"
---

If you find yourself in the same position as I did where trying to push via an
IntelliJ based IDE isn't working (in my case PyCharm), and you're getting the
error: `Push failed: fatal: Could not read from remote repository`. You might
find that changing your SSH executable from the `built-in` to the system
`native` will fix your woes. Pop into the preferences of your project and
navigate to `Version Control/Git/SSH executable` and flip that setting to
`native`.

---
layout: post
title: "Brother HL-5250DN on Raspberry Pi"
---

I have an old Brother HL-5250DN which I've had issues getting to print
consistently. When I print some PDFs it had been spitting out a page with the
message:

```
ERROR NAME;
   typecheck
COMMAND;
   image
OPERAND STACK;
```

The default drivers available under cups listed as `BR-Script3` do *not* work
well with this printer, and there is quite a wealth of bug reports of people
experiencing similar issues:
- [https://bugs.launchpad.net/ubuntu/+source/foomatic-db/+bug/1306849](https://bugs.launchpad.net/ubuntu/+source/foomatic-db/+bug/130684)
- [https://bugzilla.gnome.org/show_bug.cgi?id=504705](https://bugzilla.gnome.org/show_bug.cgi?id=504705)
- [https://bugs.launchpad.net/ubuntu/+source/evince/+bug/147759](https://bugs.launchpad.net/ubuntu/+source/evince/+bug/147759)
- [https://bugzilla.redhat.com/show_bug.cgi?id=855009](https://bugzilla.redhat.com/show_bug.cgi?id=855009)
- [https://github.com/OpenPrinting/cups-filters/commit/84657859490f302bb6d146517f656d5fe933363d](https://github.com/OpenPrinting/cups-filters/commit/84657859490f302bb6d146517f656d5fe933363d)

If you're on an x86 platform (i.e. not a Raspberry Pi), just visit Brother's
page on the HL-5250DN and download and install their `lpr` and `cupswrapper`
packages. Once you've done that go into cups, modify the printer and select the
driver "Brother HL5250DN for CUPS", not the "Brother HL-2550DN BR-Script3 (en)"
driver which is the buggy one shipped with cups.

Now if you're on ARM (e.g. a Raspberry Pi), you can't do this since the Brother
driver ships some i386 compiled cups filters that they don't provide source
code for. I've had better success with using the postscript driver via the
["Postscript" PPD file on openprinting](https://www.openprinting.org/printer/Brother/Brother-HL-5250DN), following a comment on one of the above bug reports, I did also switch the postscript level from 3 to 2:

```
*LanguageLevel: "3"
```
should be changed to
```
*LanguageLevel: "2"
```

If this approach doesn't work for you, there are [some who have actually run the
Brother drivers under
QEMU](https://superuser.com/questions/781454/debian-arm-and-brother-dcp195c-with-cups), perhaps try that route.

---
title: "Miscellaneous notes on electronics (mainly helping me avoid doing stupid things)"
layout: layout
---

- When using ICSP headers for programming, remember that the pinout diagrams are from looking above, the chip, whereas you're most likely sticking jumpers from underneath.
- [ICSP pinout](http://www.instructables.com/id/Adding-ICSP-header-to-your-ArduinoAVR-board/step3/ICSP-header-pinout/), SCK is next to the notched part of the connector.
- (Arch) make sure that avrdude can access the USBTinyISP, also with arduino, you have to be in the `uucp` group (`gpasswd -a will uucp`). It may also be the case
with systemd that you can't lock /run/lock, this is because incorrect permissions are set, copy `/usr/lib/tmpfiles.d/legacy.conf` to `/etc/tmpfiles.d/` and edit it, changing
the permissions to 0777 for /run/lock. (good notes [here](http://perhof.wordpress.com/tag/usbtinyisp/))
- When programming atmega chips, hook up ALL GROUNDS and ALL VOLTAGE SOURCES.

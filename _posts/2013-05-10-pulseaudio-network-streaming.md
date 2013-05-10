---
layout: post
title: "Pulseaudio network streaming"
description: ""
category: 
tags: []
---
I've tried setting up pulseaudio before to stream music from my laptop to my
desktop without much success. I attribute my past failures to my lack of
understanding of the client/server model that pulseaudio follows. Trust me when
I say it's important to learn the necessery terminology to setup pulseaudio,
  you'll end up quite confused otherwise!

* `server` - A pulseaudio server or daemon accepts `sources` and outputs audio
on a `sink`
* `source` - Any process that outputs audio, for example chromium playing music
from [hypem.com](http://hypem.com/willprice)
* `sink` - A soundcard, a remote pulseaudio server (with soundcards) and some
other niche things (think /dev/null, visualisers).
* `client` - same as a `source`

## Setup the server (the machine that is attached to an audio device): 
  Add the following lines to `/etc/pulse/default.pa`

      load-module module-native-protocol-tcp auth-ip-acl=127.0.0.1;192.168.0.0/24 auth-anonymous=1
      load-module module-zeroconf-publish

  The first line sets up a TCP server for pulseaudio allowing remote sound sources
  to be utilized (clients can be anonymous as well). The second line sets up `zerconf` publishing by the `avahi
  daemon` (enable with `systemctl enable avahi-daemon && systemctl start
          avahi-daemon` on Arch), the clients that will attach to the server will also
  need the `avahi deamon` running to be informed of the pulseaudio server you've
  just set up. 

## Setup the client (the machine that you want audio to be stream from)
  Add the following lines to `/etc/pulse/default.pa`
  load-module module-zeroconf-discover
  Understandably this module searches out for other pulseaudio servers on the LAN.

  Restart pulseaudio and install `pasystray` or `padevchooser` to set your sink
  (desktop) on the client/source (laptop).


## Sources
*  [Pulseaudio on Wikipedia](http://en.wikipedia.org/wiki/PulseAudio)
*  [Sound on Linux is confusing part 1: ALSA](http://colin.guthr.ie/2009/08/sound-on-linux-is-confusing-defuzzing-part-1-alsa/)
*  [Sound on Linux is confusing part 2: Pulseaudio](http://colin.guthr.ie/200k9/08/sound-on-linux-is-confusing-defuzzing-part-2-pulseaudio/)
*  [Pulseaudio examples | Arch Wiki](https://wiki.archlinux.org/index.php/PulseAudio/Examples#PulseAudio_over_network)

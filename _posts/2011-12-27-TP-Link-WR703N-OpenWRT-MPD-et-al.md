---
layout: post
title: First encounters with OpenWRT on the TP-Link WR703N
---
Finally, a post....
I bought a TP-Link WR703N [1], it's a little router meant to be used in conjunction with a 3G Modem, it works as an access point broadcasting a wireless connection allowing multiple devices to utilize the modem at once (quite a clever idea, however, not one I'm interested in using), hence I decided to flash it with OpenWRT [2]

Specs:
RAM - 32Mb
ROM - 4Mb
USB port (USB2)
CPU - Atheros AR7240 - 400Mhz
Wireless - Atheros AR9331 - b/g/n

Powered by a micro usb port, 5.7cm x 5.7cm, serial interface.
(These are just the basics, more here [3])

OpenWRT Install:
The device comes preinstalled with Chinese firmware, I connected the router via ethernet and configured Arch to have the IP 192.168.1.2 (in /etc/rc.conf) but you could also easily use wifi to upload the new firmware.

After connecting to the router, keep hovering over the menu items, the page file names are in English, keep expanding the drop down menus until you find one with a page name similar to 'software upgrade', something along those lines (I do believe it's in one of the last sections). Go to the OpenWRT wiki and download the 'vanilla' firmware for the router, upload this, once the router has upgraded the firmware, it should reboot and openWRT will have been installed

Having now installed the OpenWRT firmware, you can connect to the router via the ethernet port if you configure your computer's IP to be 192.168.1.2, telnet into the router using:
telnet 192.168.1.1
There you are presented with the CLI of the router where you can start manipulating things. Use opkg update to update the packages list and opkg install *package name* to install applications

These are simply the basics and much more informative instructions can be found on the OpenWRT forums and wiki.

OpenWRT Configuration:
I wanted to use the router as a wireless client (i.e. similar to a computer), I used the following network configurations

/etc/config/network

config 'interface' 'loopback'
 option 'ifname' 'lo'
 option 'proto' 'static'
 option 'ipaddr' '127.0.0.1'
 option 'netmask' '255.0.0.0'


config 'interface' 'lan'
 option 'ifname' 'eth0'
 option 'type' 'bridge'
 option 'proto' 'static'
 option 'ipaddr' '192.168.1.1'
 option 'netmask' '255.255.255.0'


config 'interface' 'wan'
 option 'proto' 'dhcp'

/etc/config/wireless
config 'wifi-device' 'radio0'
 option 'type' 'mac80211'
 option 'channel' '11'
 option 'macaddr' '38:83:45:a2:14:18'
 option 'hwmode' '11ng'
 option 'htmode' 'HT20'
 list 'ht_capab' 'SHORT-GI-20'
 list 'ht_capab' 'SHORT-GI-40'
 list 'ht_capab' 'RX-STBC1'
 list 'ht_capab' 'DSSS_CCK-40'

config 'wifi-iface'
 option 'device' 'radio0'
 option 'network' 'wan' #Set the adapter to act as a wide area network -- not sure why
 option 'ssid' 'Price LAN'
 option 'key' '*******'
 option 'encryption' 'psk2' # My network uses psk2 security
 option 'mode' 'sta' #Setup client mode

In the section 'config 'wifi-iface'' I've setup the router to act as a client by setting the 'mode' to 'sta' which sets the router to act as a client rather than an access point.

USB Support:
I needed USB support as the router only has a 4mb flash which isn't sufficient to install transmission, mpd, mpc etc. I updated
/etc/opkg.conf to remedy this (look at the wiki page on opkg, there is a section on how to do this).

Now I could install to my memory stick using the command
opkg -d usb install *package name*
This usually works fairly well, I had to update my PATH variable in /etc/profile to reflect the new install directories.

I've also played around in /etc/rc.local setting up some startup applications.
I've got mpd, transmission-daemon and mpc (adding playlists) on startup. 

Links:
[1] - $22/£15 - http://www.volumerates.com/product/genuine-tp-link-tl-wr703n-150m-11n-mini-wifi-wireless-router-for-instant-wifi-connection-99273
[2] - https://openwrt.org/
[3] - OpenWRT wiki page on WR703N - http://wiki.openwrt.org/toh/tp-link/tl-wr703n


---
layout: post
title: "WR703n OpenWRT ... again"
description: "Playing around with OpenWRT on the TP-Link WR703n again"
category: "Linux"
tags: ["linux", "wr703n", "router", "mpd"]
---

## Installation of OpenWRT on device
I wanted to start using the WR703n again for a project. This decision was brought about by wanting to ressurect an old project: building a wifi radio with access to my desktop music collection. I had already flashed OpenWRT on the device so I just needed to update it, this can be acheived by running the following commands on the device.

{% highlight sh %}
$ wget http://downloads.openwrt.org/snapshots/trunk/ar71xx/openwrt-ar71xx-generic-tl-wr703n-v1-squashfs-factory.bin /tmp
$ mtd -r write /tmp/openwrt-ar71xx-generic-tl-wr703n-v1-squashfs-factory.bin firmware
{% endhighlight %}

mtd writes the image `openwrt-ar71xx-generic-tl-wr703n-v1-squashfs-factory.bin` to the `firmware` portion of the device (specific memory address range) and then `-r` tells it to reboot after it completes writing.

If you haven't already installed OpenWRT on the router, follow the instructions on this article: [xinechejan wiki](http://wiki.xinchejian.com/wiki/Install_OpenWRT_on_TPlink_WR703N).


## Network Configuration
Now OpenWRT is up and running again, it's time to set up the network, because we've just done a fresh install, we have to access the device through it's ethernet port. This is a bit annoying, first I have to disconnect from wireless on my PC, and then setup a manual connection using NetworkManager using `nm-applet`, first I set my wired connection to manual with the following characteristics:

- IP: 192.168.1.2 (this is the IP address of our computer)
- Subnet Mask: 255.255.255.0 (standard subnet mask)
- Default Route: 192.168.1.1 (this is the IP address of the WR703n)

Save this as "OpenWRT fresh", or something descriptive. 

[Umbrella page for OpenWRT configuration](http://wiki.openwrt.org/doc/howto/basic.config) - Use this page to find out how to configure services.

Now we can telnet into the router and update the settings to enable wireless. we're going to configure the device so that it will _connect_ (note: I'm not enabling it as an access point, it will act as a client -- like a laptop etc) to my internet router.

My network is comprised of a WR1043nd that is connected to a modem for internet access, then all the PCs on our network connect wirelessly to the router for internet access, this is a common arrangement. I want the WR703n to act as a client like my PCs so it can stream radio and connect to my desktop to stream music from a music server.

I think it's important to outline what is going to be changed and for what reasons, there are far too many guides that specify what to change but not why, which makes it very difficult to trouble shoot. We'll take a top-down development approach to configuration, as I detailed eariler, I want the WR703n to act as a client, we might as well connect wlan0 to eth0 so my RPi can be connected to it to gain internet access. 

A few terms need to be defined clearly if this is going to be at all understandable. 
- LAN: Local Area Network, this is the network containing my internet router and all my PCs, this is essentially a safe network, where there is no need to be particularly careful.
- WLAN: Wireless Local Area Network, instead of cabling, we do things wirelessly.
- WAN: Wide Area Network, e.g. the Internet. WANs are large computer networks spanning large regions. WANs connect LANs together allowing LANs to talk to each other.

Quite often I see firewall rules with 'wan' referring to the connection to the internet router in a LAN, like in this example where the WR703n isn't acting as a router, but a client. I'm pretty sure this is incorrect (but please leave a comment if I've misunderstood). The network we're going to create will have a 'lan' zone and a 'wlan' zone, the 'lan' zone will correspond to anything attached to the ethernet port of the WR703n, whereas the 'wlan' zone will correspond to the network all our computers are on, along with the internet router. The connection to the internet will be through the 'wlan' zone as our internet router lies in this subnet, the firewall file is configured to allow input and output (refer to the definitions further down) in the 'wlan' zone, 

To implement this zoning, we have to configure the /etc/config/network (zone definitions) file and the /etc/config/firewall file, as it defines where packets can come from, whether they're regetted etc. 

{% highlight sh %}
# /etc/config/firewall
# I've ommitted the rest of the configuration files as these are the entries
# that need modification. 
#
# This is the original file
config zone                      
        option name             lan
        option network          'lan'
        option input            ACCEPT
        option output           ACCEPT
        option forward          REJECT

config zone                           
        option name             wan
        option network          'wan'
        option input            REJECT
        option output           ACCEPT
        option forward          REJECT
        option masq             1
        option mtu_fix          1

config forwarding                
        option src              lan
        option dest             wan

{% endhighlight %}

Refer to [OpenWRT firewall](http://wiki.openwrt.org/doc/uci/firewall) for available options and more indepth descriptions.

We're going to modify the entries above to get rid of the 'wan' zone, replacing it with 'wlan', and allow packets from the internet coming in on the 'wlan' zone to reach the 'lan' zone. The settings above are the default settings shipped with OpenWRT that correspond to the situation where the device is being used as an internet router, and hence will block input from the 'wan' (internet) zone unless it's filtered by one of the other rules found in /etc/config/firewall, the 'lan' is bridged to the 'wan' meaning that requests for addresses outside the specific subnet the computers lie on will be routed through the router and to the internet.

Understanding the firewall configuration is very much dependent upon understanding how 'output', 'input' and 'forward' options work, they're all quite simple, but keep that if you don't understand the reason for a particular configuration option, come back to the definitions and try and figure out what would happen to a packet if the option was enabled or disabled (most of the time options are disabled for security, and enabled to allow communication through).

_These definitions are lifted from the [OpenWRT firewall page](http://wiki.openwrt.org/doc/uci/firewall)._

- `input`: Input rules describe what happens to traffic trying to reach the router itself through that zone.
- `output`: Output rules describe what happens to traffic originating from the router itself.
- `forward`: Forward rules describe what happens to traffic coming from that zone, targetting another zone.

More lingo needs to be clearly defined.
- `zone`: A software abstraction used in the firewall defining what happens to packets, it is attached to a specific network interface e.g. 'lan'
- `network interface`: A software abstraction of a physical networking device, which is setup with particular properties, in OpenWRT there are defined in /etc/config/wireless e.g. 'wlan0'
- `network device`: The actual device, driver loaded by the linux kernel which initializes a network device e.g. 'radio0'

So now we actually know what 'things' are, we can write some configuration files!

{% highlight sh %}
# /etc/config/firewall
# Configured for our needs   

# Our 'lan' zone will cover everything attached to the ethernet port
config zone                      
        option name             lan
        option network          'lan'
        # Packets are going to be sent through the ethernet port
        option input            ACCEPT        
        # No need to allow packets to leave the router through 'lan'/eth0 as everything coming through 'lan' is forwarded to 'wlan'
        option output           REJECT       
        # No need to allow for forwarding as we already have a dedicated rule, and only 2 zones.
        option forward          REJECT       

# Our 'wlan' zone will connect to the internet router providing a connection for itself and any
# machines connected to it's ethernet port. (as 'wlan'/wlan0 is bridge to 'lan'/eth0)
config zone                           
        # Rename network to be more accurate
        option name             wlan          
        option network          'wlan'
        # If we want to SSH to the router over wifi, we need the device to accept the packets as 
        # they'll be received on the wlan0 device that 'wlan' will be attached to.
        option input            ACCEPT        
        # Obviously we want packets to leave the device through 'wlan'/wlan0
        option output           ACCEPT        
        # If you want to SSH into clients behind this device, then the requests will come in on the
        # 'wlan'/wlan0 zone/interface, which won't be forwarded to the 'lan'/eth0 zone/interface, so
        # to SSH into clients, ACCEPT forwarding packets. I'm leaving this as REJECT as I don't require the functionality.
        # You'll also need to setup a forwarding config for wlan -> lan
        option forward          REJECT        
        # Masquerading is a form of NAT (network address translation), this allows clients attached to 'lan' to speak to 
        # outside world through this device, without having an external IP address, though they cannot be addressed outside of
        # 192.168.2.0/24 subnet. Setup routing for access to this subnet.
        option masq             1
        # Enables MSS Clamping, look here:
        # http://www.tegola.org.uk/howto/pmtud.html
        option mtu_fix          1

# forwarding configurations allow specific directions of flows between 2 zones, everything else is DROPPED/REJECTED.
# forward: lan -> wlan
config forwarding                             
        option src              lan
        option dest             wlan
{% endhighlight %}


{% highlight sh %}
# /etc/config/network
# Original
{% endhighlight %}

{% highlight sh %}
# /etc/config/network
# Modified
# The settings stored here attach IP address settings and
# network interfaces to definitions of zones.

config interface 'loopback'
        option ifname 'lo'
        option proto 'static'
        option ipaddr '127.0.0.1'
        option netmask '255.0.0.0'
                                  
# 'lan' can be left as it is
config interface 'lan'            
        option ifname 'eth0'
        option type 'bridge'
        option proto 'static'
        option ipaddr '192.168.2.1'
        option netmask '255.255.255.0'
                                      
# We now attach the 'wlan' zone to the wlan0 wireless interface, which is in turn attached to
# radio0, the wireless radio in the WR703n
config interface 'wlan'               
        option ifname 'wlan0'
        # 
        option proto 'dhcp'
{% endhighlight %}


{% highlight sh %}
# /etc/config/wireless
config wifi-device  radio0
        option type     mac80211
        option channel  11
        option macaddr  38:83:45:a2:14:18
        option hwmode   11ng
        option htmode   HT20
        list ht_capab   SHORT-GI-20
        list ht_capab   SHORT-GI-40
        list ht_capab   RX-STBC1
        list ht_capab   DSSS_CCK-40

config wifi-iface
        option device   radio0
        option network  wan               # 'wan' is wide-area-network, as distinguised from 'lan'
        option mode     sta               # 'sta' enables managed client mode, allowing connection to another wireless network
        option ssid     'Price LAN'       # wireless access point name, replace with your SSID
        option key      'priceLanPassword' # wireless access point key, replace with the pass to your SSID
        option encryption psk2            # wireless access point encryption
{% endhighlight %}


## Router Bricking & Serial access
I've had such a crappy time trying to get my USB-to-UART converter working, it's just one of these cheap CP2102 based dongles, there's nothing wrong with the hardware, it's just my ignorance in setting up serial connections, and what hardware flow control is etc. 

After tweaking multiple settings and using different programs, I've got a serial connection up, first, if you want to understand what's going on with serial check out the [TLDP Documentation](http://www.tldp.org/HOWTO/Serial-HOWTO-4.html) which is excellent -- it'll help you diagnose problems. If you don't fancy doing that just follow what I've written, providing you have the same hardware, it should work.

- Install minicom: `pacman -S minicom` (if you're on arch, apt-get if you're on a deb based distribution)
- Find out what your serial device is labelled as: `ls /dev/ | grep -i usb`, this should give you something like `ttyUSB0`, figure out which one is your USB to serial device
- Global configuration of minicom: `sudo minicom -s`, `-s` enters the setup menu, running as root allows you to save to /etc/minirc.dfl, minicoms configuration file.
- Settings:
 - Go into 'Serial port setup':
  - Set serial device as `/dev/ttyUSB0` or whatever your device is recognised as
  - Bps/Par/Bits should be 115200 8N1 which means that the serial connection is setup to run at 115200 baud (symbols per second), [8N1](http://en.wikipedia.org/wiki/8-N-1) defines that there should be 8 data bits per word, with no parity bit and 1 stop bit, so each word consists of a 9 bit string, 8 bits form the word (usually an ASCII character) and 1 bit defines where the word ends.
  - Hardware Flow Control should be _off_, this caused me a lot of trouble as when the device was booting I could see all the messages the WR703n was transmitting, but I couldn't send anything in return, this remedied that issue.
  - Software Flow Control can be on or off, or at least I found it didn't make a difference
  - Leave everything else as it is

A feel a little mention of what 'flow control' is might ease the troubleshooting of misbehaving serial devices. Flow control is used to define how quickly bytes are transferred through a wire, if you're using hardware flow control, 2 separate data lines are required, they send signals about when to send data, this is through the RTS (request to send) and CTS (clear to send) pins. If hardware flow control is turned on then, these pins need to be connected to the device, the WR703n doesn't have any CTS and RTS pins (AFAIK) so hardware flow control mustn't be used. Software flow control mimics this behavious through software, it can be used, I haven't found any benefit or disadvantage to using it, so I don't bother with it.

Now minicom is set up, it's time to perform a _loopback test_ to confirm whether it's actually had the correct configuration. The loopback test involves jumpering the RXD (Receive eXchanged Data) and TXD (Transmit eXchanged Data) pins so that anything you type is sent through TXD is received at RXD (I hope I've got this the right way round). Jumper RXD and TXD, fire up minicom and start typing, if you can't see anything then you have probably set up minicom wrong, this happened for me and was solved by turning 'Hardware Flow Control' _off_. 

Minicom can now transmit and receive data through the USB to UART dongle, hook it up to the WR703n through the `TP_OUT` and `TP_IN` pins, you might not connect them up right first time, so if you turn on the WR703n and don't see anything spewing out of minicom then try switching around RXD and TXD (I mixed up TXD and ground on my board... I didn't look at where my wires were going carefully enough which caused me a lot of pain).

To enter into the uboot command prompt type 'tpl' as quickly as possible when the device starts up. You can also enter failsafe mode though serial, which is nice, instruction for this are spewed out during startup (`<F>` followed by `<Return>` followed by `<Return>` again a little later). Now you can set up a local tftp server and boot from that if you're stuck. 

### Booting using tftpboot
_This requires access to serial port_
1. Boot up the router typing 'tpl' into the terminal to enter the uboot command line
2. Set environment variables, assuming routers IP is: 192.168.1.1, PC ip is: 192.168.1.2
   - setenv ipaddr 192.168.1.1
   - setenv serverip 192.168.1.2
3. Check environment variables with `printenv`, they should match what you've set them to.
4. Disconnect from you wireless network as you're likely to be on the 192.168.1 subnet which will interfere with the tftp server
5. Run the following commands on the router:
   - tftpboot 0x81000000 openwrt.bin
   - erase 0x9f020000 +0x3c0000
   - cp.b 0x81000000 0x9f020000 0x3c0000
   -  bootm 0x9f020000
Now you should have copied the original firmware from the tftp server and flashed it to the device succesfully, you should the system log output through the serial port if it was successful.

## Installing applications (alternatives to root)
First, you need to have a cursory knowledge of the [flash layout of OpenWRT](http://wiki.openwrt.org/doc/techref/flash.layout). I'll try my best to offer a simple explanation here, but you might well be better off getting the information directly from the flash layout page. 

The flash layout of OpenWRT consists of writeable and non-writeable chunks of flash memory, the whole flash memory is first broken into chunks:
- *mtd0*: *u-boot*: u-boot is installed here
- *mtd5*: *firmware*:
   - *mtd1*: *kernel*: The kernel is stored in this subdivision of the *firmware* block
   - *mtd2*: *rootfs*:
      - /rom takes up the first part of this block using the SquashFS filesystem, this is non-writeable, it stores all the applications that were part of the OpenWRT build you're using.
   - *mtd3*: *rootfs_data* is mounted to /overlay using JFFS2 filesystem, this is writeable and where everything gets written to during your day to day use of OpenWRT

The bottleneck for installing application is the size of the `/overlay` partition, the idea is that we move the location of `/overlay` from the flash memory to some external device. 

Given the rather small size of the flash memory in this device, you're stuck installing applications etc to external storage, this most probably will be a memory stick plugged into the USB port. If you're going to use USB storage head over to [this article](http://wiki.openwrt.org/doc/techref/opkg#installation.destinations) to install directly to the USB storage whilst keeping the overlay filesystem on the device, this is a rather hacky approach meaning that each time you install an application, if it's got any init files, they'll have to be symlinked over to the *rootfs_data* device which is simply `/etc/init.d/` as /overlay gets merged with `/rom` as `/` during startup. Alternatively you can use the memory stick as the overlay filesystem, some bootloaders allow this functionality, (checkout [Das U-Boot](http://wiki.openwrt.org/doc/techref/bootloader/uboot) and [RedBoot](http://wiki.openwrt.org/doc/techref/bootloader/redboot), I believe these are supported by a limited number of routers). I'm going to use *extroot* which boots up normally, without any custom bootloader, it then switches the overlay directory from the flash device to the external memory stick.

First get [USB Storage](http://wiki.openwrt.org/doc/howto/usb.storage) working, you should be able to see some `/dev/sd*` devices present after following the article. Install `kmod-fs-ext4` or `kmod-fs-vfat`, or whatever filesystem module is appropriate for your memory stick, I use ext4, I also had to install `libext2fs` to be able to mount my memory stick, and as always YMMV. Now that you can mount you memory stick, just try writing to it and unmounting and remounting just to make sure everything worked. You _MUST_ be able to mount and write to your device before carrying on, otherwise debugging is going to be a PITA if you don't know what's broken. 

Now go an read how [extroot works](http://wiki.openwrt.org/doc/howto/extroot/extroot.theory), reading this will save you time in the long run, you should understand things before trying to implement them, when something goes inevitably wrong, you'll be glad you have some sort of idea how the system works. The extroot method I'm describing from here out is for use on 'Attitude Adjustment' or above, previous versions of OpenWRT use the `is_rootfs` option, read the wiki if you're using an old version. 

Configuring OpenWRT to use your memory stick for an external partition is actually very easy, just open up /etc/config/fstab and modify the lines like this:
{% highlight sh %}

{% endhighlight %}

When OpenWRT turns on, the following happens
* Sequence pivot overlay
* IF NOT SquashFS, root is remounted rw on /
* IF SquashFS, JFFS2 is mounted rw on /tmp/overlay
 IF /tmp/overlay/etc/config/fstab exists we use it as the configuration file, otherwise we use /etc/config/fstab (if it exists)
* Fork
* Backfire: we search for a mount section in the fstab-file with the option `is_rootfs` set to true, and mount it on /overlay, if we find it
* Attitude Adjustment: in trunk we prefer to look for a mount section in the fstab-file with the target /overlay
* we unmount /tmp/overlay again and/or remount root (/) read only
* we pivot the root so that that /overlay on top of /rom is now root, and old root is on /rom
* [OpenWRT wiki: extroot.theory](http://wiki.openwrt.org/doc/howto/extroot/extroot.theory)

So the memory stick gets mounted after /tmp/overlay is unmounted, leaving the memory stick with /rom combined to form the `/` filesystem. You can go ahead an install what you like now as you've got a nice big memory stick for installing programs! Initially I had tried to configure `opkg` to install to a memory stick, but things got messy with changing `$PATH` and `$LD_LIBRARY_PATH` which was a hack at best.

---
layout: post
title: Adventures with SPI TFT screens for the Raspberry Pi 
toc: yes
---

The following is a grab bag of notes from an afternoon of playing around with
a [Elegoo 3.5" 480x320 SPI TFT touch
screen](https://www.amazon.co.uk/480x320-Raspberry-Elegoo-Monitor-Interface/dp/B01MRQTMTD/ref=sr_1_1?ie=UTF8&qid=1505683694&sr=8-1&keywords=elegoo+3.5%22)

**TL:DR**

Skip these rubbish screens, they're a massive pain to set up and have very poor
refresh rates (sub 8 FPS)

If you're a masochist and want to learn more, read on...

---


## Background

These little TFT screens use SPI and are controlled via the
[`fbtft`](https://github.com/notro/fbtft/) framebuffer driver that is part of
the linux kernel.

This article is written testing the screen on a Raspberry Pi 2 loaded with
Raspbian `2017-09-07-raspbian-stretch.zip`


## Raspbian setup

### Provided driver (`LCD-show`)
The screen comes with a link to a prebuilt raspbian image setup for use,
however I wanted the latest Raspbian release and didn't want to reflash my SD
card. The screen also provided a driver folder with a bunch of tar archives called
`LCD-show-XXXXXX.tar.gz` and a README specifying the compatibility of each version
of LCD-show with Raspbian versions:

| LCD-show version | Min Raspbian version  | Max Raspbian version |
|------------------+-----------------------+----------------------|
| Unmarked         | ?                     | 2015-05-05 Wheezy    |
| 150602           | ?                     | 2015-05-05 Wheezy    |
| 151020           | 2015-05-05 Wheezy     | 2015-09-24 Jessie    |
| 160620           | 2016-05-10 Jessie     | Latest (?)           |
| 160701           | 2016-05-10 Jessie (?) | Latest (?)           |

An additional version `160701` was provided but not documented, I assume this
is the latest and should be used with the latest version of Raspbian.

Un-tarring the latest `LCD-show` yields a bunch of files:

```
.
├── boot
│   ├── config-28.txt
│   ├── config-32.txt
│   ├── config-35.txt
│   ├── config-397.txt
│   ├── config-43.txt
│   ├── config-5.txt
│   ├── config-7B-800x480.txt
│   ├── config-7C-1024x600.txt
│   └── config-nomal.txt
├── LCD28-show
├── LCD32-show
├── LCD35-show
├── LCD397-show
├── LCD43-show
├── LCD5-show
├── LCD7B-show
├── LCD7C-show
├── LCD-hdmi
├── ReadMe.txt
├── usr
│   ├── 99-calibration.conf-28
│   ├── 99-calibration.conf-32
│   ├── 99-calibration.conf-35
│   ├── 99-calibration.conf-397
│   ├── 99-calibration.conf-43
│   ├── 99-calibration.conf-5
│   ├── 99-fbturbo.conf
│   ├── 99-fbturbo.conf-HDMI
│   ├── cmdline.txt
│   ├── inittab
│   ├── modules-HDMI
│   ├── tft35a-overlay.dtb
│   └── tft9341-overlay.dtb
└── xinput-calibrator_0.7.5-1_armhf.deb
```

Here's the README:

```
[version]
 v1.1
[Driver installation]
Step1, Install Raspbian official mirror
1)Download Raspbian official mirror:https://www.raspberrypi.org/downloads/
2)Use SDFormatter.exe to Format your TF Card
3)Use Win32DiskImager.exe Burning mirror to TF Card
Step2, Install LCD Driver
1)Copy LCD-show-160701.tar.gz to the root directory of raspberry pi you can copy it directly to TF card after Step1, or use SFTP to remote copy
2)Landing Raspberry pi system to user command line (Name:pi,Password:raspberry) Execute the following command:
cd /boot
sudo tar zxvf LCD-show-160701.tar.gz
cd LCD-show/
#For 2.8inch RPI LCD excute:
sudo ./LCD28-show
# For 3.2inch RPI LCD excute:
sudo ./LCD32-show
# For 3.5inch RPI LCD excute:
sudo ./LCD35-show
# For 3.97inch RPI LCD excute:
sudo ./LCD397-show
# For 4.3inch RPI LCD excute:
sudo ./LCD43-show
# For 5inch RPI LCD excute:
sudo ./LCD5-show
# For 7inch(B)-800X480 RPI LCD excute:
sudo ./LCD7B-show
# For 7inch(C)-1024X600 RPI LCD excute:
sudo ./LCD7C-show
# If you need to switch back to the traditional HDMI display excute:
Sudo ./LCD-hdmi

3)Wait a few minutes,the system will restart automatically, enjoy with your LCD.
```

So what's in these `LCDXX-show` scripts? Here's `LCD35-show` for setting up a 3.5" TFT.

```
sudo mkdir /etc/X11/xorg.conf.d
sudo cp ./usr/tft35a-overlay.dtb /boot/overlays/
sudo cp ./usr/tft35a-overlay.dtb /boot/overlays/tft35a.dtbo
sudo cp -rf ./usr/99-calibration.conf-35  /etc/X11/xorg.conf.d/99-calibration.conf
sudo cp -rf ./usr/99-fbturbo.conf  /usr/share/X11/xorg.conf.d/
sudo cp ./usr/cmdline.txt /boot/
sudo cp ./usr/inittab /etc/
sudo cp ./boot/config-35.txt /boot/config.txt
sudo reboot
```

Hooray, it's a really shitty shell script! Got changes in your `config.txt`?
Kiss goodbye to them! How about `cmdline.txt`? Gone as well! Fuck you, puny
user.

Does it work? No. The script reboots the pi and comes up with a white screen.
What now? Googling `LCDShow` brings up the [LCDShow
repository](https://github.com/goodtft/LCD-show), let's try the latest (commit
e6fd2c6abb2195a2b08c856ddeee2ba4c07d7c1f). Hooray, success!

![Initial success!](/media/img/raspberry-pi/elegoo-tft/initial-success.png)

Refresh rate is appalling, as can be seen in the video below.

<div class="yt-video-wrapper">
  <iframe width="856" height="480" src="https://www.youtube.com/embed/6swVrs4jOyY"></iframe>
</div>

Let's dig deeper and find out how it works.

Here's the working version of `LCD35-show`

```
#!/bin/bash
sudo mkdir /etc/X11/xorg.conf.d
sudo cp ./usr/tft35a-overlay.dtb /boot/overlays/
sudo cp ./usr/tft35a-overlay.dtb /boot/overlays/tft35a.dtbo
sudo cp -rf ./usr/99-calibration.conf-35  /etc/X11/xorg.conf.d/99-calibration.conf
sudo cp -rf ./usr/99-fbturbo.conf  /usr/share/X11/xorg.conf.d/
sudo cp ./usr/cmdline.txt /boot/
sudo cp ./usr/inittab /etc/
sudo cp ./boot/config-35.txt /boot/config.txt
nodeplatform=`uname -n`
kernel=`uname -r`
version=`uname -v`
if test "$nodeplatform" = "raspberrypi";then
echo "this is raspberrypi kernel"
version=${version%% *}
version=${version#*#}
echo $version
if test $version -lt 970;then
echo "reboot"
else
echo "need to update touch configuration"
if test $version -ge 1023;then
echo "install xserver-xorg-input-evdev_2.10.5-1"
sudo dpkg -i -B xserver-xorg-input-evdev_2.10.5-1_armhf.deb
else
echo "install xserver-xorg-input-evdev_1%3a2.10.3-1"
sudo dpkg -i -B xserver-xorg-input-evdev_1%3a2.10.3-1_armhf.deb
fi
sudo cp -rf /usr/share/X11/xorg.conf.d/10-evdev.conf /usr/share/X11/xorg.conf.d/45-evdev.conf
echo "reboot"
fi
else
echo "this is not raspberrypi kernel, no need to update touch configure, reboot"
fi
sudo reboot
```

We've got

* Overlay
* X11 config
* Kernel options
* `inittab`
* `config.txt`

Let's find out what they do.

First the overlays... What is an overlay? Googling round leads to the
[`overlays`](https://github.com/raspberrypi/firmware/tree/master/boot/overlays)
directory in the Raspberry Pi firmware github repo which has a README
explaining that overlays are *device tree overlays* and have something to do
with loading modules, they supersede module loading from `/etc/modules`. Here's the device tree spiel:

> Device Tree makes it possible to support many hardware configurations with
> a single kernel and without the need to explicitly load or blacklist kernel
> modules. Note that this isn't a "pure" Device Tree configuration (c.f.
> MACH_BCM2835) - some on-board devices are still configured by the board support
> code, but the intention is to eventually reach that goal.
>
> On Raspberry Pi, Device Tree usage is controlled from /boot/config.txt. By
> default, the Raspberry Pi kernel boots with device tree enabled. You can
> completely disable DT usage (for now) by adding: `device_tree=` to your
> config.txt which should cause your Pi to revert to the old way of doing
> things after a reboot.

Are overlays plain text? `vi /boot/overlays/tft35a.dtbo`... nope. But they've
got a decent amount of ASCII in them: `strings /boot/overlays/tft35a.dtbo`
lists all the ASCII strings in the file, not hugely useful or informative.
Moving on.

Back to the Raspberry Pi docs:

> Overlays are loaded using the "dtoverlay" directive. As an example, consider
> the popular lirc-rpi module, the Linux Infrared Remote Control driver. In the
> pre-DT world this would be loaded from /etc/modules, with an explicit
> "modprobe lirc-rpi" command, or programmatically by lircd. With DT enabled,
> this becomes a line in config.txt: `dtoverlay=lirc-rpi`. This causes the file
> /boot/overlays/lirc-rpi.dtbo to be loaded. By default it will use GPIOs 17
> (out) and 18 (in), but this can be modified using DT parameters:
> `dtoverlay=lirc-rpi,gpio_out_pin=17,gpio_in_pin=13`.
>
> Parameters always have default values, although in some cases (e.g. "w1-gpio")
> it is necessary to provided multiple overlays in order to get the desired
> behaviour. See the list of overlays below for a description of the parameters
> and their defaults.

So what did `LCD35-show` do to the `config.txt`, what overlays did it enable?
Well if I'd had the old `config.txt` before the script overwrote it I could
`diff` it, *sigh*. How do I get the default `config.txt`? Googling doesn't
yield much--I'll mount the boot partition from the original
`2017-09-07-raspbian-stretch.img` that I wrote to the SD card:

```bash
$ fdisk -l 2017-09-07-raspbian-stretch.img
Disk 2017-09-07-raspbian-stretch.img: 4.6 GiB, 4916019200 bytes, 9601600 sectors
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disklabel type: dos
Disk identifier: 0x020c3677

Device                           Boot Start     End Sectors  Size Id Type
2017-09-07-raspbian-stretch.img1       8192   93814   85623 41.8M  c W95 FAT32 (LBA)
2017-09-07-raspbian-stretch.img2      94208 9601599 9507392  4.5G 83 Linux

$ mkdir boot

# Offset is in sectors, each sector is 512 bytes.
$ sudo mount -v -o offset=$((8192 * 512)) -t vfat 2017-09-07-raspbian-stretch.img boot
$ ls boot/config.txt
-rwxr-xr-x 1 root root 1590 Sep  7 16:05 boot/config.txt*
```

Ta da! Here's the original in case anyone needs it

```
# For more options and information see
# http://rpf.io/configtxt
# Some settings may impact device functionality. See link above for details

# uncomment if you get no picture on HDMI for a default "safe" mode
#hdmi_safe=1

# uncomment this if your display has a black border of unused pixels visible
# and your display can output without overscan
#disable_overscan=1

# uncomment the following to adjust overscan. Use positive numbers if console
# goes off screen, and negative if there is too much border
#overscan_left=16
#overscan_right=16
#overscan_top=16
#overscan_bottom=16

# uncomment to force a console size. By default it will be display's size minus
# overscan.
#framebuffer_width=1280
#framebuffer_height=720

# uncomment if hdmi display is not detected and composite is being output
#hdmi_force_hotplug=1

# uncomment to force a specific HDMI mode (this will force VGA)
#hdmi_group=1
#hdmi_mode=1

# uncomment to force a HDMI mode rather than DVI. This can make audio work in
# DMT (computer monitor) modes
#hdmi_drive=2

# uncomment to increase signal to HDMI, if you have interference, blanking, or
# no display
#config_hdmi_boost=4

# uncomment for composite PAL
#sdtv_mode=2

#uncomment to overclock the arm. 700 MHz is the default.
#arm_freq=800

# Uncomment some or all of these to enable the optional hardware interfaces
#dtparam=i2c_arm=on
#dtparam=i2s=on
#dtparam=spi=on

# Uncomment this to enable the lirc-rpi module
#dtoverlay=lirc-rpi

# Additional overlays and parameters are documented /boot/overlays/README

# Enable audio (loads snd_bcm2835)
dtparam=audio=on
```

Here's the diff (`/boot/config.txt` is the config from `LCD-show`):

```
--- /home/pi/config.txt 2017-09-17 17:57:37.065563044 +0000
+++ /boot/config.txt    2017-09-17 17:20:58.000000000 +0000
@@ -1,5 +1,5 @@
 # For more options and information see
-# http://rpf.io/configtxt
+# http://www.raspberrypi.org/documentation/configuration/config-txt.md
 # Some settings may impact device functionality. See link above for details

 # uncomment if you get no picture on HDMI for a default "safe" mode
@@ -22,7 +22,7 @@
 #framebuffer_height=720

 # uncomment if hdmi display is not detected and composite is being output
-#hdmi_force_hotplug=1
+hdmi_force_hotplug=1

 # uncomment to force a specific HDMI mode (this will force VGA)
 #hdmi_group=1
@@ -43,10 +43,10 @@
 #arm_freq=800

 # Uncomment some or all of these to enable the optional hardware interfaces
-#dtparam=i2c_arm=on
+dtparam=i2c_arm=on
 #dtparam=i2s=on
-#dtparam=spi=on
-
+dtparam=spi=on
+enable_uart=1
 # Uncomment this to enable the lirc-rpi module
 #dtoverlay=lirc-rpi

@@ -54,3 +54,5 @@

 # Enable audio (loads snd_bcm2835)
 dtparam=audio=on
+dtoverlay=tft35a
+#dtoverlay=ads7846,cs=1,penirq=17,penirq_pull=2,speed=1000000,keep_vref_on=1,swapxy=1,pmax=255,xohms=60,xmin=200,xmax=3900,ymin=200,ymax=3900
```

In terms of functional changes we've only got these:

```
-#hdmi_force_hotplug=1
+hdmi_force_hotplug=1
...
-#dtparam=i2c_arm=on
+dtparam=i2c_arm=on
...
-#dtparam=spi=on
+dtparam=spi=on
...
+enable_uart=1
+dtoverlay=tft35a
```

* HDMI force hotplug enabled
* UART enabled (why!?)
* SPI enabled
* `tft35a` overlay added

Not sure why I2C is enabled seeing as this is a SPI screen, moving on... the
main changes are enabling SPI and adding the `tft35a` overlay.

What about the `cmdline.txt`, how has that changed?

Here's the original (after adding linebreaks):

```
dwc_otg.lpm_enable=0
console=serial0,115200
console=tty1
root=PARTUUID=020c3677-02
rootfstype=ext4
elevator=deadline
fsck.repair=yes
rootwait
quiet
init=/usr/lib/raspi-config/init_resize.sh
splash
plymouth.ignore-serial-consoles
```

After line breaking here's a diff with the replacement

```
--- cmdline.txt.orig    2017-09-17 18:05:48.081800539 +0000
+++ cmdline.txt 2017-09-17 18:06:41.511375876 +0000
@@ -1,12 +1,10 @@
 dwc_otg.lpm_enable=0
-console=serial0,115200
 console=tty1
-root=PARTUUID=020c3677-02
+console=ttyAMA0,115200
+root=/dev/mmcblk0p2
 rootfstype=ext4
 elevator=deadline
-fsck.repair=yes
 rootwait
-quiet
-init=/usr/lib/raspi-config/init_resize.sh
-splash
-plymouth.ignore-serial-consoles
+fbcon=map:10
+fbcon=font:ProFont6x11
+logo.nologo
```

The following are removed:

* `fsck.repair`, why!?
* `quiet`, fair enough
* `init=/usr/lib/raspi-config/init_resize.sh`, perhaps this is removed after first boot anyway?
* `splash`, if we're not using quiet, makes sense to get rid of the splash screen

The main functional changes appear to be:

* `fbcon=map:10`
* `fbcon=font:ProFont6x11`
* `console=serial0,115200` -> `console=ttyAMA0,1152001`

What do the `fbcon` lines do? Once again, the [linux kernel
docs](https://www.kernel.org/doc/Documentation/fb/fbcon.txt) come to the
rescue. `fbcon` stands for *framebuffer console* and is a console running on
top of a framebuffer device. What is a [framebuffer
device](https://en.wikipedia.org/wiki/Linux_framebuffer)? It's literally an
abstraction of the underlying framebuffer (a memory buffer that holds the
current video frame). So what are we configuring here? `map` specifies which
driver gets mapped to which console, the value is repeated until a string of 64
numbers is produced and the ttys starting from 1 ending at 64 are mapped onto
this string; no idea why this is necessary. The second option is self
explanatory, its simply setting the font of the framebuffer console.

It's unclear what the `console` line change is for. `serial0` is represents the
first available serial device, lets try replacing `ttyAMA0` with `serial0`, on
the RPi 2 I don't think it should make a difference. *reboots*, seems to work
fine, no difference. I think `ttyAMA0` will break on a RPi 3 since [`ttyAMA0`
will map to the bluetooth
UART](https://www.raspberrypi.org/documentation/configuration/uart.md).

Back to the device tree overlays. Let's understand that `tft35a.dtbo` file. How
does one make a device tree overlay? Hopefully that'll help us understand what
its doing. [Adafruit has a good tutorial on device overlays on the
beaglebone](https://learn.adafruit.com/introduction-to-the-beaglebone-black-device-tree/device-tree-overlays)

Here's what a device tree overlay sourcefile looks like:

```
/dts-v1/;
/plugin/;

/ {
    compatible = "ti,beaglebone", "ti,beaglebone-black";

    /* identification */
    part-number = "ADAFRUIT-SPI0";

    /* version */
    version = "00A0";

    fragment@0 {
        target = <&am33xx_pinmux>;
        __overlay__ {
            spi0_pins_s0: spi0_pins_s0 {
                pinctrl-single,pins = <
                  0x150 0x30 /* spi0_sclk, INPUT_PULLUP | MODE0 */
                  0x154 0x30 /* spi0_d0, INPUT_PULLUP | MODE0 */
                  0x158 0x10 /* spi0_d1, OUTPUT_PULLUP | MODE0 */
                  0x15c 0x10 /* spi0_cs0, OUTPUT_PULLUP | MODE0 */
                >;
            };
        };
    };

    fragment@1 {
        target = <&spi0>;
        __overlay__ {
             #address-cells = <1>;
             #size-cells = <0>;

             status = "okay";
             pinctrl-names = "default";
             pinctrl-0 = <&spi0_pins_s0>;

             spidev@0 {
                 spi-max-frequency = <24000000>;
                 reg = <0>;
                 compatible = "spidev";
             };
             spidev@1 {
                 spi-max-frequency = <24000000>;
                 reg = <1>;
                 compatible = "spidev";
             };
        };
    };
};
```

It is compiled with `dtc`, turns out you can also decompile `dtb` files back to
`dts` (source overlay) files; cool! Let's do that with ours.

```bash
$ dtc -O dts -o tft35a.dts -I dtb /boot/overlays/tft35a.d
tft35a.dts: Warning (unit_address_vs_reg): Node /fragment@0 has a unit name, but no reg property
tft35a.dts: Warning (unit_address_vs_reg): Node /fragment@0/__overlay__/spidev@0 has a unit name, but no reg property
tft35a.dts: Warning (unit_address_vs_reg): Node /fragment@0/__overlay__/spidev@1 has a unit name, but no reg property
tft35a.dts: Warning (unit_address_vs_reg): Node /fragment@1 has a unit name, but no reg property
tft35a.dts: Warning (unit_address_vs_reg): Node /fragment@2 has a unit name, but no reg property
```

Here it the overlay source (decompiled):

```
/dts-v1/;

/ {
        compatible = "brcm,bcm2835", "brcm,bcm2708", "brcm,bcm2709";

        fragment@0 {
                target = <0xdeadbeef>;

                __overlay__ {
                        status = "okay";

                        spidev@0 {
                                status = "disabled";
                        };

                        spidev@1 {
                                status = "disabled";
                        };
                };
        };

        fragment@1 {
                target = <0xdeadbeef>;

                __overlay__ {

                        tft35a_pins {
                                brcm,pins = <0x11 0x19 0x18>;
                                brcm,function = <0x0 0x0 0x0>;
                                linux,phandle = <0x1>;
                                phandle = <0x1>;
                        };
                };
        };

        fragment@2 {
                target = <0xdeadbeef>;

                __overlay__ {
                        #address-cells = <0x1>;
                        #size-cells = <0x0>;

                        tft35a@0 {
                                compatible = "ilitek,ili9486";
                                reg = <0x0>;
                                pinctrl-names = "default";
                                pinctrl-0 = <0x1>;
                                spi-max-frequency = <0xf42400>;
                                txbuflen = <0x8000>;
                                rotate = <0x5a>;
                                bgr = <0x0>;
                                fps = <0x1e>;
                                buswidth = <0x8>;
                                regwidth = <0x10>;
                                reset-gpios = <0xdeadbeef 0x19 0x0>;
                                dc-gpios = <0xdeadbeef 0x18 0x0>;
                                debug = <0x0>;
                                init = <0x10000b0 0x0 0x1000011 0x20000ff 0x100003a 0x55 0x1000036 0x28 0x10000c2 0x44 0x10000c5 0x0 0x0 0x0 0x0 0x10000e0 0xf 0x1f 0x1c 0xc 0xf 0x8 0x48 0x98 0x37 0xa 0x13 0x4 0x11 0xd 0x0 0x10000e1 0xf 0x32 0x2e 0xb 0xd 0x5 0x47 0x75 0x37 0x6 0x10 0x3 0x24 0x20 0x0 0x10000e2 0xf 0x32 0x2e 0xb 0xd 0x5 0x47 0x75 0x37 0x6 0x10 0x3 0x24 0x20 0x0 0x1000036 0x28 0x1000011 0x1000029>;
                                linux,phandle = <0x2>;
                                phandle = <0x2>;
                        };

                        tft35a-ts@1 {
                                compatible = "ti,ads7846";
                                reg = <0x1>;
                                spi-max-frequency = <0x1e8480>;
                                interrupts = <0x11 0x2>;
                                interrupt-parent = <0xdeadbeef>;
                                pendown-gpio = <0xdeadbeef 0x11 0x0>;
                                ti,x-plate-ohms = [00 3c];
                                ti,pressure-max = [00 ff];
                                linux,phandle = <0x3>;
                                phandle = <0x3>;
                        };
                };
        };

        __overrides__ {
                speed = <0x2 0x7370692d 0x6d61782d 0x66726571 0x75656e63 0x793a3000>;
                txbuflen = [00 00 00 02 74 78 62 75 66 6c 65 6e 3a 30 00];
                rotate = [00 00 00 02 72 6f 74 61 74 65 3a 30 00];
                fps = [00 00 00 02 66 70 73 3a 30 00];
                bgr = [00 00 00 02 62 67 72 3a 30 00];
                debug = <0x2 0x64656275 0x673a3000>;
                swapxy = <0x3 0x74692c73 0x7761702d 0x78793f00>;
        };

        __symbols__ {
                tft35a_pins = "/fragment@1/__overlay__/tft35a_pins";
                tft35a = "/fragment@2/__overlay__/tft35a@0";
                tft35a_ts = "/fragment@2/__overlay__/tft35a-ts@1";
        };

        __fixups__ {
                spi0 = "/fragment@0:target:0", "/fragment@2:target:0";
                gpio = "/fragment@1:target:0", "/fragment@2/__overlay__/tft35a@0:reset-gpios:0", "/fragment@2/__overlay__/tft35a@0:dc-gpios:0", "/fragment@2/__overlay__/tft35a-ts@1:interrupt-parent:0", "/fragment@2/__overlay__/tft35a-ts@1:pendown-gpio:0";
        };

        __local_fixups__ {
                fixup = "/fragment@2/__overlay__/tft35a@0:pinctrl-0:0", "/__overrides__:speed:0", "/__overrides__:txbuflen:0", "/__overrides__:rotate:0", "/__overrides__:fps:0", "/__overrides__:bgr:0", "/__overrides__:debug:0", "/__overrides__:swapxy:0";
        };
};
```

OK, a little overwhelming, is there a real source file we can use? [`fbtft`
have some](https://github.com/notro/fbtft/tree/master/dts/overlays/rpi) for
other screens. It looks like this mostly defines properties of the LCD
and touch layer. Let's step back up the stack.

### X11

Two files are added to `/etc/X11/xorg.conf.d/` to configure the X11 display
server.

* `99-calibration.conf`
* `99-fbturbo.conf`

The touch layer configuration is fairly straight forward:

```
Section "InputClass"
        Identifier      "calibration"
        MatchProduct    "ADS7846 Touchscreen"
        Option  "Calibration"   "3936 227 268 3880"
        Option  "SwapAxes"      "1"
EndSection
```

It matches the `ADS7846` device and pre-calibrates it whilst also
swapping X/Y axes (so X becomes Y and vica versa).

```
Section "Device"
        Identifier      "Allwinner A10/A13/A20 FBDEV"
        Driver          "fbturbo"
        Option          "fbdev" "/dev/fb1"

        Option          "SwapbuffersWait" "true"
EndSection
```

This Xorg config specifies the driver to use for the panel;
[`fbturbo`](https://github.com/ssvb/xf86-video-fbturbo), the generally
preferred framebuffer driver (over
[`fbdev`](https://www.x.org/releases/current/doc/man/man4/fbdev.4.xhtml).
`fbturbo` is actually based off of `fbdev` so acts as a strict superset, it
adds additional optimisations for ARM platforms, in the README it lists the raspberry pi:

> Hardware accelerated window moving/scrolling on Raspberry Pi (using the
> BCM2835 DMA Controller)

Shame it doesn't seem to be that quicker, maybe its the SPI interface
bottlenecking the display updates?

The `inittab` spawns a `getty` terminal instance on `ttyAMA0` at 115200 baud.

Can we speed things up and get a higher refresh rate? 

Looks like [some
people](https://www.reddit.com/r/raspberry_pi/comments/4cq7cc/refresh_rate_on_pitft_and_other_gpiodriven/)
are increasing the speed of the SPI clock:

```
# config.txt
dtoverlay=pitft28r,rotate=90,speed=80000000,fps=60
```

Let's try adding `speed=80000000` to the `dtoverlay=tft35a` clause in
`config.txt`... whitescreen of death. How about with `fps=60` too?

Let's have a look at that device tree overlay file, does it list any options
about `fps` or `speed` in it? These are the defaults we are trying to override.
Here's the fragment of interest:

```
tft35a@0 {
        compatible = "ilitek,ili9486";
        reg = <0x0>;
        pinctrl-names = "default";
        pinctrl-0 = <0x1>;
        spi-max-frequency = <0xf42400>;
        txbuflen = <0x8000>;
        rotate = <0x5a>;
        bgr = <0x0>;
        fps = <0x1e>;
        buswidth = <0x8>;
        regwidth = <0x10>;
        reset-gpios = <0xdeadbeef 0x19 0x0>;
        dc-gpios = <0xdeadbeef 0x18 0x0>;
        debug = <0x0>;
        init = <0x10000b0 0x0 0x1000011 0x20000ff 0x100003a 0x55 0x1000036 0x28 0x10000c2 0x44 0x10000c5 0x0 0x0 0x0 0x0 0x10000e0 0xf 0x1f 0x1c 0xc 0xf 0x8 0x48 0x98 0x37 0xa 0x13 0x4 0x11 0xd 0x0 0x10000e1 0xf 0x32 0x2e 0xb 0xd 0x5 0x47 0x75 0x37 0x6 0x10 0x3 0x24 0x20 0x0 0x10000e2 0xf 0x32 0x2e 0xb 0xd 0x5 0x47 0x75 0x37 0x6 0x10 0x3 0x24 0x20 0x0 0x1000036 0x28 0x1000011 0x1000029>;
        linux,phandle = <0x2>;
        phandle = <0x2>;
};
```

The device is an Ilitek ILI9486, cool, that's good to know, turns out `fbtft`
supports this :) Hang on, we might already even be using it:

```
$ dmesg | grep -i tft
[   25.610311] fbtft: module is from the staging directory, the quality is unknown, you have been warned.
[   25.630096] fbtft_of_value: regwidth = 16
[   25.630109] fbtft_of_value: buswidth = 8
[   25.630119] fbtft_of_value: debug = 0
[   25.630127] fbtft_of_value: rotate = 90
[   25.630135] fbtft_of_value: fps = 60
[   25.630142] fbtft_of_value: txbuflen = 32768
```

We can also [list supported
devices](https://github.com/notro/fbtft/wiki/fbtft_device#supported-devices):

```
$ sudo modprobe fbtft_device name=list; dmesg | tail -30
[  406.017439] fbtft_device: ili9481
[  406.017443] fbtft_device: itdb24
[  406.017446] fbtft_device: itdb28
[  406.017449] fbtft_device: itdb28_spi
[  406.017452] fbtft_device: mi0283qt-2
[  406.017455] fbtft_device: mi0283qt-9a
[  406.017458] fbtft_device: mi0283qt-v2
[  406.017461] fbtft_device: nokia3310
[  406.017464] fbtft_device: nokia3310a
[  406.017467] fbtft_device: nokia5110
[  406.017470] fbtft_device: piscreen
[  406.017473] fbtft_device: pitft
[  406.017476] fbtft_device: pioled
[  406.017480] fbtft_device: rpi-display
[  406.017483] fbtft_device: s6d02a1
[  406.017486] fbtft_device: sainsmart18
[  406.017489] fbtft_device: sainsmart32
[  406.017492] fbtft_device: sainsmart32_fast
[  406.017495] fbtft_device: sainsmart32_latched
[  406.017499] fbtft_device: sainsmart32_spi
[  406.017502] fbtft_device: spidev
[  406.017505] fbtft_device: ssd1331
[  406.017508] fbtft_device: tinylcd35
[  406.017511] fbtft_device: tm022hdh26
[  406.017514] fbtft_device: tontec35_9481
[  406.017518] fbtft_device: tontec35_9486
[  406.017521] fbtft_device: upd161704
[  406.017524] fbtft_device: waveshare32b
[  406.017527] fbtft_device: waveshare22
[  406.017530] fbtft_device:
```

Closest to the seems to be `ili9481`, not quite `ILI9486`, googling the two
together yields an Aliexpress page selling the 9481 claiming comptability with
the 9486. Let's try that driver then! First commenting out the `dtoverlay`
clause in `config.txt` then rebooting to use `modprobe` to load the driver.

```
$ sudo modprobe fbtft_device name=ili9481
```

The screen goes black, woohoo! That means the display has been initialised
(according to the fbtft docs). `dmesg` output:

```
[   37.977381] fbtft: module is from the staging directory, the quality is unknown, you have been warned.
[   37.983798] fbtft_device: module is from the staging directory, the quality is unknown, you have been warned.
[   37.985388] spidev spi0.0: spidev spi0.0 500kHz 8 bits mode=0x00
[   37.985421] spidev spi0.1: spidev spi0.1 500kHz 8 bits mode=0x00
[   37.985470] bcm2708_fb soc:fb: soc:fb id=-1 pdata? no
[   37.985519] spidev spi0.0: Deleting spi0.0
[   37.986706] fbtft_device: GPIOS used by 'ili9481':
[   37.986719] fbtft_device: 'reset' = GPIO25
[   37.986738] fbtft_device: 'dc' = GPIO24
[   37.986744] fbtft_device: 'led' = GPIO22
[   37.986765] spidev spi0.1: spidev spi0.1 500kHz 8 bits mode=0x00
[   37.986779] spi spi0.0: fb_ili9481 spi0.0 32000kHz 8 bits mode=0x00
[   38.012675] fb_ili9481: module is from the staging directory, the quality is unknown, you have been warned.
[   38.324103] graphics fb1: fb_ili9481 frame buffer, 320x480, 300 KiB video memory, 4 KiB DMA buffer memory, fps=20, spi0.0 at 32 MHz
```

Trying to launch Xorg:

```
$ FRAMEBUFFER=/dev/fb1 startx
X.Org X Server 1.19.2
Release Date: 2017-03-02
X Protocol Version 11, Revision 0
Build Operating System: Linux 4.9.35-v7+ armv7l Raspbian
Current Operating System: Linux raspberrypi 4.9.41-v7+ #1023 SMP Tue Aug 8 16:00:15 BST 2017 armv7l
Kernel command line: bcm2708_fb.fbwidth=640 bcm2708_fb.fbheight=480 bcm2708_fb.fbswap=1 vc_mem.mem_base=0x3ec00000 vc_mem.mem_size=0x40000000  dwc_otg.lpm_enable=0 console=tty1 console=ttyAMA0,115200 root=/dev/mmcblk0p2 rootfstype=ext4 elevator=deadline rootwait fbcon=map:10 fbcon=font:ProFont6x11 logo.nologo
Build Date: 20 July 2017  09:07:00AM
xorg-server 2:1.19.2-1+deb9u1+rpi1 (https://www.debian.org/support)
Current version of pixman: 0.34.0
        Before reporting problems, check http://wiki.x.org
        to make sure that you have the latest version.
Markers: (--) probed, (**) from config file, (==) default setting,
        (++) from command line, (!!) notice, (II) informational,
        (WW) warning, (EE) error, (NI) not implemented, (??) unknown.
(==) Log file: "/home/pi/.local/share/xorg/Xorg.0.log", Time: Sun Sep 17 19:34:57 2017
(==) Using config directory: "/etc/X11/xorg.conf.d"
(==) Using system config directory "/usr/share/X11/xorg.conf.d"
(EE)
Fatal server error:
(EE) parse_vt_settings: Cannot open /dev/tty0 (Permission denied)
(EE)
(EE)
Please consult the The X.Org Foundation support
         at http://wiki.x.org
 for help.
(EE) Please also check the log file at "/home/pi/.local/share/xorg/Xorg.0.log" for additional information.
(EE)
(EE) Server terminated with error (1). Closing log file.
xinit: giving up
xinit: unable to connect to X server: Connection refused
xinit: server error
Couldn't get a file descriptor referring to the console
```

Not sure why it's trying to open /dev/tty0, `sudo FRAMEBUFFER=/dev/fb1 startx`
does start an X11 session! The display is portrait and the colours look all
wrong, I think its a BGR/RGB ordering issue.

![Weird colours](/media/img/raspberry-pi/elegoo-tft/colour-problems.png)

According to [FBTFT: boot
console](https://github.com/notro/fbtft/wiki/Boot-console), `fbcon=map:10`
specifies that the console should be output to the display. 

Let's unload and reload the `fbtft_device` module to try and fix the colour issue:

```
$ sudo modprobe -r fbtft_device && sudo modprobe --first-time fbtft_device name=ili9481 bgr=1
```

I can see part of a flashing cursor! Cool. `sudo startx` caused the device to
hang, rebooting again.

Loading `fbtft_device` with `debug=1` this time to have a look at refresh rate timings

```
[  168.718299] fbtft_device: module is from the staging directory, the quality is unknown, you have been warned.
[  168.719783] spidev spi0.0: spidev spi0.0 500kHz 8 bits mode=0x00
[  168.719805] spidev spi0.1: spidev spi0.1 500kHz 8 bits mode=0x00
[  168.719846] bcm2708_fb soc:fb: soc:fb id=-1 pdata? no
[  168.719890] spidev spi0.0: Deleting spi0.0
[  168.730169] fbtft_device: GPIOS used by 'ili9481':
[  168.730187] fbtft_device: 'reset' = GPIO25
[  168.730194] fbtft_device: 'dc' = GPIO24
[  168.730200] fbtft_device: 'led' = GPIO22
[  168.730221] spidev spi0.1: spidev spi0.1 500kHz 8 bits mode=0x00
[  168.730235] spi spi0.0: fb_ili9481 spi0.0 32000kHz 8 bits mode=0x00
[  168.747999] fb_ili9481: module is from the staging directory, the quality is unknown, you have been warned.
[  168.750410] fb_ili9481 spi0.0: fbtft_request_gpios: 'reset' = GPIO25
[  168.750442] fb_ili9481 spi0.0: fbtft_request_gpios: 'dc' = GPIO24
[  168.750466] fb_ili9481 spi0.0: fbtft_request_gpios: 'led' = GPIO22
[  169.006923] graphics fb1: fb_ili9481 frame buffer, 320x480, 300 KiB video memory, 4 KiB DMA buffer memory, fps=20, spi0.0 at 32 MHz
```

Interesting, `reset` and `led` look incorrect, I think `reset` should be `22`
according to the pin definitions in the informational PDF on the CD. Not sure
which pin is LED though.

Starting an X11 session on `vt1` caused the display to light up with a mirrored
terminal!

![A mirrored terminal](/media/img/raspberry-pi/elegoo-tft/mirrored.png)

How do we mirror it so that it appears correctly?

```
$ sudo modprobe -r fbtft_device && sudo modprobe --first-time fbtft_device  name=ili9481 debug=1 rotate=90 bgr=1
```

Produces something that looks reasonable

![A happier terminal](/media/img/raspberry-pi/elegoo-tft/final-success.png)

Oops, made it hang again, it doesn't like repeated `sudo startx` invocations.

Now to make it actually show an xserver rather than running one to show the
terminal! The [`fbtft` wiki](https://github.com/notro/fbtft/wiki) suggest using
`con2fbmap` to map a tty to a framebuffer. Trying `fbcon2fbmap 1 1` didn't
produce any results so I tried:

```
$ fb=1; for tty in {1..10}; do echo "$tty to fb $fb"; con2fbmap $tty $fb; sleep 1; done
1 to fb 1
2 to fb 1
3 to fb 1
4 to fb 1
5 to fb 1
6 to fb 1
7 to fb 1
8 to fb 1
9 to fb 1
10 to fb 1
$ fb=0; for tty in {1..10}; do echo "$tty to fb $fb"; con2fbmap $tty $fb; sleep 1; done
1 to fb 0
2 to fb 0
3 to fb 0
4 to fb 0
5 to fb 0
6 to fb 0
7 to fb 0
8 to fb 0
9 to fb 0
10 to fb 0
```

When `con2fbmap 0 7` was run the blinking cursor on the screen disappeared
suggesting I was already displaying tty7 on `/dev/fb1`. Plugging in a keyboard
and spamming the keys didn't yield any characters on the display. I wonder if
the `inittab` changes have messed things up?

Let's try adding the `fbtft_device` options to the `/boot/config.txt` and see
how things go.

Found an [excellent
post](https://www.raspberrypi.org/forums/viewtopic.php?t=111817#p1041032) on
configuring these screens. Apparently `fbtft` is being transitioned *into* the kernel
and lots has changed since then... 

Not sure whether continuing down the `fbtft` approach is worth it, the device
overlay must be using the [linux kernel
driver](https://github.com/torvalds/linux/tree/master/drivers/staging/fbtft)
anyway... going to focus on trying to speed up the LCD now.

There's a `pitft35-resistive` overlay in `/boot/overlays` that I thought was
worth a punt, but booted up with a white screen, probably a different
controller.

One of the helpful commands from the forum post was `vcdbg log msg` to get the
videocore debug logs

Finally I've got debug logs in `dmesg` by adding `dtparam=debug=7` to `config.txt`.
Here's what the logs look like:

```
[   44.554902] fb_ili9486 spi0.0: Display update: 1792 kB/s, fps=4
[   44.756564] fb_ili9486 spi0.0: fbtft_update_display(start_line=304, end_line=319)
[   44.756591] fb_ili9486 spi0.0: fbtft_write_reg16_bus8: 002a 0000 0000 0001 00df
[   44.756610] fb_ili9486 spi0.0: fbtft_write_spi(len=2): 00 2a
[   44.756678] fb_ili9486 spi0.0: fbtft_write_spi(len=8): 00 00 00 00 00 01 00 df
[   44.756715] fb_ili9486 spi0.0: fbtft_write_reg16_bus8: 002b 0001 0030 0001 003f
[   44.756729] fb_ili9486 spi0.0: fbtft_write_spi(len=2): 00 2b
[   44.756756] fb_ili9486 spi0.0: fbtft_write_spi(len=8): 00 01 00 30 00 01 00 3f
[   44.756786] fb_ili9486 spi0.0: fbtft_write_reg16_bus8: 002c
[   44.756798] fb_ili9486 spi0.0: fbtft_write_spi(len=2): 00 2c
[   44.756824] fb_ili9486 spi0.0: fbtft_write_vmem16_bus8(offset=291840, len=15360)
[   44.756917] fb_ili9486 spi0.0: fbtft_write_spi(len=15360): 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ...
[   44.764916] fb_ili9486 spi0.0: Display update: 1792 kB/s, fps=4
```

FPS=4!? That sounds bad, lets try overriding that in `config.txt` with
`fps=20`, nope still `fps=4` in the logs.

Fiddling with the `speed` param with `fps=30`

| `speed`  | Result                           | Display update speed (kB/s) |
|----------+----------------------------------+-----------------------------|
| 16000000 | Colours correct, Tolerable speed |                             |
| 20000000 | Colours correct                  | 2032                        |
| 24000000 | Colours correct                  | 2325                        |
| 32000000 | Colour corruption, Good speed    |                             |

[Adafruit](https://learn.adafruit.com/adafruit-pitft-28-inch-resistive-touchscreen-display-raspberry-pi/faq#faq-11)
has a good post on the `speed` parameter and overclocking

**Conclusion: These SPI driven TFT screens suck, don't bother with them as they
all run far too slow to be useful (unless its the expensive Tontec one, might
as well get an official 7" screen).**


## Elegoo 3.5" 480x230 TFT Technical Details

The screen ships with a little CD with some documentation on, frustratingly
this is hard to find anywhere else on the internet, so here it is reproduced
for my future benefit when I lose the CD/don't have a CD drive to hand
(seriously, who has CD drives in there laptop any more!?)

* LCD panel: [Ilitek ILI9486](http://www.displayfuture.com/Display/datasheet/controller/ILI9486L.pdf)
* Touch layer: ADS7846
* Touch controller: XPT2046



| Pin                            | Symbol           | Description                                                  |
|--------------------------------+------------------+--------------------------------------------------------------|
| 1, 17                          | `3.3V`           | + Power rail                                                 |
| 2, 4                           | `5V`             | + Power rail                                                 |
| 3, 5, 7, 8, 10, 12, 13, 15, 16 | `NV`             | NC                                                           |
| 6, 9, 14, 20, 25               | `GND`            | Ground                                                       |
| 11                             | `TP_IRQ`         | Touch panel interrupt, pulled low during touch               |
| 18                             | `LCD_RS`         | LCD instruction control, Instruction/Data register selection |
| 19                             | `LCD_SI/TP_SI`   | SPI data input of both LCD & touch panel                     |
| 21                             | `TP_S0`          | SPI data output of touch panel                               |
| 22                             | `RST`            | Reset                                                        |
| 23                             | `LCD_SCK/TP_SCK` | SPI clock for both LCD & touch panel                         |
| 24                             | `LCD_CS`         | LCD chip select (active low)                                 |
| 26                             | `TP_CS`          | Touch panel chip select (active low)                         |



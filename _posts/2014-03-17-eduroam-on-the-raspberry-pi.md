---
layout: post
title: "Eduroam on the raspberry pi"
---

For far too long have I not documented the process of getting to connected to
eduroam with a raspberry pi. This time I endeavour to document the process.`

The general process of getting up and running with wireless (on the command
line) on Raspbian is as follows:

1. Disable network service
2. Write a `wpa_supplicant` configuration file with your username and password.
3. Connect to the wireless network using `wpa_supplicant`
4. Request an IP address with `dhclient`.

# Disable network service
Raspbian's network service needs to be stopped to connect using the method
we're going to use. To do this run 

    sudo service networking stop

# Connect using wpa_supplicant

I'm at Bristol university where our eduroam network uses PEAP or TTLS for
authentication, if you're at a different university this may well be different
and you'll need to change the `wpa_supplicant` file accordingly

```
network={
	# --- MUST CONFIGURE THE FOLLOWING THREE OPTIONS --

	# The 'identity' is the username actually used for authentication.
	# This must be your Bristol username, all lowercase.
        identity="ab1234"

	# Your normal Bristol password (so make sure the permissions on
	# your wpa_supplicant config file are not world readable!)
        password="myUOBpassword"

	# CA cert from here:
    # https://www.wireless.bris.ac.uk/certs/eaproot/uob-net-ca.pem
	# Change the path to where you downloaded the file
        ca_cert="/etc/ssl/certs/uob-net-ca.pem"

	# --- ONLY CHANGE BELOW IF YOU ARE NOT A MEMBER --
	# --- OF THE UNIVERSITY OF BRISTOL, UK          --

	# Bristol supports PEAP and TTLS.
        eap=PEAP TTLS

	# The 'anonymous_identity' is the identity used for routing
	# the authentication to Bristol. It must end with '@bris.ac.uk'
	# or '@bristol.ac.uk'. It must be all lowercase. If you have 
	# anything preceding the @ it must be all lowercase letters or 
	# a hyphen (no spaces, punctuation etc) 
	# e.g. "wireless-user@bristol.ac.uk" would be ok
        anonymous_identity="@bristol.ac.uk"

	# Bristol use MS-CHAPv2 as the inner authentication scheme,
	# with the traditional label
	phase1="peaplabel=0"
	phase2="auth=MSCHAPV2"

	# Set priority to a big number
	priority=999

	# --- DONT CHANGE THE REST OF THIS BLOCK --

	# Enable this network block
	disabled=0

	# eduroam please
        ssid="eduroam"

	# SSID should be broadcast, so don't scan.
	scan_ssid=0

	# Infrastructure mode
	mode=0

	# WPA/WPA2 require OPEN
	auth_alg=OPEN

	# WPA and WPA2 (RSN) are both used for eduroam 
	# (depending on which organisation you are at)
	# In the future 'WPA' can be removed (WPA2 only).
	proto=WPA RSN

	# CCMP (AES) is stronger, but some organisations use TKIP.
	# In the future 'TKIP' can be removed.
	pairwise=CCMP TKIP

	# Use EAP
        key_mgmt=WPA-EAP

	# Use PMKSA caching
        proactive_key_caching=1

}
```
Thanks to
[wirless.bris.ac.uk](http://www.wireless.bris.ac.uk/eduroam/instructions/go-wpasup/) for the file!

Run `wpa_supplicant`: 

    sudo wpa_supplicant -i wlan0 -c /path/to/wpa_supplicant.conf -B

You'll also need the PEM file `uob-net-ca.pem` to put into `/etc/ssl/certs/`
which is located at
[https://www.wireless.bris.ac.uk/certs/eaproot/uob-net-ca.pem](https://www.wireless.bris.ac.uk/certs/eaproot/uob-net-ca.pem)

Problems you may encounter at this stage include:

* The certificate being invalid as the raspberry pi's time is set to a time
  before the certificate is valid (run wpa_supplicant with the `-dd` flag for
  verbose debugging).
* You're as thick as me and you accidentally rename the certificate
* Something else has control of the wireless interface preventing you from
  connecting.


# Request an IP address

Once you've connected to eduroam which you can verify by running `iwconfig`. You
should now request an ip address with the command 

    sudo dhclient wlan0

To verify that you have got an ip address run `ifconfig` and make sure your
wireless interface (usually wlan0) has been assigned an address.

You should now have a wireless connection!

---
layout: post
title: "How to backup a linux system"
---
I've had trouble backing up linux systems, my  main issue seemed to be ignorance
of how linux systems are booted, what needs replacing after a screw up and
finally how to replace what needs replacing with (relative) ease.

# Filesystem
Here's the root of my Arch system.

{% highlight console %}
$ ls /
bin  boot  dev  etc  home  lib  media  mnt  opt  proc  root  run  sbin  srv
sys  tmp  usr  var
{% endhighlight %}

All these folders need replicating, though some folder's contents are
generated at book and so backing up the files would be futile; With these
folders, we just want to recreate the actual folder and leave them empty,
everything else we want to back up in entirety. 

To backup the root directory in this fashion
[rdiff-backup](http://rdiff-backup.nongnu.org/) can be employed. `rdiff-backup`
first takes an initial backup of a directory, in our case, the root directory.
For each successive backup after the initial backup, `patch` files are stored
recording the difference between the original files and the newest files (or
perhaps the most recent backup, I haven't delved into it's inner workings). This
type of backup allows you to restore your system back to any previous backup in
time with minimal space concerns. When it comes to restoring the root directory
`rdiff-backup` simply applies the patch files to the original directory it
copied and thus restores your backup to the point in time which you wish to
restore.

Now you understand how `rdiff-backup` functions, we can get into a meaty
example... 

I use a script to keep my `crontab` clean and easily understandable:

{% highlight bash %}
#!/bin/bash
[[ $# -ge 2 ]] || { echo "Need at least 2 arguments: src and dest, the rest are passed to rdiff-backup" ; exit 3 ; }
[[ $EUID -eq 0 ]] || { echo "Must be root user to run this script" ; exit 2 ; }
[[ -d /mnt/backup/backups ]] || { mount /mnt/backup || exit 3 ; }

SOURCE="$1"
DEST="$2"
# The earlier the include or exclude, the higher the precedence
shift 2
rdiff-backup "$@" "$SOURCE" "$DEST" 
{% endhighlight %}

I'm just beginning to start using bash scripts on my system, so please feel free
to point out any grievous errors.

This script checks that my backup drive is mounted, that it's being run as root,
that the necessary number of arguments are passed to it and then proceeds to run
`rdiff-backup`. 


# 

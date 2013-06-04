---
layout: post
title: "Learning git"
description: "Beginner's notes on learning git"
category: 
tags: []
---

I picked up ['Pro Git'](http://git-scm.com/book) to learn how to use the DVCS to
try and keep a little
order to my projects. As I read through the first few chapters I kept a few notes of commands that I
didn't already know. I'd definitely recommend the book, it's well written and
available free on the authors website.

With git I also intend to document my progress learning TDD, I'll commit after
each test written.

I've taken the liberty of writing down some commands I hadn't already
encountered in my (very limited) previous usage of `git`. These commands are roughly in the order I encountered them in the book so they
should get increasingly more complicated.

{% highlight sh %}
# Basic commands
git init # initialize repository
git add <filename> # add filename to the staging area
git commit # save staging area to commit
git status # current status of files in the repository
git diff <filename> # view the differences between working dir and staged files
    git mv <filename> <newfilename> # handles moving files easily
git commit --amend # Add current staged files to last commit (good if you forget to stage files)
    git log # view commit history
    git rm --cached <filename> # remove commit from staging area
git commit -a # add and commit a file (skip staging area)
    git log --pretty=format:"formatting parameters" # commit history in your format, check man pages for help
{% endhighlight %}

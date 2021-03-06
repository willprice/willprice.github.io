---
layout: post
title: "Choosing a target platform"
---

I'm currently working on a project with my mentor. We first chose the simplest user
story to work on that didn't depend on any other user stories.

> Given a list of players for all games
>
> When a game is selected
>
> Then the list is filtered to only include players 
> capable of playing that game.

The idea of the platform is to allow players to write AI programs that are able
to play games (e.g. Noughts and crosses, Chess, Hangman...). Players can challenge
other players to games in which their AIs play against each other.

Games are held on a server to eliminate issues of cheating that may
occur if the games were held client-side. I chose Python and Django to
implement the necessary code server-side to pass the story. Initially
we had intended to have a web interface in which games were played,
however evaluating the TDD and acceptance testing frameworks in
javascript was less than favourable. So I instead had to
look into other ways to pass the client-side part of the user story
which leads us onto the topic of this post: How do you choose a target
platform?

There are so many platforms you can develop for: Android, iOS, the web, Windows,
OS X, Linux, GTK, QT, KDE, Cocoa, etc. Ideally you choose the platform that
maximises the number of users that will be able to use your system, minimise the
time taken to develop and maximise the user experience. Unfortunately no silver
bullet exists, and so you have to make trade-offs on each of these points. 

If you develop for the web you maximise your audience at the cost of having to
check your website works in a hundred different browsers at hundreds of
different resolutions using a language that was designed in 10 days with no
built-in support for modules, which requires at least 10 different libraries to
program at a sane level of abstraction.

If you develop for iOS, then you severely restrict your audience to those owning
i-products. Android has a larger user base, but then you have to deal with the
plethora of different devices that your application has to work well on.

You could still develop a desktop application for each major platform, but that
racks up large development costs. You could trade in part of your user
experience and develop in Java/Swing so that the application runs on all
platforms, but requires your users to download a 200MB language and wait 2-20
seconds for your application to start up every time. 

Since the target audience for our application is beginner developers such as
Raspberry Pi enthusiasts, then we'd better make sure our program runs well on
Linux (that, and I develop on Linux ;), but it should also at least run on
Windows since almost everybody uses it, and a large proportion of our target
audience will likely be using it. OS X shouldn't be too hard to support if we
require Windows and Linux compatibility. What technology can we choose to
develop for these platforms?

Well there are two groups:
- The web
- Cross platform languages (with cross platform GUIs)

I've already established that I'd like to avoid web development for
the time being. This leaves us with a cross platform language to
choose, and by cross platform I require that I don't have to
constantly think about platform incompatibilities, I want to leave
that up to libraries to handle. Since I've already developed the
server-side in Python, I'd like to keep the code base as homogeneous
as possible. Python is cross platform and has a decent selection of
good cross platform GUI toolkits (wxpython, tkinter). After looking
into some examples with both toolkits I'll decide which to use. Python
can also be quite easily be packaged into a executable that includes
the interpreter/VM in a reasonable size (< 20MB).

My mentor suggested Android as a target platform since it's programmed in Java,
a language he's an expert in, and we've both paired on lots of Java katas
before. I raised the point that this seems to fragment our user experience to
programming on a laptop/desktop and challenging on a phone/tablet, therefore
restricting our audience and making development harder (testing on devices). He
countered that we needn't have just one client, but that we need to push on and
develop some client to pass the acceptance test. I'm in two minds about this;
I'm not sure whether we should target Android for our first client since in my
eyes, a desktop client would be more useful to our target audience, and it means
programming in a different language which will surely duplicate some of the code
that was developed for the server. On the other hand I'm unsure how difficult
writing a GUI program in Python is going to be, if I come across unforeseen
issues then development might stall again, which we want to try and avoid in the
next month since we want to present what we've been doing at the BCS SPA
conference--It'd be good to have some MVP to show off.

---
layout: post
title: "Introduction to Jekyll"
description: "An introduction to the static site generator used to create this site"
category: Technology
tags: [Jekyll, Web]
---

I first encountered Jekyll through github pages. I read that all git repositories are passed through jekyll and if they are either a valid jekyll or html site then that site can be published through github pages. This was my first misconception that left me confused as I thought that Jekyll was some server side program that you processed some text files, although it is in a sense it isn't true to the real workflow using jekyll.

Jekyll is a program that generates a static html site from markdown pages using layouts you specify. I kind of like to think of it a control program that converts markdown to html, then structures that and runs a local http server so you can check out what your site looks like, finally you're left with a folder with your site in, you could setup your own website with the http root pointed at it, or upload it to github and enable github pages so that you can host it freely. This tutorial hopefully will give you a sense of jekyll works and what's what.

Install Jekyll and other programs to begin with:

      $ gem install jekyll rdiscount

This installs jekyll and rdiscount, *a markdown converter*. These programs are the utter basics we need to start playing around with jekyll, in a later guide I'll introduce some other programs.

Create a directory in which you're going to make your site:

      $ mkdir jekyll_site
      $ cd jekyll_site

Inside that folder we're going to create a folder called '_layouts', '_posts' and 'css', these will hold virtually everything we need for our site. The website will need an 'index.html', which is what jekyll will initially point at when someone visits the site, it is our homepage.

      $ mkdir _layouts _posts css
      $ touch index.html _layouts/default.html _layouts/post.html css/screen.css _config.yml

The layouts and homepage need to be created now before we can start writing anything in the _posts folder. In _layouts/default.html type:

    <!DOCTYPE HTML>
    <html>
      <head>
        <title>{{page.title}}</title>
      </head>
      <body>
        <h2>{{page.title}}</h2>
        <section>
        {{ content }}
        </section>
      </body>
    </html>
The parts of the file bound in {{ }} tags are [Liquid Tags](https://github.com/shopify/liquid/wiki/liquid-for-designers), they will be substituted by whatever variable is inserted into them, in this case we have 'page.title' which is the title of the page defined in the YAML preamble (we'll get to this in a minute) and 'content' which is a standard tag that is filled by the page content like index.html or a translated markdown post.

We need to do something similar in _layouts/post.html

      ---
      layout: default
      ---
      {{ content }}


In the top part of the file where the hyphens and the title are located are processed by Jekyll is [YAML Front Matter](https://github.com/mojombo/jekyll/wiki/liquid-extensions),this sets some variables like the layout to use, in this case default.html is used, content will be substituted by the post content.

Finally we need a homepage for our website which will be located in index.html, just something simple for the time being

      ---
      layout: default
      title: homepage
      ---

      <ul>
        ``{% for post in site.posts %}
        <li><a href="{{ post.url }}">{{ post.title }}</a></li>
        {% endfor %}``
      </ul>

Here we have another example of liquid extensions, this is a for loop. There is a standard array of all the posts in the site, we're looping through them and creating an unordered list of each one with links to their location attached to their titles.


Now we've created all the files we need to get up and running. You can type a test post with the title '2012-08-12-title.md' where 'title' is anything you want it to be separated with hyphens. Type this into it:

      ---
      title: test post
      --- 

      This is a post

And then run

      $ jekyll --server

This will run jekyll generating the site in html whilst also serving it at the address: 'localhost:4000'

{% highlight python %}
      import sys
      while x < 10:
          x += 1
{% endhighlight}

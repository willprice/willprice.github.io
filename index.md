---
layout: layout
title: Will Price
---

<h2>Posts</h2>
<ul class="posts">
  {% for post in site.posts %}
  <li><span>{{ post.date | date_to_string }}</span> &#8212; <a href="{{ post.url }}">{{ post.title }}</a></li>
  {% endfor %}
</ul>

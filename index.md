---
layout: layout
title: Will Price
---

<h2 style='border: none;'>Posts</h2>
<ul class="posts">
  {% for post in site.posts %}
  <li><span class="post-date">{{ post.date | date_to_string }}</span><a href="{{ post.url }}">{{ post.title }}</a></li>
  {% endfor %}
</ul>

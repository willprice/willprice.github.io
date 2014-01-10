---
layout: post
title: "LaTeX fails... and fixes!"
---

I thought it might be a good idea to brush up my LaTeX skills by writing my
maths homework in it... big mistake... lots of time wasted! I'm much more
informed on LaTeX now, so here's some of the things I struggled with in the
hopes it will help future me from spending hours figuring out how to put
multiple tables on one line!

## Referencing figures and tables
You must put the label *after the caption* in a figure or table:
{% highlight tex %}
\begin{table}
% Don't put labels before the caption, like here
    \begin{tabular}
        ...
    \end{tabular}
    \caption{A table of things}
    \label{table:things}
\end{table}
{% endhighlight %}

## Multiple tables on a single line
Use the `subcaption` package, this allows you to specify the width of subtables
and subfigures.

{% highlight tex %}
\begin{table}[h]
    \begin{subtable}[b]{1.3\linewidth}
      \centering
      \begin{tabular}{c|cccc}
        $\circ$ & $e$ & $a$ & $b$ & $c$ \\
        \hline
        $e$     & $e$ & $a$ & $b$ & $c$ \\
        $a$     & $a$ & $c$ & $e$ & $b$ \\
        $b$     & $b$ & $e$ & $c$ & $a$ \\
        $c$     & $c$ & $b$ & $a$ & $e$ \\
      \end{tabular}
      \caption{$Z_4$}
    \end{subtable}
    %replace \quad with a new line if you don't want it on the same line
    \quad
    \begin{subtable}[b]{0.4\linewidth}
      \centering
      \begin{tabular}{c|cc}\label{table:z_4}
        $\circ$ & $e$ & $c$ \\
        \hline

        $e$     & $e$ & $c$ \\
        $c$     & $c$ & $e$ \\
      \end{tabular}
      \caption{Only valid $Z_4$ subgroup: $Z_2$}
    \end{subtable}
    \caption{$Z_4$ and it's subgroup $Z_2$}
    \label{table:z_4}
\end{table}
{% endhighlight %}

## Specify the location of tables
`[specifier]` takes one of the following `{h,t,b,p}`

* `h` - Here
* `t` - Top
* `b` - Bottom
* `p` - Own page

These can be combined like `hbp`, close to the place in the text on it's own
separate page at the bottom

## Spacing and measures
* `\quad` - space
* `\linewidth` - width of page, use this with the `subtable` environment when
  you're setting the width of a subtable.

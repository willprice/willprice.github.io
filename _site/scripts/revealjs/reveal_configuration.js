// More info https://github.com/hakimel/reveal.js#configuration
Reveal.initialize({
  history: true,

  // More info https://github.com/hakimel/reveal.js#dependencies
  dependencies: [
    { src: '/scripts/revealjs/plugin/markdown/marked.js' },
    { src: '/scripts/revealjs/plugin/markdown/markdown.js' },
    { src: '/scripts/revealjs/plugin/notes/notes.js', async: true },
    { src: '/scripts/revealjs/plugin/highlight/highlight.js', async: true, callback: function() { hljs.initHighlightingOnLoad(); } }
  ]
});

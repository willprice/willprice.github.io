---
layout: post
title: "Testing client side javascript"
---

I've recently had to look at writing some client-side javascript for an
application I'm developing. Since I love testing, I had to have a look at what
testing framework I should use. Javascript is not Java, there are lots and lots
of testing frameworks. After browsing the most popular projects I decided on
using [Mocha](http://visionmedia.github.io/mocha/) to handle test running and
suite generation with [Chai](http://chaijs.com) which is used to provide a rich
library of assertions.

These tools can be run on the browser and manipulate the DOM to show outputs. I
personally think this method is quite ugly and slow so I looked into running
things headlessly. A few immediate choices came to mind:

* [Node.js](http://nodejs.org/)
* [PhantomJS](http://phantomjs.org/)
* [Rhino](https://developer.mozilla.org/en-US/docs/Rhino)

These projects all run javascript off the browser and hence some don't support
DOM manipulation (e.g. Rhino).

PhantomJS supports DOM manipulation which is quite a nice feature
if you are eventually going to run your javascript client-side.

Having recently used node for a university project, I thought I'd try something
else that isn't built on an asynchronous model since I found this made testing
quite difficult. In the end I chose PhantomJS as I running Rhino regularly
sounded quite unpleasant given the time it takes the JVM to start.


Mocha is well supported under PhantomJS and already has a [runner
availabe](https://github.com/metaskills/mocha-phantomjs). I'll give a few
examples of how to get all these libraries cooperating.

First up you'll need `node` installed to give you access to the `npm` package
manager. It seems like most js projects have adopted it as a package manager
irrespective of whether they target Node.js or the browser.

    $ sudo npm install -g mocha-phantomjs phantomjs

will pull in PhantomJS, Mocha and the PhantomJS Mocha runner that we'll use to
run our tests in the command line.

Start a new project somewhere and add a source and tests directory.
    
    $ mkdir tests src

Since we're PhantomJS we need an HTML page that will be run in the headless
browser, this is mainly just a shell that will include all the javascript code
that we wish to run. The advantage of using a platform like Node.js or Rhino
means you can skip this extra step, but then you also lose the ability to
perform DOM manipulation.

    $ touch tests.html

This file will be used to included all your test suites, this might get pretty
ugly/slow if you've got many and large test suites, but you can always break
them up, or you could use python and jinja2 to dynamically create HTML pages
based on the js files you have in your tests directory (I'm sure you could do
this in js as well, but I'm not really familiar with the ecosystem).

    $ cat > tests.HTML << EOF
    <html>
      <head>
        <meta charset="utf-8">
        <link rel="stylesheet" href="../node_modules/mocha/mocha.css" />
      </head>
      <body>
        <div id="mocha"></div>
        <script src="../node_modules/mocha/mocha.js"></script>
        <script src="../node_modules/chai/chai.js"></script>
        <script>
          mocha.ui('tdd');
          mocha.reporter('html');
          assert = chai.assert;
        </script>
        <script src="src/fibonacci.js"></script>
        <script src="tests/fibonacci"></script>
        <script>
          if (window.mochaPhantomJS) { mochaPhantomJS.run(); }
          else { mocha.run(); }
        </script>
      </body>
    </html>
    EOF    

This is just a simple document that will include the necessary libraries, setup
Mocha appropriately:

  * Import Mocha and Chai
  * Use the TDD interface instead of BDD
  * Use the reporter 'html', this allows us to run open the page with a
    browser and check out the results in there too. We'll specify a different
    reporter on the command line when developing code and running tests. 
  * Alias `chai.assert` as `assert` for nicer looking test code
  * Finally check whether the tests are being executed in PhantomJS and use the
    mochaPhantomJS runner if they are, otherwise execute Mocha directly.

Evidently this HTML has some dependencies that need to be installed before the
code can be run.

    $ npm install --save mocha chai

will install the necessary testing libraries and the `--save` flag will produce
a package.json file that can be distributed with your project for other users to
automate downloading dependencies.

The HTML sources `tests/test_file.js` which needs to be created, this is simply
an example test file:
    
    $ cat > tests/fibonacci.js << EOF
    suite('Recursive fibonacci tests', function() {
        test('fib(0) = 0', function() {
            assert.equal(0, fib(0));
        });
        test('fib(2) = 1', function() {
            assert.equal(1, fib(1));
        });
    });
    EOF

    $ cat > src/fibonacci.js << EOF
    function fib(n) {
        if (n < 2) { return n; }
        return fib(n - 1) + fib(n - 2);
    }
    EOF

Now everything is set up you can run your tests:

    $ mocha-phantomjs tests.html

Quite nice really. Look into Sinon.js for a nice mocking framework

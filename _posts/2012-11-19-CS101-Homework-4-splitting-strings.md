---
title: "CS101 Unit 4: Homework 4: Splitting Strings"
layout: post
---

I've been going through CS101 on Udacity to get a decent grounding in Python and some CS concepts. So far I've found it quite rewarding thanks to some rather challenging questions. This question in particular (Unit 4 homework, question 4) I found very difficult to crack and finally had to watch the answer video. I'll explain the question and how the solution is reached for those that didn't find the video particularly clear.

The question:

     # 1 Gold Star
     
     # The built-in <string>.split() procedure works
     # okay, but fails to find all the words on a page
     # because it only uses whitespace to split the
     # string. To do better, we should also use punctuation
     # marks to split the page into words.
     
     # Define a procedure, split_string, that takes two
     # inputs: the string to split and a string containing
     # all of the characters considered separators. The
     # procedure should return a list of strings that break
     # the source string up by the characters in the
     # splitlist.
     #
     # def split_string(source,splitlist)

There are also some examples and expected behaviour given:

     out = split_string("This is a test-of the,string separation-code!"," ,!-")
     print out
     #>>> ['This', 'is', 'a', 'test', 'of', 'the', 'string', 'separation', 'code']
     
     out = split_string("After  the flood   ...  all the colors came out.", " .")
     print out
     #>>> ['After', 'the', 'flood', 'all', 'the', 'colors', 'came', 'out']


Approaching the problem from a high level we can see that in essence we need produce a list of words (sets of characters that aren't members of `splitlist`) that are separated by splitting characters (as defined in `splitlist`). 

Let's define a list,`word_list`, that will hold all the words from source without the splitting characters present, each block of characters seperated by splitlist characters will be a new entry in `word_list`. We want to iterate through `source` adding characters to a string present in `word_list` until we hit upon a splitting character. At that point we want to skip to the next character and check whether that's also a splitting character, if it is, then skip to the next one and so on until we reach a word character (i.e. one not present in splitlist). Once we reach that new word character, we'll need to start a new entry in the word_list list otherwise we'll continue appending to the first word we found and therefore just end up with an list containing one element; a string containing all the words without any splitting characters in it.


Now we have a better of idea of the problem and how to implement the solution we can start writing code:

{% highlight py %}
def split_string(source,splitlist):
    word_list = []

    # Once we've filled word list, we'll want to return the list containing all the words
    return word_list
{% endhighlight %}

So we've got a skeleton function now, we know what parameters the function is going to take and the end result. We'll now add functionality that loops through `source` and check which characters are members of split list

{% highlight py %}
def split_string(source,splitlist):
    word_list = []

    for char in source:
        if char in splitlist:
            print "this char: " + str(char) + " is in splitlist"

    # Once we've filled word list, we'll want to return the list containing all the words
    return word_list

out = split_string("This is a test-of the,string separation-code!"," ,!-.")
print out
{% endhighlight %}

This code results in:

      this char:   is in splitlist
      this char:   is in splitlist
      this char:   is in splitlist
      this char: - is in splitlist
      this char:   is in splitlist
      this char: , is in splitlist
      this char:   is in splitlist
      this char: - is in splitlist
      this char: ! is in splitlist

We've got a code block that is executed when `char` is equal to a character from `splitlist`. We can now implement the code that will add the words to `word_list`. Remember that once we've added a word to `word_list` and have iterated over the splitting characters between the word just added and the word about to be added, a new list entry needs to be added otherwise we'll end up with one great list of words without spaces. First we'll acheive this unwanted behaviour as it's a step in the right direction, then we'll add checks to create new list entries splitting the words properly.

{% highlight py %}
def split_string(source,splitlist):
    word_list = ['']

    for char in source:
        if char in splitlist:
            print "this char: " + str(char) + " is in splitlist"
        else:
            word_list[-1] = word_list[-1] + char
    # Once we've filled word list, we'll want to return the list containing all the words
    return word_list

out = split_string("This is a test-of the,string separation-code!", " ,.!-")
print out
{% endhighlight %}

`word_list`s initialisation value has changed so that it contains an empty string, this will allow us to concatenate characters with it, otherwise an error would be raised if it was simply left empty. In our for loop there is a conditional that will now concatenate non-splitting characters with our string in `word_list`. This produces one big string inside the list, our code now has to be modified so that each word gets a new entry in the list.

To acheive the functionality above, we need to know when we get to splitting characters, we've already got a block of code that deals with this situation, it's simply printing lines at the moment, not doing anything useful, we'll change that so we know when we've reached a splitting character.


{% highlight py %}
def split_string(source,splitlist):
    word_list = ['']

    at_split = False
    for char in source:
        if char in splitlist:
            at_split = True
        else:
            at_split = False
            word_list[-1] = word_list[-1] + char
    # Once we've filled word list, we'll want to return the list containing all the words
    return word_list

out = split_string("This is a test-of the,string separation-code!", " ,.!-")
print out
{% endhighlight %}

Here we've intialised `at_split` outside of the for loop as it's going to be used in the else statement and hence has to be accessible by the if and else statements. This change hasn't affected the functionality of `split_string` yet, but it's a step in the right direction, we now have a variable that can be used to execute code blocks when an end of word is reached, which is the last step to reproducing the desired behaviour.


{% highlight py %}
def split_string(source,splitlist):
    word_list = ['']

    at_split = False
    for char in source:
        if char in splitlist:
            at_split = True
        else:
            if at_split:
                # We've now reached the start of the word, time to make a new element in the list
                word_list.append(char) # This creates a new element in the array with the value of 'char'
                # Reset at_split so no more elements are created until we reach a new word
                at_split = False
            else:
                # Char is not in splitlist, and we're not at the start of a word, so simply concatenate
                # char with the last entry in word_list
                word_list[-1] = word_list[-1] + char

    # Once we've filled word list, we'll want to return the list containing all the words
    return word_list

out = split_string("This is a test-of the,string separation-code!", " ,.!-")
print out
{% endhighlight %}

Finally, we have the behaviour, the code above prints:
      ['This', 'is', 'a', 'test', 'of', 'the', 'string', 'separation', 'code']

Mission accomplished.

I've also used Python Tutor's visualise program to show how the code is executed: [Visualised](http://goo.gl/GSRHJ). I found this helpful to understand what was happening as words were ending and new elements in the list were being created.

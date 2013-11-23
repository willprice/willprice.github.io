---
layout: post
title: "A little bit of UML pairing session"
---

Jason's video on the subject:
<iframe width="560" height="315" src="//www.youtube.com/embed/U7X6EswilYc"></iframe>
[Slide source](http://www.codemanship.co.uk/files/littleuml.pdf)

Jason and I went through the slides discussing OO design as we went. After
looking at the user cases, acceptance tests and CRC cards, we started writing an
implementation of the software.

## Tests
This is as far as we got:

1. add a new title
2. donating a copy of a title that isn't in the library add the title to the
   library
3. donating a copy of a different title that isn't in the library adds the title
   to the library
4. finding a title that doesn't exist in the library returns null.

To satisfy *1* we mocked the title class and wrote a method `addToNewTitles` on
library to add that title to library. The assertion used a `getNewTitles` method
that returned a list of new titles. Initially we tried using arrays but lists
have a nicer set of methods such as `contains` that saved us the cost of writing
sorting and searching algorithms (that would also require us to implement quite
a bit of title). Satisfying *2* involved adding a title to the library, and then
returning the first element of the list holding our titles. The assertions we
were writing to check the title was correct were very horrible, lots of getters
on title--poor emergent design. Next week we'll have a look at how to go from
our current implementation to something a little cleaner doing lots of
refactoring!

# LibraryTests.java
{% highlight java %}
package org.willprice.videolibrary;

import static org.junit.Assert.*;

import java.lang.reflect.Array;
import java.util.Arrays;

import org.junit.Test;

import static org.mockito.Mockito.*;

public class LibraryTests {

	@Test
	public void addNewTitle() {
		Title expectedTitle = mock(Title.class);
		Library library = new Library();
		library.addToNewTitles(expectedTitle);
		assertTrue(library.getNewTitles().contains(expectedTitle));
	}
	
	@Test
	public void donatingCopyOfTitleThatIsntInLibraryAddsTitleToLibrary() throws Exception {
		Library library = new Library();
		String name = "The Abyss";
		String director = "James Cameron";
		String yearOfRelease = "1989";
		library.donate(name, director, yearOfRelease);
		Title titleFound = library.findTitle(name);
		assertEquals(name, titleFound.getName());
		assertEquals(director, titleFound.getDirector());
		assertEquals(yearOfRelease, titleFound.getYearOfRelease());
	}
	
	@Test
	public void donatingCopyOfOceansElevenThatIsntInLibraryAddsOceansElevenToLibrary() throws Exception {
		Library library = new Library();
		String name = "Oceans Eleven";
		String director = "Steven Soderbergh";
		String yearOfRelease = "2002";
		library.donate(name, director, yearOfRelease);
		Title titleFound = library.findTitle(name);
		assertEquals(name, titleFound.getName());
		assertEquals(director, titleFound.getDirector());
		assertEquals(yearOfRelease , titleFound.getYearOfRelease());
	}
	
	@Test
	public void findingTitleThatDoesntExistInLibraryReturnsNull() throws Exception {
		Library library = new Library();
		library.donate("The Abyss", "", "");
		assertNull(library.findTitle(""));
	}
}

{% endhighlight %}

# Library.java
{% highlight java %}
package org.willprice.videolibrary;

import java.util.ArrayList;
import java.util.List;

import org.mockito.Matchers;

public class Library {

	private List<Title> newTitles = new ArrayList<Title>();
	private List<Title> titles = new ArrayList<Title>();

	public List<Title> getNewTitles() {
		return newTitles;
	}

	public void addToNewTitles(Title title) {
		newTitles.add(title);
	}

	public List<Title> getTitles() {
		return titles ;
	}

	public void donate(String name, String director, String year) {
		titles.add(new Title(name, director, year));
	}

	public Title findTitle(String name) {
		if (name == "")
			return null;
		return titles.get(0);
	}

}
{% endhighlight %}

# Title.java
{% highlight java %}
package org.willprice.videolibrary;

public class Title {

	private String name;
	private String director;
	private String year;

	public Title(String name, String director, String year) {
		this.name = name;
		this.director = director;
		this.year = year;
	}

	public String getName() {
		return name;
	}

	public String getDirector() {
		return director;
	}

	public String getYearOfRelease() {
		return year;
	}

}
{% endhighlight %}

# The Homework: User stories, Acceptance tests, and CRC cards for an interesting problem
Jason wants me to have ago applying the principles that we covered in the
pairing session on a different example, so I have free reign over what I want to
do. I'm quite interested in writing an app that allows users to track how often
they indulge in their vices. In my case: alcohol, I'd like to cut down on my
consumption, but I'm not quite sure how much I'm drinking, having an app to
record this information would be very helpful. Graphing it would be even more
helpful to see whether I'm decreasing my intake or not.


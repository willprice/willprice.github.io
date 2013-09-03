---
layout: post
title: "Mock objects: The BoxOffice example"
tags: ['pairing']
---
(Friday 30th August Pairing with Jason)
### Introduction: Why mock objects

Having been exposed to the basics of TDD: Using `asserts` to make sure things
changed; trying to write each test so it fails for only one reason;
triangulating a solution, rather than just dumping it all in one fell swoop, I
thought it was about time to learn what mock objects are, and what they are used
for.

### Useful Terminology:
Taking a moment to familiarise myself with the terminology used with mocks was an important step in understanding what they are.
* `Stub` - A method that returns a specific result
* `Mock` - A class with the assertion that a certain method was called.

Don't expect my usage of terminology to be spot on; I'm still learning!

### The Problem:
Jason suggested we try writing a virtual box office where a customer can book
tickets for a specific play. After a discussion we wrote an acceptance test (in
English) to outline what our end result should be able to do:

    Given that the seat A6 is available for a performance of 'Cats'
    when I reserve A6 using credit card number 1234
    then A6 should be marked as reserved for 1234 and cannot be booked by anyone else.

    ### Roles:
    * Seat (A6)
    * Performance (Cats)
    * Box office - entry point.


    ### Actions:
    * Reserve


    ### States:
    * Available (Seat)
    * Marked as reserved for `[credit card number] (Seat)`
    * Cannot be booked/Unavailable (Seat)

    1. Customer tells box office to reserve seat A6 at performance of 'Cats' using credit card number 1234
    2. Box office finds performance of 'Cats' and tells performance to reserve Seat A6 using credit card number 1234
    3. 'Cats' performance finds seat A6 and tells seat A6 to reserve itself using credit card number 1234
    4. Seat A6 records the credit card number of the reserver.

### Building Outside in:
When building an application from the outside in, we need some way of testing
the interaction between what we're writing and the next layer in which hasn't
been written yet. That's were mocks and stubs come in...

To start off Jason suggested that we design the program as a simple web
service--a query would come in with a performance name, credit card number, and
seat identifier. We' d then reserve the seat if it was available, otherwise
throw and exception indicating the unavailability of that seat.

The simplest thing I could think of testing was **finding a specific
performance**, the implementation is pretty simple, define a method on
`BoxOffice` that finds a performance in a `HashMap<String, Performance>`.
Testing this is more complicated than simply asserting that the correct
performance was found using the search. Mocks to the rescue! We can write an
interface (`Mockito` can also mock classes too, Jason showed me the traditional
way, before mocking classes was possible) for performance and then mock it using
`mock(Performance.class)`, this returns a mock object of the type `Performance`.
It has no functionality, but we can call any method on it that is defined in the
interface, the methods will not do anything as we haven't defined any behaviour
for it (because for this test behaviour is superfluous). 

        // BoxOffice is a field in the test class
	protected Performance createBoxOfficeWithMockPerformance() {
		Performance mockPerformance = mock(Performance.class);
		HashMap<String, Performance> performances = new HashMap<>();
		performances.put("Cats", mockPerformance);
		boxOffice = new BoxOffice(performances);
		return mockPerformance;
	}

	@Test
	public void findsPerformanceOfCats() {
		Performance mockPerformance = createBoxOfficeWithMockPerformance();
		assertEquals(mockPerformance, boxOffice.findPerformance("Cats"));
	}

I thought the responsibility of reserving a seat should belong to a `Seat` class that would be at the bottom of the class hierarchy of the finished application: 

    BoxOffice -> Performance -> Seat

`BoxOffice` would need to talk to `Performance` which would then eventually talk to `Seat`. 

We wrote the next test for **Reserving a seat**. `BoxOffice.reserveSeat(String Performance, String seatIdentifier, String creditCardNumber)` would be the signature of the method so we started by writing the assertion: 

    verify(mockPerformance).reserveSeat("A6", "1234")

`verify` takes a mock object and makes sure that the method was called using the same parameters, and so then it was time to call `mockPerformance.reserveSeat(...)` which would be called by `BoxOffice.reserveSeat(...)`

    // mockPerformance is a performance of "Cats" in the box office
    boxOffice.reserveSeat("Cats", "A6", "1234")
    verify(mockPerformance).reserveSeat("A6", "1234")

### Mocking `voids`:
Ouch! I had a hard time figuring out why `when(mockedObject.voidMethod).thenThrow(new RuntimeException())` wasn't working. Mockito's `when` method doesn't work with void methods. You must use a `doReturn|doThrow|doAnswer...` method, and so the `when` code ends up looking like: `doThrow(new RuntimeException()).when(mockedObject).voidMethod(..);`

This helped me mock `Performance` so that I could throw an `UnavailableSeatException` when trying to reserve a seat for the second time in my acceptance test. 

### Mocked method behaviour
Giving mocked methods 'intelligent' behaviour cam be accomplished in 2 ways. 

1. Changing the behaviour based on argument
2. Changing behavious based on number of invocations

The first:

    when(mockObject.method(1)).thenReturn(1)
    when(mockObject.method(2)).thenReturn(2)

The second

    when(mockObject.method()).thenReturn(1).thenReturn(2)
    mockObject.method() // => 1
    mockObject.method() // => 2

Mockito returns the mocked method for each `then*` invocation, so you can chain the `then*` methods together like in this example. 


My tests all have the mocks written into them. Jason suggested I try removing
this hardcoding of objects, allowing myself to inject either mocks or a concrete
implementation which will the focus of my next post; that is once I've managed
to do it, and write it up.

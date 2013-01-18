---
title: "Structured Program Development"
layout: layout
---

All programs can be expressed in terms of 3 _control structures_, namely:
- sequence structure (excecution in sequential order)
- selection structure (if, if/else, switch)
- repetition structure (while, for)
# Flowcharting
- Rectangle : action symbol : computation, IO
- Oval : `begin`, `end` to mark start/end program excecution.
- Diamond : conditional symbol : if, if/else, switch

# Selection structure
- if : single-selection
- if/else : double-selection
- switch : multiple-selection

- `?:` : conditional operator : `printf("%s\n", grade >= 60 ? "Passed" : Failed");`
          `<conditional statement> ? <code block if true> : <code block if false>`

- Unitialized variables contain garbage data (still the case?)
- `;` : empty statement.

# Repetition structures:
## Count-Controlled repetition
{% highlight c %}
main() {
  int total, grade, counter, average;

  total = 0;
  counter = 1;

  while (counter <= 10) {
  
    printf("Enter grade: ");
    scanf("%d", &grade);
    total += grade;
    counter += 1;
  }
  
  average = total/10;
  printf("Class average is %d/n", average);

  return 0;
}
{% endhighlight %}

## Sentinel-Controlled repetition
### Top-down, stepwise refinement
1. Determine class average for the quiz
2. - initialize vars
   - input, sum and count the quiz grades
   - calculate the average of the quiz grades, and print
3. - intialize total to zero, counter to zero
   - input the first grade
   - while the user has not get entered the sentinel:
      - add this grade into the running total
      - Add one to the grade counter
      - input the next grade or sentinel
   - if counter is not equal to zero:
      - set average to total divided by counter
      - print average
   - else:
      - print "no grades were entered"
4. Now at a sufficiently high level of detail/low level of abstraction, rewrite in C.

{% highlight c %}
  /*  Class average written using a top-down approach
      with sentinel-controlled reptition */

  main() {
    float average;
    int counter, grade, total;

    total = 0;
    counter = 0;

    printf("Enter grade, -1 to end: ");
    scanf("%d", &grade);

    while (grade != -1) {
      total += grade;
      counter += 1;
      printf("Enter grade, -1 to end: ");
      scanf("%d", &grade);
    }

    if (counter != 0) {
      average = (float) total/counter;
      printf("Class average is %.2f", average);
    } else {
      printf("No grades were entered\n";
    }

    return 0;
}
{% endhighlight %}

Here we used (float) to _cast_ `total` from an `int` to a `float`, allowing for floating point division.
- `(float)` is the _unary cast operator_, this creates a floating point copy of it's argument for use in whatever calculation is being performed.
- When float/int, int is promoted to a float (implicit conversion/promotion) so that the calculation can take place.
- `%.2f` : print floating point number to 2 d.
- `a++` : postincrement : will use the current value of a in the expression, then increment a by one.
- `++a` : preincrement : will increment a, then use the new value of a in the expression
- `a++` == `++a` when executed as an individual statement.
- casts, increments have second highest precedence (first being parentheses)


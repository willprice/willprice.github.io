---
layout: post
title: "Loop invariants"
---

Prove that the given the code calculates the factorial of a *positive* integer
variable `x`.

```c
int y = x;
while (x-- > y) {
    y *= x;
}
```

We can annotate each line of code describe the properties of the variables (have
a look into Hoare logic for more information).

```c
// Subscripts denote the number of loops we have iterated through

// Since our input is a positive integer we know it is greater than 0
// { x_0 > 0 }
int y = x;
// { x_0 > 0, y_0 = x_0 }
while (x-- > 1) {
    y *= x;
// { x_{i + 1} = x_i - 1, y_i = x_0 * x_1 * ... * x_i }
}
// { x_j = 1 }
```

We can prove validity using the following conditions

- Pre loop: (1): `{ x_0 > 0 }`, (2): `{ y_0 = x_0 }` 
- Inside of loop: (3): `{ x_{i + 1} = x_i - 1 }` and (4): `{ y_i = x_0 * x_1 * ... * x_i }`
- Post loop: (5): `{ x_j = 1 }`

The loop runs `j` times since the loop will only execute when `x_i > 1`, and
from (1), (3), (4) and (5) we can deduce that `y_j =  x_0 * x_1 * ... * x_j = x
* (x - 1) * ... * 1` which is the factorial of `x`.

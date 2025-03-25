# Numerical-Methods-Utilities
NOTE: For educational purposes.


## Algorithm on Bisection or Bisection Method for Numerical Methods

* Bisection-Method-Epsilon.cpp uses epsilon as basis.
a and b are two points in the x-axis.
The interval is small enough when (b - a) <= epsilon.

* Bisection-Method-Error-Tolerance.cpp uses the result of f(c) as basis.
The root approximation is accurate enough when |f(c)| <= Error Tolerance (Ex).


## Regula Falsi Method or False Position Method

* Regula-Falsi-Method.cpp uses the result of F(x) as basis.
The root approximation is accurate enough when |F(x)| <= Ex.

* Regula-Falsi-Method.cpp can find root/s with a user input [a, b].

* **(New!)**: Now supports multiroots for polynomials

* coefficient based function, only modify coefficients


## Interval Finder

* Interval finder is used for finding [a, b] interval with user-defined interval size.

* File path: utils/interval_finder.cpp

* smaller interval size reduce iterations for Bisection Method and Regula Falsi Method.

## Upcoming New Tools and Utilities!

* Python graph plotter
  - For plotting interval a, b, and root.
  - Graphical representation of Methods.

* Gauss-Jacobi Method
  - iterative approach

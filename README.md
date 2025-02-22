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

* Regula-Falsi-Method.cpp can find one root with a user input [a, b].

 
## Upcoming New Tools and Utilities!

* [a, b] interval finder
  - For looking up smaller interval.
  - Reduce iterations for Bisection Method and Regula Falsi Method.

* Regula-Falsi-Method
  - Support for multiple roots.
  - For polynomials.

* Python graph plotter
  - For plotting interval a, b, and root.
  - Graphical representation of Methods.

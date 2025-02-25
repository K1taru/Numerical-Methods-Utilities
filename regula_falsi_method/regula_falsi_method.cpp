#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double function(double x) {
  return pow(x, 3) + (2 * pow(x, 2)) + (10 * x) - 20 ;
} // Example function in assignment

double regulaFalsiMethod(double a, double b, double Ex) {
  if (function(a) * function(b) >= 0) {
    cout << "Invalid interval: f(a) and f(b) must have opposite signs or f(a) * f(b) < 0.\n";
    return -1;
  }
  
    int iteration = 0;
    double x, F_a, F_b, F_x;

    while (true) { // loop until |F(x)| <= Ex
      F_a = function(a);
      F_b = function(b);

      x = (a * F_b - b * F_a) / (F_b - F_a);
      F_x = function(x);

      cout << std::setprecision(10);
      cout << "Iteration: " << ++iteration << '\n';
      cout << "  a = " << a << '\n';
      cout << "  b = " << b << '\n';
      cout << "  x = " << x << '\n';
      cout << "  F(a) = " << F_a << '\n';
      cout << "  F(b) = " << F_b << '\n';
      cout << "  F(x) = " << F_x << "\n\n";

      // Stop if |F(x)| <= Ex
      if (fabs(F_x) <= Ex)
          break;

      // Update interval based on sign of function values
      if (F_a * F_x < 0)
          b = x;
      else
          a = x;
  }
  return x;
}

int main() {
  double a, b, Ex;

  cout << "Enter a: ";
  cin >> a;
  cout << "Enter b: ";
  cin >> b;
  cout << "Enter error tolerance (Ex): ";
  cin >> Ex;

  double root = regulaFalsiMethod(a, b, Ex);

    if (root != -1)
        cout << "Approximate root: " << std::setprecision(10) << root << "\n";

  return 0;
}

#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;
                                          // Coefficients:  V      V      V    V
vector<double> coefficients = {1, 0, -1, -1}; // From f(x) = x^3 + 0*x^2 - x - 1

double polynomialFunction(double x) {
  double result = 0;
  for (double coef : coefficients) {
    result = result * x + coef;
  }
  return result;
}

double regulaFalsiMethod(double a, double b, double Ex) {
  if (polynomialFunction(a) * polynomialFunction(b) >= 0) {
    cout << "Invalid interval: f(a) and f(b) must have opposite signs.\n";
    return NAN;
  }

  int iteration = 0;
  double x, F_a, F_b, F_x;

  while (true) {
    F_a = polynomialFunction(a);
    F_b = polynomialFunction(b);

    x = (a * F_b - b * F_a) / (F_b - F_a);
    F_x = polynomialFunction(x);

    cout << fixed << setprecision(10);
    cout << "Iteration: " << ++iteration << '\n';
    cout << "  a = " << a << '\n';
    cout << "  b = " << b << '\n';
    cout << "  x = " << x << '\n';
    cout << "  F(a) = " << F_a << '\n';
    cout << "  F(b) = " << F_b << '\n';
    cout << "  F(x) = " << F_x << "\n\n";

    if (fabs(F_x) <= Ex)
      break;

    if (F_a * F_x < 0)
      b = x;
    else
      a = x;
  }

  return x;
}

// Perform synthetic division on f(x) by (x - root)
vector<double> syntheticDivision(double root) {
  vector<double> newCoefficients(coefficients.size() - 1);
  double remainder = coefficients[0]; // First coefficient remains the same

  for (size_t i = 1; i < coefficients.size(); i++) {
    newCoefficients[i - 1] = remainder;
    remainder = remainder * root + coefficients[i];
  }

  return newCoefficients; // Return reduced polynomial coefficients
}

// Solve quadratic equation ax^2 + bx + c = 0
void solveQuadratic(double a, double b, double c) {
  double discriminant = b * b - 4 * a * c;

  if (discriminant > 0) {
    double root1 = (-b + sqrt(discriminant)) / (2 * a);
    double root2 = (-b - sqrt(discriminant)) / (2 * a);
    cout << "Remaining roots: " << root1 << ", " << root2 << '\n';
  }
  else if (discriminant == 0) {
    double root = -b / (2 * a);
    cout << "Remaining root: " << root << '\n';
  }
  else {
    cout << "Remaining roots are complex.\n";
  }

}

int main() {
  double a, b, Ex;
    
  cout << "Enter a: ";
  cin >> a;
  cout << "Enter b: ";
  cin >> b;
  cout << "Enter error tolerance (Ex): ";
  cin >> Ex;

  double root1 = regulaFalsiMethod(a, b, Ex);
  
  if (!isnan(root1)) {
    cout << "First root: " << root1 << '\n';

    vector<double> reducedCoefficients = syntheticDivision(root1);
    cout << "Reduced polynomial coefficients: ";
    for (double coef : reducedCoefficients) {
      cout << coef << " ";
    }
    cout << "\n";

    solveQuadratic(reducedCoefficients[0], reducedCoefficients[1], reducedCoefficients[2]);
  }

  return 0;
}

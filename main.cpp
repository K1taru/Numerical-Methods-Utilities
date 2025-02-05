#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double function(double x) {
    return pow(x, 3) - 4;
} // Example function: f(x) = x² - 4 (root at x = ±2) (you can modify this function)

double bisection(double a, double b, double epsilon) {
    if (function(a) * function(b) >= 0) {
        cout << "Invalid interval: f(a) and f(b) must have opposite signs.\n";
        return -1;
    }

    int iteration = 0;
    double c;
    while ((b - a) >= epsilon) {
        c = (a + b) / 2;
        double f_a = function(a);
        double f_b = function(b);
        double f_c = function(c);

        cout << std::setprecision(10);
        cout << "Iteration: " << ++iteration << '\n';
        cout << "  a = " << a << '\n';
        cout << "  b = " << b << '\n';
        cout << "  c = " << c << '\n';
        cout << "  f(a) = " << f_a << '\n';
        cout << "  f(b) = " << f_b << '\n';
        cout << "  f(c) = " << f_c << "\n\n";

        if (f_c == 0.0)
            break;

        if (f_a * f_c < 0)
            b = c;
        else
            a = c;
    }
    return c;
}

int main() {
    double a, b, Ex;
    
    cout << "Enter a: ";
    cin >> a;
    cout << "Enter b: ";
    cin >> b;
    cout << "Enter Ex: ";
    cin >> Ex;

    double root = bisection(a, b, Ex);
    
    if (root != -1)
        std::cout << "Approximate root: " << std::setprecision(10) << root << '\n';
    
    return 0;
}

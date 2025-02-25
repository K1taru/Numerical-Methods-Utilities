#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double function(double x) {
    return cos(x) - (x * exp(x));
} // Example function: f(x) = x^3 - 4 (you can modify this function)

double bisectionMethod(double a, double b, double Ex) { // error tolerance for f(c)
    if (function(a) * function(b) >= 0) {
        cout << "Invalid interval: f(a) and f(b) must have opposite signs or f(a) * f(b) < 0.\n";
        return -1;
    }

    int iteration = 0;
    double c;
    while (true) { // loop until |f(c)| <= Ex
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

        // |f(c)| is <= Ex
        if (fabs(f_c) <= Ex)
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
    cout << "Enter error tolerance (Ex): ";
    cin >> Ex;

    double root = bisectionMethod(a, b, Ex);
    
    if (root != -1)
        std::cout << "Approximate root: " << std::setprecision(10) << root << '\n';
    
    return 0;
}

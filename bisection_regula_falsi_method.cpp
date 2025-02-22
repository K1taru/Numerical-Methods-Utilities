#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double function(double x) {
    return pow(x, 3) - 4; // Example function f(x) = x^3 - 4
}

// Bisection Method
double bisectionMethod(double a, double b, double Ex) {
    if (function(a) * function(b) >= 0) {
        cout << "Invalid interval: f(a) and f(b) must have opposite signs.\n";
        return -1;
    }

    int iteration = 0;
    double c;
    while (true) {
        c = (a + b) / 2;
        double f_a = function(a);
        double f_b = function(b);
        double f_c = function(c);

        cout << setprecision(10);
        cout << "Iteration: " << ++iteration << '\n';
        cout << "  a = " << a << '\n';
        cout << "  b = " << b << '\n';
        cout << "  c = " << c << '\n';
        cout << "  f(a) = " << f_a << '\n';
        cout << "  f(b) = " << f_b << '\n';
        cout << "  f(c) = " << f_c << "\n\n";

        if (fabs(f_c) <= Ex)
            break;

        if (f_a * f_c < 0)
            b = c;
        else
            a = c;
    }
    return c;
}

// Regula Falsi Method
double regulaFalsiMethod(double a, double b, double Ex) {
    if (function(a) * function(b) >= 0) {
        cout << "Invalid interval: f(a) and f(b) must have opposite signs.\n";
        return -1;
    }

    int iteration = 0;
    double x, F_a, F_b, F_x;

    while (true) {
        F_a = function(a);
        F_b = function(b);
        x = (a * F_b - b * F_a) / (F_b - F_a);
        F_x = function(x);

        cout << setprecision(10);
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

int main() {
    double a, b, Ex;
    int method;

    cout << "Choose method:\n";
    cout << "1 - Bisection Method\n";
    cout << "2 - Regula Falsi Method\n";
    cout << "Enter method: ";
    cin >> method;

    cout << "Enter a: ";
    cin >> a;
    cout << "Enter b: ";
    cin >> b;
    cout << "Enter error tolerance (Ex): ";
    cin >> Ex;

    double root;
    switch (method) {
        case 1:
            root = bisectionMethod(a, b, Ex);
            break;
        case 2:
            root = regulaFalsiMethod(a, b, Ex);
            break;
        default:
            cout << "Invalid choice!\n";
            return 1;
    }

    if (root != -1)
        cout << "Approximate root: " << setprecision(10) << root << '\n';

    return 0;
}
 
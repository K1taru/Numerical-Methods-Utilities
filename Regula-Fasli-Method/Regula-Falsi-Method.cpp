#include <iostream>
#include <cmath>
using namespace std;

double function(double x) {
  return 3 * cos(-2 * x);
}


int main() {
  double a, b, Ex;

  cout << "Enter a: ";
  cin >> a;
  cout << "Enter b: ";
  cin >> b;
  cout << "Enter error tolerance (Ex): ";
  cin >> Ex;

  return 0;
}
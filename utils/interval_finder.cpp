#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

double function(double x) {
  return pow(x, 3) - 4; // Modify function if needed
}

// Function to find all valid intervals
vector<tuple<double, double, double, double>> findIntervals(double intervalSize) {
  vector<tuple<double, double, double, double>> intervals;

  double x = 0;
  double prevX = x, prevF = function(prevX);

  while (x <= 20) {
    x += intervalSize;
    double f_x = function(x);

    if (prevF * f_x < 0) {
      intervals.push_back({prevX, x, prevF, f_x});
    }
    prevX = x;
    prevF = f_x;
  }

  x = -intervalSize;
  prevX = 0;
  prevF = function(prevX);

  while (x >= -20) {
    double f_x = function(x);

    if (prevF * f_x < 0) {
      intervals.push_back({prevX, x, prevF, f_x});
    }

    prevX = x;
    prevF = f_x;
    x -= intervalSize;
  }

  return intervals;
}

int main() {
  double intervalSize;
  cout << "Set interval size: ";
  cin >> intervalSize;

  if (intervalSize <= 0) {
    cout << "Interval size must be positive.\n";
    return 1;
  }

  vector<tuple<double, double, double, double>> intervals = findIntervals(intervalSize);

  if (intervals.empty()) {
    cout << "No valid intervals found.\n";
  } 
  else {
    cout.precision(10);

    for (const auto &[a, b, f_a, f_b] : intervals) {
    cout << "\n[" << a << ", " << b << "]\n";
    cout << "  f(a)= " << f_a << '\n';
    cout << "  f(b)= " << f_b << "\n";
  }
}

  return 0;
}

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

double function(double x) {
  return 3 * cos(-2 * x); // Modify function if needed
}

void findIntervals() {
  struct Interval {
    double a, b;
    double f_a, f_b;
  };

  double x_AxisStart, x_AxisEnd, intervalSize;

  cout << "Set x-axis left limit: ";
  cin >> x_AxisStart;
  cout << "Set x-axis right limit: ";
  cin >> x_AxisEnd;
  cout << "Set interval size: ";
  cin >> intervalSize;

  if (intervalSize <= 0) {
    cout << "Interval size must be positive.\n";
    return;
  }

  vector<Interval> intervals;
  double prevX = x_AxisStart, prevF = function(prevX);

  for (double x = x_AxisStart + intervalSize; x <= x_AxisEnd; x += intervalSize) {
    double f_x = function(x);

    if (prevF * f_x < 0) {
      intervals.push_back({prevX, x, prevF, f_x});
    }

    prevX = x;
    prevF = f_x;
  }

  if (intervals.empty()) {
    cout << "No valid intervals found.\n";
  } else {
    cout.precision(10);
    for (const auto& interval : intervals) {
      cout << "\n[" << interval.a << ", " << interval.b << "]\n";
      cout << "  f(a) = " << interval.f_a << '\n';
      cout << "  f(b) = " << interval.f_b << "\n";
    }
  }
}

int main() {
  findIntervals();
  return 0;
}

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  int T;
  cin >> T;
  for (int z = 0; z < T; ++z) {
    double d;
    int n;
    cin >> d >> n;
    vector<double> k;
    vector<double> s;
    for (int i = 0; i < n; ++i) {
      double temp;
      cin >> temp;
      k.push_back(temp);
      cin >> temp;
      s.push_back(temp);
    }
    double t = 0;
    for (int i = 0; i < n; ++i) {
      double ti = (d - k[i]) / s[i];
      if (ti > t)
        t = ti;
    }
    cout << "Case #" << z + 1 << ": " << setprecision(9) << d / t << "\n";
  }
}
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  int T;
  cin >> T;
  for (int z = 0; z < T; ++z) {
    int n, q;
    cin >> n >> q;
    vector<double> e;
    vector<double> s;
    vector<double> d;
    for (int i = 0; i < n; ++i) {
      double temp;
      cin >> temp;
      e.push_back(temp);
      cin >> temp;
      s.push_back(temp);
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        double temp;
        cin >> temp;
        if (j == i + 1) {
          d.push_back(temp);
        }
      }
    }
    double temp;
    cin >> temp >> temp;

    vector<vector<double>> t;
    vector<vector<double>> dur;
    t.resize(n - 1);
    dur.resize(n - 1);
    for (int i = 0; i < n - 1; ++i) {
      t[i].resize(n - 1);
      dur[i].resize(n - 1);
    }

    t[0][0] = d[0] / s[0];
    dur[0][0] = e[0] - d[0];
    for (int i = 1; i < n - 1; ++i) {
      t[0][i] = 1e20;
      dur[0][i] = -1;
    }
    for (int i = 1; i < n - 1; ++i) {
      for (int j = 0; j < n - 1; ++j) {
        if (j < i) {
          if (dur[i - 1][j] < d[i]) {
            t[i][j] = 1e20;
            dur[i][j] = -1;
          } else {
            t[i][j] = t[i - 1][j] + d[i] / s[j];
            dur[i][j] = dur[i - 1][j] - d[i];
          }
        } else if (j == i) {
          double min = 1e20;
          for (int x = 0; x < n - 1; ++x) {
            if (t[i - 1][x] < min)
              min = t[i - 1][x];
          }
          t[i][j] = min + d[i] / s[i];
          dur[i][j] = e[i] - d[i];
        } else {
          t[i][j] = 1e20;
          dur[i][j] = -1;
        }
      }
    }
    double mint = 1e20;
    for (int i = 0; i < n - 1; ++i) {
      if (t[n - 2][i] < mint)
        mint = t[n - 2][i];
    }
    cout << "Case #" << z + 1 << ": " << setprecision(9) << mint << "\n";
  }
}
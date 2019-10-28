#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  int T;
  cin >> T;
  for (int i = 0; i < T; ++i) {
    int n, p;
    cin >> n >> p;
    vector<int> target;
    for (int j = 0; j < n; ++j) {
      int temp;
      cin >> temp;
      target.push_back(temp);
    }
    vector<vector<int>> table;
    table.resize(n);
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < p; ++k) {
        int temp;
        cin >> temp;
        table[j].push_back(temp);
      }
      sort(table[j].begin(), table[j].end());
    }
    vector<vector<int>> upper;
    vector<vector<int>> lower;
    upper.resize(n);
    lower.resize(n);

    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < p; ++k) {
        upper[j].push_back(
            floor((double)table[j][k] / (0.9 * (double)target[j])));
        lower[j].push_back(
            ceil((double)table[j][k] / (1.1 * (double)target[j])));
        // cout<<upper[j][k]<< ' ' <<lower[j][k]<<'\n';
      }
    }
    vector<int> current;
    for (int j = 0; j < n; ++j) {
      current.push_back(0);
    }
    int count = 0;
    for (int k = 0; k < p; ++k) {
      if (upper[0][k] < lower[0][k])
        continue;
      bool flag = true;
      bool flag2;
      for (int j = 1; j < n; ++j) {
        flag2 = false;
        for (int l = current[j]; l < p; ++l) {
          if (upper[j][l] >= lower[0][k] && upper[j][l] >= lower[j][l]) {
            current[j] = l;
            flag2 = true;
            if (lower[j][l] <= upper[0][k]) {
              ;
              break;
            } else {
              flag = false;
              break;
            }
          }
        }
        if (!flag2 || !flag)
          break;
      }
      if (!flag2)
        break;
      if (flag) {
        ++count;
        for (int j = 1; j < n; ++j) {
          ++current[j];
        }
      }
    }
    cout << "case #" << i + 1 << ": " << count << '\n';
  }
}

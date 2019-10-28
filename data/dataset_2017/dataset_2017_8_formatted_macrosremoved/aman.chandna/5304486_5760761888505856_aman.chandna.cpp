

#include <bits/stdc++.h>
#include <unordered_map>
#include <unordered_set>
using namespace std;

int main() {

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  ;
  freopen("inp.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
  long long t;
  cin >> t;
  for (long long ccr = 1; ccr <= t; ++ccr) {

    long long rows, cols;
    cin >> rows >> cols;
    cin.ignore(256, '\n');
    vector<string> vec(rows, "");
    for (long long i = 0; i < rows; ++i)
      cin >> vec[i];
    for (long long i = 0; i < rows; ++i) {
      for (long long j = 1; j < cols; ++j) {
        if (vec[i][j] == '?' && vec[i][j - 1] != '?')
          vec[i][j] = vec[i][j - 1];
      }
    }
    for (long long i = 0; i < rows; ++i) {
      for (long long j = cols - 2; j >= 0; --j) {
        if (vec[i][j] == '?' && vec[i][j + 1] != '?')
          vec[i][j] = vec[i][j + 1];
      }
    }
    for (long long j = 0; j < cols; ++j) {
      for (long long i = 1; i < rows; ++i) {
        if (vec[i][j] == '?' && vec[i - 1][j] != '?')
          vec[i][j] = vec[i - 1][j];
      }
    }
    for (long long j = 0; j < cols; ++j) {
      for (long long i = rows - 2; i >= 0; --i) {
        if (vec[i][j] == '?' && vec[i + 1][j] != '?')
          vec[i][j] = vec[i + 1][j];
      }
    }

    cout << "Case #" << ccr << ":\n";
    for (long long i = 0; i < rows; ++i) {
      cout << vec[i] << "\n";
    }
  }

  return 0;
}

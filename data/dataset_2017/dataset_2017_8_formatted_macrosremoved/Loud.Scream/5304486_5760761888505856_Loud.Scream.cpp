#include <bits/stdc++.h>

using namespace std;

bool check(const vector<string> &mas, int l) {
  int que = 0;
  for (int i = 0; i < mas.size(); ++i) {
    if (mas[i][l] == '?')
      ++que;
  }
  return que > 0;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) {
    cout << "Case #" << i << ":\n";
    int n, m;
    cin >> n >> m;
    vector<string> mas(n);
    for (int i = 0; i < n; ++i)
      cin >> mas[i];
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (mas[i][j] == '?')
          continue;
        int c = i + 1;
        while (c < n && mas[c][j] == '?') {
          mas[c][j] = mas[i][j];
          ++c;
        }
      }
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (mas[i][j] == '?')
          continue;
        int c = i - 1;
        while (c >= 0 && mas[c][j] == '?') {
          mas[c][j] = mas[i][j];
          --c;
        }
      }
    }
    for (int j = 0; j < m; ++j) {
      int que = 0;
      if (!check(mas, j)) {
        string h = "";
        for (int i = 0; i < n; ++i) {
          h += mas[i][j];
        }
        int l = j - 1, r = j + 1;
        while (l >= 0 && check(mas, l)) {
          for (int i = 0; i < n; ++i)
            mas[i][l] = h[i];
          --l;
        }
        while (r < m && check(mas, r)) {
          for (int i = 0; i < n; ++i)
            mas[i][r] = h[i];
          ++r;
        }
      }
    }
    for (int i = 0; i < n; ++i)
      cout << mas[i] << "\n";
  }
  return 0;
}

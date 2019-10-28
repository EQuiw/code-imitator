#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int t;
  cin >> t;

  for (int z = 1; z <= t; z++) {
    int r, c;
    cin >> r >> c;
    string s[12];
    for (int i = 0; i < r; i++) {
      cin >> s[i];
    }
    for (int i = 0; i < r - 1; i++) {
      for (int j = 0; j < c; j++) {
        if (s[i][j] != '?' && s[i + 1][j] == '?') {
          s[i + 1][j] = s[i][j];
        }
      }
    }
    for (int i = r - 1; i > 0; i--) {
      for (int j = 0; j < c; j++) {
        if (s[i][j] != '?' && s[i - 1][j] == '?') {
          s[i - 1][j] = s[i][j];
        }
      }
    }

    for (int j = 0; j < c - 1; j++) {
      for (int i = 0; i < r; i++) {
        if (s[i][j] != '?' && s[i][j + 1] == '?') {
          s[i][j + 1] = s[i][j];
        }
      }
    }

    for (int j = c - 1; j > 0; j--) {
      for (int i = 0; i < r; i++) {
        if (s[i][j] != '?' && s[i][j - 1] == '?') {
          s[i][j - 1] = s[i][j];
        }
      }
    }
    cout << "Case #" << z << ":" << endl;
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        cout << s[i][j];
      }
      cout << endl;
    }
  }
}
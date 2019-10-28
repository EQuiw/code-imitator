#include <iostream>
using namespace std;

int main() {
  int T;
  cin >> T;
  for (int iCase = 1; iCase <= T; ++iCase) {
    int n, m;
    cin >> n >> m;
    char cake[30][30];
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        cin >> cake[i][j];
        if (cake[i][j] == '?' && j > 0 && cake[i][j - 1] != '?') {
          cake[i][j] = cake[i][j - 1];
        }
      }
    }
    for (int i = 0; i < n; ++i) {
      for (int j = m - 1; j >= 0; --j) {
        if (cake[i][j] == '?' && j < m - 1 && cake[i][j + 1] != '?') {
          cake[i][j] = cake[i][j + 1];
        }
      }
    }
    for (int j = 0; j < m; ++j) {
      for (int i = 0; i < n; ++i) {
        if (cake[i][j] == '?' && i > 0 && cake[i - 1][j] != '?') {
          cake[i][j] = cake[i - 1][j];
        }
      }
    }
    for (int j = 0; j < m; ++j) {
      for (int i = n - 1; i >= 0; --i) {
        if (cake[i][j] == '?' && i < n - 1 && cake[i + 1][j] != '?') {
          cake[i][j] = cake[i + 1][j];
        }
      }
    }
    cout << "Case #" << iCase << ":" << endl;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        cout << cake[i][j];
      }
      cout << endl;
    }
  }
}
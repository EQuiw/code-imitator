#include <iostream>
using namespace std;

#define MAXN 32

int main() {
  int T, t, R, C, i, j;
  char m[MAXN][MAXN];

  cin >> T;
  for (t = 1; t <= T; t++) {
    cin >> R >> C;
    for (i = 0; i < R; i++)
      for (j = 0; j < C; j++)
        cin >> m[i][j];

    for (i = 0; i < R; i++)
      for (j = 1; j < C; j++)
        if (m[i][j] == '?' && m[i][j - 1] != '?')
          m[i][j] = m[i][j - 1];
    for (i = 0; i < R; i++)
      for (j = C - 2; j >= 0; j--)
        if (m[i][j] == '?' && m[i][j + 1] != '?')
          m[i][j] = m[i][j + 1];

    for (i = 1; i < R; i++)
      if (m[i][0] == '?' && m[i - 1][0] != '?')
        for (j = 0; j < C; j++)
          m[i][j] = m[i - 1][j];
    for (i = R - 2; i >= 0; i--)
      if (m[i][0] == '?' && m[i + 1][0] != '?')
        for (j = 0; j < C; j++)
          m[i][j] = m[i + 1][j];

    cout << "Case #" << t << ":" << endl;
    for (i = 0; i < R; i++) {
      for (j = 0; j < C; j++)
        cout << m[i][j];
      cout << endl;
    }
  }

  return 0;
}

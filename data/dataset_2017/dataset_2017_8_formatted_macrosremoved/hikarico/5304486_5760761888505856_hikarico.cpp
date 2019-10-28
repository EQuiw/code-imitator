#include <bits/stdc++.h>
using namespace std;
const int N = 30;

char s[N][N];
int tc, match[N][N];
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, -1, 0, 1};
int lmx[N], lMx[N], lmy[N], lMy[N], o[N];
bool used[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t, r, c;
  cin >> t;
  while (t--) {
    cin >> r >> c;
    for (int i = 0; i < r; ++i) {
      cin >> s[i];
    }
    memset(used, 0, sizeof used);
    // for each letter, interpolate
    int size = 0;
    for (char ch = 'A'; ch <= 'Z'; ++ch) {
      int mx = r, Mx = -1, my = c, My = -1;
      for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
          if (s[i][j] == ch) {
            mx = min(mx, i);
            Mx = max(Mx, i);
            my = min(my, j);
            My = max(My, j);
          }
        }
      }
      lmx[ch - 'A'] = mx;
      lmy[ch - 'A'] = my;
      lMx[ch - 'A'] = Mx;
      lMy[ch - 'A'] = My;
      if (mx <= Mx) {
        o[size++] = ch - 'A';
        used[ch - 'A'] = true;
        for (int i = mx; i <= Mx; ++i)
          for (int j = my; j <= My; ++j)
            s[i][j] = ch;
      }
    }
    // fill by rows first
    sort(o, o + size, [](int i, int j) {
      return lmx[i] < lmx[j] || (lmx[i] == lmx[j] && lMx[i] > lMx[j]);
    });
    for (int i = 0; i < size; ++i) {
      char ch = o[i];
      // expand left
      for (int ny = lmy[ch] - 1; ny >= 0; --ny) {
        bool ok = true;
        for (int k = lmx[ch]; k <= lMx[ch]; ++k) {
          if (s[k][ny] != '?') {
            ok = false;
            break;
          }
        }
        if (!ok)
          break;
        --lmy[ch];
        for (int k = lmx[ch]; k <= lMx[ch]; ++k) {
          s[k][ny] = ch + 'A';
        }
      }
      // expand right
      for (int ny = lMy[ch] + 1; ny < c; ++ny) {
        bool ok = true;
        for (int k = lmx[ch]; k <= lMx[ch]; ++k) {
          if (s[k][ny] != '?') {
            ok = false;
            break;
          }
        }
        if (!ok)
          break;
        ++lMy[ch];
        for (int k = lmx[ch]; k <= lMx[ch]; ++k) {
          s[k][ny] = ch + 'A';
        }
      }
    }
    // sort by columns
    sort(o, o + size, [](int i, int j) {
      return lmy[i] < lmy[j] || (lmy[i] == lmy[j] && lMy[i] > lMy[j]);
    });
    for (int i = 0; i < size; ++i) {
      char ch = o[i];
      // expand up
      for (int nx = lmx[ch] - 1; nx >= 0; --nx) {
        bool ok = true;
        for (int k = lmy[ch]; k <= lMy[ch]; ++k) {
          if (s[nx][k] != '?') {
            ok = false;
            break;
          }
        }
        if (!ok)
          break;
        --lmx[ch];
        for (int k = lmy[ch]; k <= lMy[ch]; ++k) {
          s[nx][k] = ch + 'A';
        }
      }
      // expand down
      for (int nx = lMx[ch] + 1; nx < r; ++nx) {
        bool ok = true;
        for (int k = lmy[ch]; k <= lMy[ch]; ++k) {
          if (s[nx][k] != '?') {
            ok = false;
            break;
          }
        }
        if (!ok)
          break;
        ++lMx[ch];
        for (int k = lmy[ch]; k <= lMy[ch]; ++k) {
          s[nx][k] = ch + 'A';
        }
      }
    }
    cout << "Case #" << ++tc << ":\n";
    for (int i = 0; i < r; ++i) {
      cout << s[i] << "\n";
    }
  }
}

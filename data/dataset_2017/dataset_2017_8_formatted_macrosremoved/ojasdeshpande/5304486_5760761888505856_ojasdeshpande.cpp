#include <bits/stdc++.h>

using namespace std;

signed main() {
  freopen("a.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  long long tt;
  cin >> tt;
  for (long long t = 1; t <= tt; t++) {
    cout << "Case #" << t << ":\n";
    long long r, c;
    cin >> r >> c;
    char g[r][c];
    map<char, long long> L, R, T, B;
    for (long long i = 0; i < r; i++)
      for (long long j = 0; j < c; j++) {
        cin >> g[i][j];
        if (g[i][j] != '?') {
          if (L.find(g[i][j]) == L.end())
            L[g[i][j]] = j;
          else
            L[g[i][j]] = min(L[g[i][j]], j);
          if (R.find(g[i][j]) == R.end())
            R[g[i][j]] = j;
          else
            R[g[i][j]] = max(R[g[i][j]], j);
          if (B.find(g[i][j]) == B.end())
            B[g[i][j]] = i;
          else
            B[g[i][j]] = min(B[g[i][j]], i);
          if (T.find(g[i][j]) == T.end())
            T[g[i][j]] = i;
          else
            T[g[i][j]] = min(T[g[i][j]], i);
        }
      }
    if (t == 88) {
      for (long long i = 0; i < r; i++) {
        for (long long j = 0; j < c; j++) {
          cerr << g[i][j];
        }
        cerr << endl;
      }
    }
    for (auto it = L.begin(); it != L.end(); it++) {
      char ch = it->first;
      for (long long i = B[it->first]; i <= T[it->first]; i++) {
        for (long long j = L[it->first]; j <= R[it->first]; j++) {
          g[i][j] = ch;
        }
      }
    }
    for (long long ii = 0; ii < 25; ii++) {
      for (long long i = 0; i < r; i++) {
        for (long long j = 0; j < c; j++) {
          if (g[i][j] == '?') {
            char ch = '?';
            if (i != 0)
              ch = g[i - 1][j];
            if (ch != '?' && L[ch] == j) {
              long long flag = 0;
              for (long long k = j + 1; k <= R[ch]; k++) {
                if (g[i][k] != '?')
                  flag = 1;
              }
              if (flag == 0) {
                for (long long k = j; k <= R[ch]; k++) {
                  g[i][k] = ch;
                }
                T[ch] = max(T[ch], i);
              }
            }
            if (g[i][j] != '?')
              continue;
            if (j != 0)
              ch = g[i][j - 1];
            if (ch != '?' && B[ch] == i) {
              long long flag = 0;
              for (long long k = i + 1; k <= T[ch]; k++) {
                if (g[k][j] != '?')
                  flag = 1;
              }
              if (flag == 0) {
                for (long long k = i; k <= T[ch]; k++)
                  g[k][j] = ch;
                R[ch] = max(R[ch], j);
              }
            }
            if (g[i][j] != '?')
              continue;
            if (i != (r - 1)) {
              for (long long k = i + 1; k < r; k++)
                if (g[k][j] != '?') {
                  ch = g[k][j];
                  break;
                }
            }
            if (ch != '?' && L[ch] == j) {
              long long flag = 0;
              for (long long k = j + 1; k <= R[ch]; k++) {
                if (g[i][k] != '?')
                  flag = 1;
              }
              if (flag == 0) {
                for (long long k = j; k <= R[ch]; k++)
                  g[i][k] = ch;
                B[ch] = min(B[ch], i);
              }
            }
            if (g[i][j] != '?')
              continue;
            if (j != (c - 1)) {
              for (long long k = j + 1; k < c; k++)
                if (g[i][k] != '?') {
                  ch = g[i][k];
                  break;
                }
            }
            if (ch != '?' && B[ch] == i) {
              long long flag = 0;
              for (long long k = i + 1; k <= T[ch]; k++) {
                if (g[k][j] != '?')
                  flag = 1;
              }
              if (flag == 0) {
                for (long long k = i; k <= T[ch]; k++)
                  g[k][j] = ch;
                L[ch] = min(L[ch], j);
              }
            }
          }
        }
      }
      long long flag = 1;
      for (long long i = 0; i < r; i++)
        for (long long j = 0; j < c; j++)
          if (g[i][j] == '?')
            flag = 0;
      if (flag) {
        if (t == 88)
          cerr << ii << endl;
        break;
      }
      if (t == 88 && ii < 4) {
        for (long long i = 0; i < r; i++) {
          for (long long j = 0; j < c; j++)
            cerr << g[i][j];
          cerr << endl;
        }
        cerr << L['A'] << " " << R['A'] << " " << T['A'] << " " << B['A']
             << endl;
        cerr << endl;
      }
    }
    for (long long i = 0; i < r; i++) {
      for (long long j = 0; j < c; j++)
        cout << g[i][j];
      cout << "\n";
    }
  }
  return 0;
}

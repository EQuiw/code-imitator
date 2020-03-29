#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

void updateGridPlus(vector<vector<int>> &c, int n, int x, int y) {
  for (int u = 0; u < n; ++u) {
    for (int v = 0; v < n; ++v) {
      if (u == x && v == y) {
        continue;
      }
      if (u == x || v == y) {
        c[u][v] = (c[u][v] & 2);
      }
    }
  }
}

void updateGridCross(vector<vector<int>> &c, int n, int x, int y) {
  for (int u = 0; u < n; ++u) {
    for (int v = 0; v < n; ++v) {
      if (u == x && v == y) {
        continue;
      }
      if (u + v == x + y || u - v == x - y) {
        c[u][v] = (c[u][v] & 1);
      }
    }
  }
}

int getTheoretical(vector<string> s) {
  int n = s.size();
  int score = 0;
  for (int i = 0; i < n; ++i) {
    int x = count(s[i].begin(), s[i].end(), 'x');
    int o = count(s[i].begin(), s[i].end(), 'o');
    int p = count(s[i].begin(), s[i].end(), 'p');

    x = min(x, 1);
    if (o > 0) {
      score += p + (o - 1) + 2;
    } else {
      score += p + x;
    }
  }
  return score;
}

void solve(int test) {
  int n, m;
  cin >> n >> m;

  vector<vector<char>> a(n, vector<char>(n, 0));
  vector<vector<int>> c(n, vector<int>(n, 7));

  for (int i = 0; i < m; ++i) {
    string s;
    int x, y;
    cin >> s >> x >> y;
    --x;
    --y;
    a[x][y] = s[0];

    if (a[x][y] != '+') {
      updateGridPlus(c, n, x, y);
    }
    if (a[x][y] != 'x') {
      updateGridCross(c, n, x, y);
    }

    if (a[x][y] == 'o') {
      c[x][y] = (c[x][y] & 4);
    }

    if (a[x][y] == '+') {
      c[x][y] = (c[x][y] & 6);
    }
    if (a[x][y] == 'x') {
      c[x][y] = (c[x][y] & 5);
    }

    /* for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
    cout << c[i][j] << " ";
    }
    cout << endl;
    }*/
  }

  vector<string> r(n, string(n, '.'));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      r[i][j] = a[i][j];
    }
  }

  int index = -1;
  for (int i = 0; i < n; ++i) {
    if (r[0][i] == 0) {
      r[0][i] = '+';
    } else if (r[0][i] == 'x') {
      r[0][i] = 'o';
    }

    if (r[0][i] != '+') {
      index = i;
    }
  }
  if (index == -1) {
    r[0][0] = 'o';
    index = 0;
  }

  for (int i = 1; i + 1 < n; ++i) {
    r[n - 1][i] = '+';
  }

  vector<bool> x(n, false), y(n, false);
  y[index] = true;

  int cnt = 0;
  for (int i = n - 1; i >= 0; --i) {
    for (int j = 0; j < n; ++j) {
      if (r[i][j] == 0 && !x[i] && !y[j]) {
        r[i][j] = 'x';
        x[i] = y[j] = true;
        ++cnt;
      }
    }
  }

  if (cnt != n - 1) {
    cerr << "BAD" << endl;
  }

  int score = 0;
  vector<pair<char, pair<int, int>>> res;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (r[i][j] == 'o') {
        score += 2;
        if (a[i][j] != 'o') {
          res.push_back(make_pair('o', make_pair(i + 1, j + 1)));
        }
      } else if (r[i][j] == 'x') {
        score += 1;
        if (a[i][j] != 'x') {
          res.push_back(make_pair('x', make_pair(i + 1, j + 1)));
        }
      } else if (r[i][j] == '+') {
        score += 1;
        if (a[i][j] != '+') {
          res.push_back(make_pair('+', make_pair(i + 1, j + 1)));
        }
      }
    }
  }

  printf("Case #%d: %d %d\n", test, score, res.size());
  for (int i = 0; i < res.size(); ++i) {
    printf("%c %d %d\n", res[i].first, res[i].second.first,
           res[i].second.second);
  }

  /*vector < string > s(n, "");
  for (int i = 0; i < n; ++i) {
          for (int j = 0; j < n; ++j) {
                  if (c[i][j] == 0) {
                          s[i] += '.';
                  } else if (c[i][j] & 4) {
                          s[i] += 'o';
                  } else if (c[i][j] & 1) {
                          s[i] += 'x';
                  } else {
                          s[i] += '+';
                  }
          }
  }

  printf("Theoretical %d\n", getTheoretical(s));
  for (int i = 0; i < n; ++i) {
          cout << s[i] << endl;
  }

  for (int t = 0; t < 100; ++t) {
          for (int i = 0; i < n; ++i) {
                  for (int j = 0; j < n; ++j) {
                          if (c[i][j] & 4) {
                                  ++m;
                                  updateGridCross(c, n, i, j);
                                  updateGridPlus(c, n, i, j);
                          } else if (c[i][j] == 1) {
                                  updateGridPlus(c, n, i, j);
                          } else if (c[i][j] == 2) {
                                  updateGridCross(c, n, i, j);
                          }
                  }
          }
  }

  int score = 0;
  vector < pair < char, pair < int, int > > > res;
  for (int i = 0; i < n; ++i) {
          for (int j = 0; j < n; ++j) {
                  if (c[i][j] == 0) {
                  } else if (c[i][j] & 4) {
                          score += 2;
                          if (a[i][j] != 'o') {
                                  res.push_back(make_pair('o', make_pair(i + 1,
  j + 1)));
                          }
                  } else if (c[i][j] & 1) {
                          score += 1;
                          if (a[i][j] != 'x') {
                                  res.push_back(make_pair('x', make_pair(i + 1,
  j + 1)));
                          }
                  } else {
                          score += 1;
                          if (a[i][j] != '+') {
                                  res.push_back(make_pair('+', make_pair(i + 1,
  j + 1)));
                          }
                  }
          }
  }

  printf("Case #%d: %d %d\n", test, score, res.size());
  for (int i = 0; i < res.size(); ++i) {
          printf("%c %d %d\n", res[i].first, res[i].second.first,
  res[i].second.second);
  }*/
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; ++i) {
    solve(i + 1);
    cerr << i + 1 << ": " << clock() << endl;
  }

  return 0;
}
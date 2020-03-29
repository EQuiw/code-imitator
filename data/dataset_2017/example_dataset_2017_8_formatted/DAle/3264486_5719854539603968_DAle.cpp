#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

using Item = tuple<char, int, int>;

int countsum(const vector<string> &v) {
  int res = 0;
  for (string s : v) {
    for (char ch : s) {
      if (ch == 'o')
        res += 2;
      else if (ch != '.')
        res++;
    }
  }
  return res;
}

bool check(int n, const vector<Item> &v) {
  vector<int> col(n, 0);
  vector<int> row(n, 0);
  vector<int> d1(2 * n, 0), d2(2 * n, 0);

  for (auto i : v) {
    char ch;
    int x, y;
    tie(ch, x, y) = i;
    if (ch == 'x') {
      if (++col[y] > 1)
        return false;
      if (++row[x] > 1)
        return false;
    }
    if (ch == '+') {
      if (++d1[x + y] > 1)
        return false;
      if (++d2[x - y + n - 1] > 1)
        return false;
    }
    if (ch == 'o') {
      if (++col[y] > 1)
        return false;
      if (++row[x] > 1)
        return false;
      if (++d1[x + y] > 1)
        return false;
      if (++d2[x - y + n - 1] > 1)
        return false;
    }
  }
  return true;
}

vector<int> r, c, d1, d2;
// vector<string> table, old;

int fd1(int x, int y) { return x + y; }

int fd2(int n, int x, int y) { return x + n - 1 - y; }

bool add(vector<string> &table, int n, int x, int y, char ch) {
  if (ch == '+') {
    if (d1[fd1(x, y)] != 0 || d2[fd2(n, x, y)] != 0)
      return false;
    d1[fd1(x, y)]++;
    d2[fd2(n, x, y)]++;
  } else if (ch == 'x') {
    if (r[x] != 0 || c[y] != 0)
      return false;
    r[x]++;
    c[y]++;
  } else if (ch == 'o') {
    if (d1[fd1(x, y)] != 0 || d2[fd2(n, x, y)] != 0 || r[x] != 0 || c[y] != 0)
      return false;
    r[x]++;
    c[y]++;
    d1[fd1(x, y)]++;
    d2[fd2(n, x, y)]++;
  }
  table[x][y] = ch;
  return true;
}

bool remove(vector<string> &table, int n, int x, int y, char ch) {
  if (ch == '+' || ch == 'o') {
    d1[fd1(x, y)]--;
    d2[fd2(n, x, y)]--;
  } else if (ch == 'x' || ch == 'o') {
    r[x]--;
    c[y]--;
  }
  table[x][y] = '.';
  return true;
}

void assign(int n) {
  r.assign(n, 0);
  c = r;
  d1.assign(2 * n - 1, 0);
  d2 = d1;
}

int main() {
  ios_base::sync_with_stdio(false);
  ifstream ifs("d.in");
  ofstream ofs("d.out");

  int t;
  ifs >> t;
  for (int test = 0; test < t; ++test) {
    int res = 0;
    int n, m;
    ifs >> n >> m;
    assign(n);
    vector<string> table(n, string(n, '.'));
    vector<string> old, table2;
    table2 = table;
    for (int i = 0; i < m; ++i) {
      char ch;
      int x, y;
      ifs >> ch >> x >> y;
      --x;
      --y;
      add(table, n, x, y, ch);
    }
    old = table;
    for (int i = 0; i < n; ++i) {
      if (table[0][i] == '.')
        add(table, n, 0, i, '+');
    }
    for (int i = 1; i < n; ++i) {
      add(table, n, i, n - i - 1, 'x');
    }
    for (int i = 1; i < n; ++i) {
      add(table, n, n - 1, i, '+');
    }

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (table[i][j] != 'o') {
          if (table[i][j] == '.')
            add(table, n, i, j, 'o');
          else {
            char ch = table[i][j];
            remove(table, n, i, j, ch);
            if (!add(table, n, i, j, 'o'))
              add(table, n, i, j, ch);
          }
        }
      }
    }
    int sum = countsum(table);

    assign(n);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        if (old[i][j] != '.')
          add(table2, n, i, j, old[i][j]);
    for (int i = 0; i < n; ++i) {
      if (table2[0][i] == '.')
        add(table2, n, 0, i, '+');
    }
    for (int i = 1; i < n; ++i) {
      add(table2, n, i, i, 'x');
    }
    for (int i = n - 2; i >= 0; --i) {
      add(table2, n, n - 1, i, '+');
    }

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (table2[i][j] != 'o') {
          if (table2[i][j] == '.')
            add(table2, n, i, j, 'o');
          else {
            char ch = table2[i][j];
            remove(table2, n, i, j, ch);
            if (!add(table2, n, i, j, 'o'))
              add(table2, n, i, j, ch);
          }
        }
      }
    }

    int sum2 = countsum(table2);
    if (sum2 > sum) {
      sum = sum2;
      table = table2;
    }
    vector<Item> v;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j) {
        if (old[i][j] != table[i][j]) {
          v.emplace_back(table[i][j], i, j);
        }
      }
    if (!check(n, v)) {
      cout << "ERROR!" << endl;
    }
    ofs << "Case #" << test + 1 << ": " << sum << ' ' << v.size() << endl;
    for (auto i : v) {
      ofs << get<0>(i) << ' ' << get<1>(i) + 1 << ' ' << get<2>(i) + 1 << endl;
    }
  }
  return 0;
}

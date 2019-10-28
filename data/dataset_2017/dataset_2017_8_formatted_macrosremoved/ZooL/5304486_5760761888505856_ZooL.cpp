
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

typedef long long LL;
typedef long double LD;
typedef pair<int, int> pii;

const LD eps = 1e-9;
const LD pi = acos(-1.0);
const LL inf = 1e+9;
// extended template
#pragma comment(linker, "/STACK:36777216")
typedef vector<int> vi;
typedef vector<vi> vvi;

template <typename T> istream &operator>>(istream &, vector<T> &);
template <typename T> ostream &operator<<(ostream &, const vector<T> &);

map<char, int> sp;
vector<string> s;

struct rect {
  pii a, b;
  rect() {}
  rect(pii a, pii b) : a(a), b(b) {}
};
queue<rect> q;
void split(const rect &r) {
  map<char, int> sp2;
  set<char> d, d2;
  for (int i = r.a.first; i <= r.b.first; i++) {
    for (int j = r.a.second; j <= r.b.second; j++) {
      if (s[i][j] != '?')
        d.insert(s[i][j]);
    }
  }
  if (d.size() == 1) {
    char res = *d.begin();
    for (int i = r.a.first; i <= r.b.first; i++) {
      for (int j = r.a.second; j <= r.b.second; j++) {
        s[i][j] = res;
      }
    }
    return;
  }
  d2 = d;

  for (int i = r.a.first; i <= r.b.first; i++) {
    for (int j = r.a.second; j <= r.b.second; j++) {
      if (s[i][j] != '?')
        sp2[s[i][j]]++;
    }
    set<char> dif;
    for (auto v : sp2)
      dif.insert(v.first);

    if (dif.size() == 0)
      continue;

    for (auto v : dif) {
      if (sp2[v] == sp[v]) {
        sp2.erase(v);
        d.erase(v);
      }
    }

    if (sp2.empty() && !d.empty()) {
      q.push(rect(r.a, make_pair(i, r.b.second)));
      q.push(rect(make_pair(i + 1, r.a.second), r.b));
      return;
    }
  }
  sp2.clear();
  d = d2;
  for (int j = r.a.second; j <= r.b.second; j++) {
    for (int i = r.a.first; i <= r.b.first; i++) {
      if (s[i][j] != '?')
        sp2[s[i][j]]++;
    }
    set<char> dif;
    for (auto v : sp2)
      dif.insert(v.first);

    if (dif.size() == 0)
      continue;

    for (auto v : dif) {
      if (sp2[v] == sp[v]) {
        sp2.erase(v);
        d.erase(v);
      }
    }
    if (sp2.empty() && !d.empty()) {
      q.push(rect(r.a, make_pair(r.b.first, j)));
      q.push(rect(make_pair(r.a.first, j + 1), r.b));
      return;
    }
  }
}
void solve() {
  int t;
  cin >> t;
  for (int w = 0; w < t; w++) {
    int n, m;
    cin >> n >> m;
    s.clear();
    s.resize(n);
    sp.clear();
    for (int i = 0; i < n; i++)
      cin >> s[i];

    for (int i = 0; i < n; i++)
      for (int k = 0; k < m; k++)
        if (s[i][k] != '?')
          sp[s[i][k]]++;

    q = queue<rect>();
    q.push(rect(make_pair(0, 0), make_pair(n - 1, m - 1)));

    while (!q.empty()) {
      auto v = q.front();
      q.pop();
      split(v);
    }
    cout << "Case #" << w + 1 << ":" << endl;
    for (int i = 0; i < n; i++)
      cout << s[i] << endl;
  }
}

int main() {

  // START
  // freopen(NAME ".in", "r", stdin); freopen(NAME ".out", "w", stdout);
  freopen("A-small-attempt0 (1).in", "r", stdin);
  freopen("output.txt", "w", stdout);
  solve();

  // END
  return 0;
}
/*******************************************
*******************************************/

template <typename T> istream &operator>>(istream &is, vector<T> &v) {
  for (int i = 0; i < v.size(); ++i)
    is >> v[i];
  return is;
}
template <typename T> ostream &operator<<(ostream &os, const vector<T> &v) {
  for (int i = 0; i < v.size(); ++i)
    os << v[i] << " ";
  return os;
}

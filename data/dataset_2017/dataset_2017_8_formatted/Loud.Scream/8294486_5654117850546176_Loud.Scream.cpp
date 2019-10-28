#include <bits/stdc++.h>

using namespace std;

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define ld long double
#define ll long long
#define uint unsigned int
#define all(a) a.begin(), a.end()
#ifdef DEBUG
#define NAME "1"
#else
#define NAME "fox-blocks"
#endif
#define FREOPEN                                                                \
  freopen(NAME ".in", "r", stdin);                                             \
  freopen(NAME ".out", "w", stdout)
#define PI 3.1415926535897932384626433832795

const double EPS = 1e-9;
const double INF = 1e15;

bool check(const string &s) {
  bool res = 0;
  if (s.size() == 1)
    return 0;
  int sz = (int)s.size();
  for (int i = 0; i <= s.size(); ++i) {
    int j = (i + 1) % (sz);
    if (s[i] == s[j])
      res = 1;
  }
  return res;
}

void change(string &s) {
  int sz = (int)s.size();
  int i = 0;
  for (i = 0; i <= s.size(); ++i) {
    int j = (i + 1) % (sz);
    if (s[i] == s[j]) {
      int pr = (i - 1 + sz) % sz;
      swap(s[pr], s[i]);
      break;
      i += 2;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  cout << fixed << setprecision(7);
  for (int qq = 1; qq <= t; ++qq) {
    cout << "Case #" << qq << ": ";
    int n;
    cin >> n;
    char C[3];
    C[0] = 'R', C[1] = 'Y', C[2] = 'B';
    vector<pair<int, int>> mas;
    int cnt = 0;
    for (int i = 0; i < 6; ++i) {
      int a;
      cin >> a;
      if (i % 2 == 0) {
        mas.push_back({a, cnt++});
      }
    }
    sort(all(mas));
    string h;
    char last = '-';
    while (min(mas[1].first, mas[2].first) > 0) {
      if (last != C[mas[2].second]) {
        h += C[mas[2].second];
        --mas[2].first;
      } else {
        h += C[mas[1].second];
        --mas[1].first;
      }
      last = h.back();
    }
    sort(all(mas));
    for (int i = h.size(); i < n; ++i) {
      if (last != C[mas[2].second]) {
        h += C[mas[2].second];
        --mas[2].first;
      } else {
        h += C[mas[1].second];
        --mas[1].first;
      }
      last = h.back();
      sort(all(mas));
    }
    bool res = check(h);
    if (!res) {
      cout << h << "\n";
      continue;
    }
    bool kek = 0;
    for (int tt = 0; tt < 1000; ++tt) {
      change(h);
      res = check(h);
      if (!res) {
        cout << h << "\n";
        kek = 1;
        break;
      }
    }
    if (kek)
      continue;
    cout << "IMPOSSIBLE\n";
  }
  return 0;
}
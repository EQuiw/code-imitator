#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_set;

const int N = 1e6 + 7, inf = 1e9 + 7, mod = 1e9 + 7;
const ll linf = (ll)1e18 + 7;
const int dx[] = {-1, 0, 1, 0, 1, -1, -1, 1},
          dy[] = {0, 1, 0, -1, 1, -1, 1, -1};

int n, m;
char c[33][33], cur[33][33];

struct node {
  int x1, y1, x2, y2;
  node() {}
  node(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
} a[26];
bool cmp(char x, char y) { return a[x - 'a'].x2 > a[y - 'a'].x2; }
int get(int x) { return ((rand() << 16) + rand()) % x + 1; }
void gen() {
  n = get(25), m = get(25);

  set<char> st;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      char x = get(26) - 1;
      if (st.count(x))
        c[i][j] = '?';
      else
        c[i][j] = x + 'A';
      st.insert(x);
    }
  }
}
void solve(int _id) {
  cin >> n >> m;
  // gen();
  vector<char> v;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> c[i][j];
      cur[i][j] = c[i][j];
      if (isalpha(c[i][j]))
        a[c[i][j] - 'a'] = node(i, j, i, j), v.push_back(c[i][j]);
    }
    //  cout << nl;
  }

  sort(v.begin(), v.end(), cmp);
  for (int blin = 1; blin <= 10000; blin++) {
    for (auto z : v) {
      int u = a[z - 'a'].x1, l = a[z - 'a'].y1, r = a[z - 'a'].y2;
      for (int i = u - 1; i >= 1; i--) {
        bool good = 1;
        for (int j = l; j <= r; j++)
          if (isalpha(c[i][j])) {
            good = 0;
            break;
          }
        if (!good)
          break;
        for (int j = l; j <= r; j++)
          c[i][j] = z;
        a[z - 'a'].x1 = i;
      }
      int d = a[z - 'a'].x2;
      for (int i = d + 1; i <= n; i++) {
        bool good = 1;
        for (int j = l; j <= r; j++)
          if (isalpha(c[i][j])) {
            good = 0;
            break;
          }
        if (!good)
          break;
        for (int j = l; j <= r; j++)
          c[i][j] = z;
        a[z - 'a'].x2 = i;
      }
      u = a[z - 'a'].x1, d = a[z - 'a'].x2;
      for (int i = r + 1; i <= m; i++) {
        bool good = 1;
        for (int j = u; j <= d; j++)
          if (isalpha(c[j][i])) {
            good = 0;
            break;
          }
        if (!good)
          break;
        for (int j = u; j <= d; j++)
          c[j][i] = z;
        a[z - 'a'].y2 = i;
      }
      for (int i = l - 1; i >= 1; i--) {
        bool good = 1;
        for (int j = u; j <= d; j++)
          if (isalpha(c[j][i])) {
            good = 0;
            break;
          }
        if (!good)
          break;
        for (int j = u; j <= d; j++)
          c[j][i] = z;
        a[z - 'a'].y1 = i;
      }
    }
    bool good = 1;
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++) {
        if (c[i][j] == '?') {
          good = 0;
          break;
        }
      }
    if (good)
      break;
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++)
        c[i][j] = cur[i][j];
    random_shuffle(v.begin(), v.end());
  }

  cout << "Case #" << _id << ":\n";
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cout << c[i][j];
      assert(c[i][j] != '?');
    }
    cout << '\n';
  }
}

int T;
int main() {

  // Kazakhstan
  srand(time(0));
  cin >> T;
  for (int i = 1; i <= T; i++)
    solve(i);
  exit(0);
}

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

const int N = 100 + 7, inf = 1e9 + 7, mod = 1e9 + 7;
const ll linf = (ll)1e18 + 7;
const int dx[] = {-1, 0, 1, 0, 1, -1, -1, 1},
          dy[] = {0, 1, 0, -1, 1, -1, 1, -1};

int n;
pair<int, int> a[7], b[7];
char c[] = {' ', 'R', 'O', 'Y', 'G', 'B', 'V'};
map<char, set<char>> bad;
bool check(char x, char y) {
  if (bad[x].count(y))
    return 0;
  return 1;
}
bool checkid(int x) {
  for (int i = 1; i <= 6; i++)
    if (a[i].second == x && a[i].first > 0)
      return 1;
  return 0;
}
void solve(int testcase) {
  cin >> n;
  for (int i = 1; i <= 6; i++)
    cin >> a[i].first, a[i].second = i;
  sort(a + 1, a + 1 + 6, greater<pair<int, int>>());
  for (int i = 1; i <= 6; i++)
    b[i] = a[i];
  int l = 1, r = 1;
  while (r + 1 <= n && a[r + 1].first == a[r].first)
    r++;
  cout << "Case #" << testcase << ": ";
  for (int i = 1; i <= 6; i++) {
    if (!a[i].first)
      break;
    string ans;
    ans += c[a[i].second];
    while ((int)ans.size() < n) {
      bool done = 0;
      for (int j = 1; j <= 6; j++) {
        if (a[j].first && check(ans.back(), c[a[j].second]))
          a[j].first--, ans += c[a[j].second], done = 1;
      }
      if (!done)
        break;
    }
    bool ok = 1;
    for (int j = 0; j <= (int)ans.size() - 1; j++)
      if (!check(ans[j], ans[(j + 1) % n])) {
        ok = 0;
        break;
      }
    if (ok && (int)ans.size() == n) {
      cout << ans << '\n';
      return;
    }
    for (int j = 1; j <= 6; j++)
      a[j] = b[j];
  }
  cout << "IMPOSSIBLE\n";
}
int main() {

  freopen("B-small-attempt2"
          ".in",
          "r", stdin);
  freopen("B-small-attempt2"
          ".out",
          "w", stdout);

  ios_base ::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  bad['R'].insert('R');
  bad['R'].insert('O');
  bad['R'].insert('V');

  bad['O'].insert('O');
  bad['O'].insert('V');
  bad['O'].insert('G');
  bad['O'].insert('R');
  bad['O'].insert('Y');

  bad['Y'].insert('Y');
  bad['Y'].insert('G');
  bad['Y'].insert('O');

  bad['G'].insert('G');
  bad['G'].insert('Y');
  bad['G'].insert('B');
  bad['G'].insert('O');
  bad['G'].insert('V');

  bad['B'].insert('B');
  bad['B'].insert('G');
  bad['B'].insert('V');

  bad['V'].insert('V');
  bad['V'].insert('R');
  bad['V'].insert('B');
  bad['V'].insert('G');
  bad['V'].insert('O');

  int T = 1;
  cin >> T;
  for (int i = 1; i <= T; i++)
    solve(i);
  exit(0);
}

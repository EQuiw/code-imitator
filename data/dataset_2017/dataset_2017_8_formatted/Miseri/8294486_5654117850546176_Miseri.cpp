#include <bits/stdc++.h>
#define pb push_back
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;

const int N = 1111;
const int M = N * N * 10;

int T, n;

int cnt[10];

// ROYGBV
string c = "ROYGBV";
int re[10][10];

void adre(int i, int j) { re[i][j] = re[j][i] = 1; }

bool dfs(string &s, int lc = 8) {
  if ((int)s.size() == n && s[0] != s[n - 1])
    return true;
  // cout << s <<endl;
  vector<pair<int, int>> v;
  for (int nc = 0; nc < 6; nc++) {
    if (re[lc][nc] || !cnt[nc])
      continue;
    v.pb({cnt[nc], nc});
  }
  sort(v.begin(), v.end());
  reverse(v.begin(), v.end());
  for (auto p : v) {
    int nc = p.second;
    if (re[lc][nc] || !cnt[nc])
      continue;
    s += c[nc];
    cnt[nc]--;
    if (dfs(s, nc))
      return true;
    s.pop_back();
    cnt[nc]++;
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  for (int i = 0; i < 6; i++) {
    adre(i, i);
    adre(i, (i + 1) % 6);
  }
  cin >> T;
  cout << fixed << setprecision(10);
  for (int it = 0; it < T; it++) {
    cin >> n;
    bool pos = true;
    for (int i = 0; i < 6; i++) {
      cin >> cnt[i];
      if (cnt[i] > n / 2)
        pos = false;
    }
    string ans = "";
    if (pos)
      pos = dfs(ans);
    if (!pos)
      ans = "IMPOSSIBLE";
    cout << "Case #" << it + 1 << ": " << ans << endl;
  }
}

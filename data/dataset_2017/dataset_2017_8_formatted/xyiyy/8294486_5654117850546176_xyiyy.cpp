#include <bits/stdc++.h>
using namespace std;
#define mp(X, Y) make_pair(X, Y)
#define F first
#define S second
typedef long long ll;
typedef pair<int, int> PII;
typedef pair<ll, ll> PLL;

int main() {
  ios::sync_with_stdio(0);
  freopen("2.in", "r", stdin);
  freopen("2.out", "w", stdout);
  int cas = 1;
  int t;
  cin >> t;
  while (t--) {
    cout << "Case #" << cas++ << ": ";
    int n, r, o, y, g, b, v;
    cin >> n >> r >> o >> y >> g >> b >> v;
    vector<pair<int, char>> vec;
    vec.push_back(mp(r, 'R'));
    vec.push_back(mp(y, 'Y'));
    vec.push_back(mp(b, 'B'));
    sort(vec.begin(), vec.end());
    bool ok = true;
    if (vec[2].F > vec[0].F + vec[1].F)
      ok = false;
    if (!ok) {
      cout << "IMPOSSIBLE" << endl;
    } else {
      string str = "";
      char last = 0;
      while (vec[2].F) {
        int idx = 2;
        if (vec[idx].S == last)
          idx--;
        if (vec[idx].F == 0) {
          break;
        }
        last = vec[idx].S;
        vec[idx].F--;
        str = str + vec[idx].S;
        while (idx && vec[idx].F < vec[idx - 1].F) {
          swap(vec[idx], vec[idx - 1]);
          idx--;
        }
      }
      int sum = vec[2].F;
      // cout << sum <<endl;
      int len = str.length();
      if (str[0] == str[len - 1]) {
        sum++;
        len--;
      }
      char p = vec[2].S;
      string ans = "";
      for (int i = 0; i < len; i++) {
        ans += str[i];
        if (i < len - 1 && p != str[i] && p != str[i + 1] && sum) {
          ans += p;
          sum--;
        }
      }
      if (sum) {
        cout << "IMPOSSIBLE" << endl;
      } else {
        cout << ans << endl;
      }
    }
  }
  return 0;
}

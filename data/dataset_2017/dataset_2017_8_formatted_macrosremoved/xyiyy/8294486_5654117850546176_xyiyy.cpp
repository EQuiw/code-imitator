#include <bits/stdc++.h>
using namespace std;

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
    vec.push_back(make_pair(r, 'R'));
    vec.push_back(make_pair(y, 'Y'));
    vec.push_back(make_pair(b, 'B'));
    sort(vec.begin(), vec.end());
    bool ok = true;
    if (vec[2].first > vec[0].first + vec[1].first)
      ok = false;
    if (!ok) {
      cout << "IMPOSSIBLE" << endl;
    } else {
      string str = "";
      char last = 0;
      while (vec[2].first) {
        int idx = 2;
        if (vec[idx].second == last)
          idx--;
        if (vec[idx].first == 0) {
          break;
        }
        last = vec[idx].second;
        vec[idx].first--;
        str = str + vec[idx].second;
        while (idx && vec[idx].first < vec[idx - 1].first) {
          swap(vec[idx], vec[idx - 1]);
          idx--;
        }
      }
      int sum = vec[2].first;
      // cout << sum <<endl;
      int len = str.length();
      if (str[0] == str[len - 1]) {
        sum++;
        len--;
      }
      char p = vec[2].second;
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

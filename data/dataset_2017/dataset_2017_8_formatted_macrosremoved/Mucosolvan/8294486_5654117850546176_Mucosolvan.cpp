#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<pii, int> para;
const int inf = 1e9 + 7;
const int maxN = 1e6 + 5;
const int M = 50;
const int N = 50;

int t, r, o, y, g, b, v, ans[maxN], sum;
set<pii, greater<pii>> s;

int main() {
  ios_base::sync_with_stdio(0);
  cin >> t;
  for (int test = (1); test <= ((t)); ++test) {
    cin >> sum >> r >> o >> y >> g >> b >> v;
    s.clear();
    if (r > 0)
      s.insert(pii(r, 1));
    if (y > 0)
      s.insert(pii(y, 2));
    if (b > 0)
      s.insert(pii(b, 3));
    int maxim = max(r, y);
    maxim = max(maxim, b);
    cout << "Case #" << test << ": ";
    // s.clear();
    if (maxim > sum / 2) {
      cout << "IMPOSSIBLE";
    } else {
      pii x = *s.begin();
      s.erase(s.begin());
      ans[0] = x.second;
      s.insert(pii(x.first - 1, x.second));

      int cnt = 1;
      while (cnt < sum) {
        pii x = *s.begin();
        if (x.second == ans[cnt - 1]) {
          pii tmp = x;
          s.erase(s.begin());
          x = *s.begin();
          ans[cnt] = x.second;
          s.erase(s.begin());
          if (x.first > 0)
            s.insert(pii(x.first - 1, x.second));
          s.insert(tmp);
        } else {
          // cout<<x.st<<" "<<x.nd<<endl;
          ans[cnt] = x.second;
          s.erase(s.begin());
          if (x.first > 0)
            s.insert(pii(x.first - 1, x.second));
        }
        cnt++;
      }
      if (ans[sum - 1] == ans[0]) {
        swap(ans[sum - 1], ans[sum - 2]);
        if (ans[sum - 2] == ans[sum - 3]) {
          cout << "IMPOSSIBLE";
        } else {
          for (int i = (0); i <= ((sum)-1); ++i) {
            if (ans[i] == 1)
              cout << "R";
            if (ans[i] == 2)
              cout << "Y";
            if (ans[i] == 3)
              cout << "B";
          }
        }
      } else {
        for (int i = (0); i <= ((sum)-1); ++i) {
          if (ans[i] == 1)
            cout << "R";
          if (ans[i] == 2)
            cout << "Y";
          if (ans[i] == 3)
            cout << "B";
        }
      }
    }
    cout << endl;
  }
  return 0;
}

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

int main() {

  int tt;
  cin >> tt;
  for (int qq = 1; qq <= tt; qq++) {
    printf("Case #%d: ", qq);
    ll n, k;
    cin >> n >> k;
    vector<vector<pair<ll, ll>>> lvl;
    lvl.push_back(vector<pair<ll, ll>>(1, make_pair(n, 1ll)));
    for (int i = 0; i < ((int)(lvl).size()); i++) {
      ll nexta = -1, cnta = 0, nextb = -1, cntb = 0;
      for (int j = 0; j < ((int)(lvl[i]).size()); j++) {
        ll cur = lvl[i][j].first, cnt = lvl[i][j].second;
        if (cur == 1)
          continue;
        ll a = (cur - 1) / 2;
        ll b = (cur - 1) - a;
        ll ca = a ? cnt : 0;
        ll cb = cnt;
        if (a > 0) {
          if (nexta == -1 || nexta == a) {
            nexta = a;
            cnta += ca;
          } else {
            nextb = a;
            cntb += ca;
          }
        }
        if (b > 0) {
          if (nexta == -1 || nexta == b) {
            nexta = b;
            cnta += cb;
          } else {
            nextb = b;
            cntb += cb;
          }
        }
      }
      if (nexta != -1)
        lvl.push_back(vector<pair<ll, ll>>(1, make_pair(nexta, cnta)));
      if (nextb != -1)
        lvl[((int)(lvl).size()) - 1].push_back(make_pair(nextb, cntb));
    }
    ll ans1 = -1, ans2 = -1;
    for (int i = 0; i < ((int)(lvl).size()); i++) {
      if (ans1 != -1)
        break;
      for (int j = ((int)(lvl[i]).size()) - 1; j >= 0; j--) {
        ll cur = lvl[i][j].first, sum = lvl[i][j].second;
        if (k <= sum) {
          ans1 = (cur - 1) / 2;
          ans2 = (cur - 1) - ans1;
          break;
        } else {
          k -= sum;
        }
      }
    }
    cout << ans2 << ' ' << ans1 << endl;
  }

  return 0;
}

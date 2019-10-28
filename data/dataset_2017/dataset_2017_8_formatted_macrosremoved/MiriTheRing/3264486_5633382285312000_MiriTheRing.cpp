#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;
using vvl = vector<vl>;
using pll = pair<ll, ll>;
using vb = vector<bool>;
const ll oo = 0x3f3f3f3f3f3f3f3fLL;
const double eps = 1e-9;
bool tidy(string a) {
  for (ll i = (1); i < (ll((a).size())); i++) {
    if (a[i - 1] > a[i])
      return false;
  }
  return true;
}

int main() {
  ios::sync_with_stdio(false);
  vl nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  vl swap;
  for (ll l = (2); l < (19); l++) {
    swap = vl();
    for (ll i = (1); i < (10); i++) {
      for (ll j = (ll((nums).size())) - 1; j >= (0); j--) {
        if (ll((to_string(nums[j])).size()) < l - 1)
          break;
        char c = ('0' + i);
        string num = to_string(nums[j]);
        num += c;
        if (tidy(num)) {
          swap.push_back(stoll(num));
        }
      }
    }
    for (ll i = (0); i < (ll((swap).size())); i++)
      nums.push_back(swap[i]);
  }
  sort(begin(nums), end(nums));
  ll TC;
  cin >> TC;
  for (ll tc = (0); tc < (TC); tc++) {
    ll n;
    cin >> n;
    auto ptr = upper_bound(begin(nums), end(nums), n);
    ptr--;
    cout << "Case #" << tc + 1 << ": " << *ptr << endl;
  }
}

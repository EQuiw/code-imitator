#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;
using vvl = vector<vl>;
using pll = pair<ll, ll>;
using vb = vector<bool>;
const ll oo = 0x3f3f3f3f3f3f3f3fLL;
const double eps = 1e-9;
map<ll, char> m = {{0, 'R'}, {1, 'O'}, {2, 'Y'}, {3, 'G'}, {4, 'B'}, {5, 'V'}};

int main() {
  ios::sync_with_stdio(false);
  ll TC;
  cin >> TC;
  for (ll tc = (1); tc < (TC + 1); tc++) {
    cout << "Case #" << tc << ": ";
    vector<pll> nums;
    ll n, last = 0;
    ll first;
    cin >> n;
    bool poss = true;
    for (ll i = (0); i < (6); i++) {
      ll k;
      cin >> k;
      nums.push_back(make_pair(k, i));
    }
    sort(nums.rbegin(), nums.rend());
    if (nums[0].first > (n) / 2) {
      poss = false;
    }
    string res = "";
    for (ll i = (0); i < (n); i++) {
      res += "R";
    }
    ll idx = 0;
    for (ll i = (0); i < (ll((nums).size())); i++) {
      while (nums[i].first) {
        res[idx] = m[nums[i].second];
        nums[i].first--;
        idx += 2;
        if (idx >= n)
          idx = 1;
      }
    }

    /*
    string res = "";
    res += m[last];
    first = last;
    num[last]--;
    FOR(i,1,n){
      ll next_idx = -1;
      ll next_num = 0;
      FOR(j,last+2, last+5){
        if(num[j%6] > next_num){
          next_num = num[j%6];
          next_idx = j%6;
        }
      }
      if(next_idx == -1){
        poss = false;
        break;
      }
      last = next_idx;
      res += m[last];
      num[last]--;
    }

    if(poss){
      poss = false;
    FOR(j, last+2, last+5){
      if(j == first) poss = true;
    }
    }
    cerr << res << endl;
    */
    if (poss)
      cout << res << endl;
    else
      cout << "IMPOSSIBLE" << endl;
  }
}

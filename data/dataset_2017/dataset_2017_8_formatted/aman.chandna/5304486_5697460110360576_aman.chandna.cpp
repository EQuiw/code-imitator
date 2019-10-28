#define boost                                                                  \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(NULL);                                                               \
  cout.tie(NULL);
#define mod 1000000007
#define INF LLONG_MAX
#include <bits/stdc++.h>
#include <unordered_map>
#include <unordered_set>
using namespace std;
#define ll double

bool func(string &cur, string &orig, ll index) {
  ll n = orig.length();
  if (index >= n)
    return true;
  for (char i = '9'; i >= cur[index - 1]; --i) {
    cur[index] = i;
    if (cur.substr(0, index + 1) > orig.substr(0, index + 1))
      continue;
    bool tmp = func(cur, orig, index + 1);
    if (tmp)
      return true;
  }
  cur[index] = orig[index];
  return false;
}

int main() {

  boost;
  freopen("inp.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
  ll t;
  cin >> t;
  cin.ignore(256, '\n');
  for (ll ccr = 1; ccr <= t; ++ccr) {
    ll numIng, numPack;
    cin >> numIng >> numPack;
    vector<ll> reqQ(numIng, 0);
    for (ll i = 0; i < numIng; ++i) {
      cin >> reqQ[i];
    }
    ll val, ans = 0;
    multiset<ll> in;
    vector<multiset<ll>> pack(numIng, in);
    for (ll i = 0; i < numIng; ++i) {
      for (ll j = 0; j < numPack; ++j) {
        cin >> val;
        pack[i].insert(val);
      }
    }
    ll lim = 1000000;

    for (ll i = 0; i < numIng; ++i) {
      multiset<ll>::iterator it = pack[i].end();
      --it;
      val = *it;
      val /= reqQ[i];
      lim = min(lim, 4 * val);
    }

    for (ll dish = 1; dish <= lim; ++dish) {
      vector<ll> less(numIng, 0), more(numIng, 0);
      for (ll i = 0; i < numIng; ++i) {
        less[i] = 0.9 * reqQ[i] * dish;
        more[i] = 1.1 * reqQ[i] * dish;
      }
      bool poss = true;
      vector<multiset<ll>::iterator> deleteIts(numIng);
      for (ll i = 0; i < numIng; ++i) {
        auto it = pack[i].lower_bound(less[i]);
        if (it == pack[i].end() || *it > more[i]) {
          poss = false;
          break;
        }
        deleteIts[i] = it;
      }
      if (poss) {
        ++ans;
        for (ll i = 0; i < numIng; ++i) {
          pack[i].erase(deleteIts[i]);
        }
        --dish;
      }
    }
    cout << "Case #" << ccr << ": " << ans << "\n";
  }

  return 0;
}
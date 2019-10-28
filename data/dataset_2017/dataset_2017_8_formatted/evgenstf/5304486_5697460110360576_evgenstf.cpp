#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#define X first
#define Y second

using namespace std;

typedef long long ll;

const ll dd = 1e6;
const ll inf = 1e9 + 7;

const double eps = 1e-8;

multiset<ll> dt;

int main() {
  //#ifdef _DEBUG
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  //#endif

  ll t;
  cin >> t;
  for (ll tt = 0; tt < t; ++tt) {
    cerr << tt << endl;
    ll n, m;
    cin >> n >> m;
    vector<ll> recipe;
    vector<vector<ll>> twopack(n, vector<ll>(m));
    for (ll i = 0; i < n; ++i) {
      ll x;
      cin >> x;
      recipe.push_back(x);
    }
    for (ll i = 0; i < n; ++i)
      for (ll j = 0; j < m; ++j)
        cin >> twopack[i][j];
    ll gans = 0;
    {
      vector<vector<ll>> pack = twopack;
      for (ll i = 0; i < n; ++i)
        sort(pack[i].begin(), pack[i].end());
      ll llans = 0;
      for (ll k = 1; k < 1000001; ++k) {
        ll ans = inf;
        for (ll i = 0; i < n; ++i) {
          ll cnt = 0;
          for (ll j = 0; j < m; ++j) {
            ll x;
            x = pack[i][j];
            if (90 <= x * 100 / (recipe[i] * k) &&
                x * 100 / (recipe[i] * k) <= 110)
              ++cnt;
          }
          ans = min(cnt, ans);
          if (ans == 0)
            break;
        }
        if (ans == 0)
          continue;
        for (ll i = 0; i < n; ++i) {
          ll cnt = 0;
          for (ll j = 0; j < m; ++j) {
            ll x;
            x = pack[i][j];
            if (90 <= x * 100 / (recipe[i] * k) &&
                x * 100 / (recipe[i] * k) <= 110) {
              if (cnt < ans)
                pack[i][j] = 0;
              ++cnt;
            }
          }
        }
        if (ans != 0)
          llans += ans;
      }
      gans = max(gans, llans);
    }
    {
      vector<vector<ll>> pack = twopack;
      for (ll i = 0; i < n; ++i)
        sort(pack[i].rbegin(), pack[i].rend());
      ll llans = 0;
      for (ll k = 1; k < 1000001; ++k) {
        ll ans = inf;
        for (ll i = 0; i < n; ++i) {
          ll cnt = 0;
          for (ll j = 0; j < m; ++j) {
            ll x;
            x = pack[i][j];
            if (90 <= x * 100 / (recipe[i] * k) &&
                x * 100 / (recipe[i] * k) <= 110)
              ++cnt;
          }
          ans = min(cnt, ans);
          if (ans == 0)
            break;
        }
        if (ans == 0)
          continue;
        for (ll i = 0; i < n; ++i) {
          ll cnt = 0;
          for (ll j = 0; j < m; ++j) {
            ll x;
            x = pack[i][j];
            if (90 <= x * 100 / (recipe[i] * k) &&
                x * 100 / (recipe[i] * k) <= 110) {
              if (cnt < ans)
                pack[i][j] = 0;
              ++cnt;
            }
          }
        }
        if (ans != 0)
          llans += ans;
      }
      gans = max(gans, llans);
    }
    for (ll r = 0; r < 5; ++r) {
      vector<vector<ll>> pack = twopack;
      for (ll i = 0; i < n; ++i)
        random_shuffle(pack[i].begin(), pack[i].end());
      ll llans = 0;
      for (ll k = 1; k < 1000001; ++k) {
        ll ans = inf;
        for (ll i = 0; i < n; ++i) {
          ll cnt = 0;
          for (ll j = 0; j < m; ++j) {
            ll x;
            x = pack[i][j];
            if (90 <= x * 100 / (recipe[i] * k) &&
                x * 100 / (recipe[i] * k) <= 110)
              ++cnt;
          }
          ans = min(cnt, ans);
          if (ans == 0)
            break;
        }
        if (ans == 0)
          continue;
        for (ll i = 0; i < n; ++i) {
          ll cnt = 0;
          for (ll j = 0; j < m; ++j) {
            ll x;
            x = pack[i][j];
            if (90 <= x * 100 / (recipe[i] * k) &&
                x * 100 / (recipe[i] * k) <= 110) {
              if (cnt < ans)
                pack[i][j] = 0;
              ++cnt;
            }
          }
        }
        if (ans != 0)
          llans += ans;
      }
      gans = max(gans, llans);
    }
    cout << "Case #" << tt + 1 << ": " << gans << endl;
  }

  return 0;
}

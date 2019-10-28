#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ii> vii;

set<ll> mark;
map<ll, map<ll, ll>> dp;
void dfs(ll n) {
  if (n == 0 || mark.count(n))
    return;
  mark.insert(n);
  if (n % 2) {
    dfs(n / 2);
    map<ll, ll> tmp;
    for (auto i : dp[n / 2]) {
      tmp[i.first] += 2 * i.second;
    }
    tmp[n] += 1;
    dp[n] = tmp;
  } else {
    dfs(n / 2);
    dfs(n / 2 - 1);
    map<ll, ll> tmp;
    for (auto i : dp[n / 2]) {
      tmp[i.first] += i.second;
    }
    for (auto i : dp[n / 2 - 1]) {
      tmp[i.first] += i.second;
    }
    tmp[n] += 1;
    dp[n] = tmp;
  }
}

vector<pair<ll, ll>> data;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  ;
  int T;
  cin >> T;
  for (int test = 1; test < T + 1; test++) {
    cout << "Case #" << test << ": ";
    mark.clear();
    dp.clear();
    data.clear();
    ll n, k;
    cin >> n >> k;
    dfs(n);
    for (auto i : dp[n]) {
      data.push_back(make_pair(i.first, i.second));
    }
    sort((data).rbegin(), (data).rend());

    ll aux = -1;
    for (auto i : data) {
      if (k <= i.second) {
        aux = i.first;
        break;
      } else {
        k -= i.second;
      }
    }
    assert(aux != -1);
    if (aux % 2) {
      cout << aux / 2 << " " << aux / 2 << endl;
    } else {
      cout << aux / 2 << " " << aux / 2 - 1 << endl;
    }
  }
  return 0;
}

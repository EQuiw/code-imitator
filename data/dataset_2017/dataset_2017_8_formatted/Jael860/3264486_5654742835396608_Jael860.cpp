#include <bits/stdc++.h>

#define debug(x) cerr << #x << ": " << x << endl;
#define print(x) cerr << x << endl;

#define mp make_pair
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define REP(i, x, y) for (int i = x; i < y; i++)
#define REPIT(it, A)                                                           \
  for (typeof(A.begin()) it = (A.begin()); it != A.end(); it++)
#define fst first
#define snd second
#define sqr(x) ((x) * (x))

#define fastio                                                                 \
  ios_base::sync_with_stdio(0);                                                \
  cin.tie(0);
#define ones(x) __builtin_popcountll(x)
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
      tmp[i.fst] += 2 * i.snd;
    }
    tmp[n] += 1;
    dp[n] = tmp;
  } else {
    dfs(n / 2);
    dfs(n / 2 - 1);
    map<ll, ll> tmp;
    for (auto i : dp[n / 2]) {
      tmp[i.fst] += i.snd;
    }
    for (auto i : dp[n / 2 - 1]) {
      tmp[i.fst] += i.snd;
    }
    tmp[n] += 1;
    dp[n] = tmp;
  }
}

vector<pair<ll, ll>> data;

int main() {
  fastio;
  int T;
  cin >> T;
  REP(test, 1, T + 1) {
    cout << "Case #" << test << ": ";
    mark.clear();
    dp.clear();
    data.clear();
    ll n, k;
    cin >> n >> k;
    dfs(n);
    for (auto i : dp[n]) {
      data.pb(mp(i.fst, i.snd));
    }
    sort(rall(data));

    ll aux = -1;
    for (auto i : data) {
      if (k <= i.snd) {
        aux = i.fst;
        break;
      } else {
        k -= i.snd;
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

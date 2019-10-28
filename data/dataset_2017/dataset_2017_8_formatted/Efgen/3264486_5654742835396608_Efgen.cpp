#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef vector<vector<int>> vvi;
typedef vector<ll> vl;
typedef vector<vector<ll>> vvl;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define forv(i, v) forn(i, v.size())
#define all(v) v.begin(), v.end()
#define mp make_pair
#define pb push_back

void add(queue<pair<ll, ll>> &a, ll val, ll cnt) {
  if (!a.empty() && a.back().first == val)
    a.back().second += cnt;
  else {
    a.push({val, cnt});
  }
}

void solveTask() {
  ll n, k;
  cin >> n >> k;
  queue<pair<ll, ll>> a;

  add(a, n, 1);
  ll L, R;
  while (k > 0) {
    auto cur = a.front();
    a.pop();
    ll val = cur.first;
    ll cnt = cur.second;
    if (val & 1) {
      L = R = (val - 1) / 2;
    } else {
      L = val / 2;
      R = val / 2 - 1;
    }
    add(a, L, cnt);
    add(a, R, cnt);
    k -= cnt;
  }
  cout << L << " " << R;
}

int main() {
#ifdef EFGEN_DBG
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int tests;
  cin >> tests;
  for (int test = 1; test <= tests; test++) {
    cout << "Case #" << test << ": ";
    solveTask();
    cout << endl;
  }
}

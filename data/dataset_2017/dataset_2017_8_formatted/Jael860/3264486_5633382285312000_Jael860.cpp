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

vi v;
int m;
ll getVal(int id) {
  ll val = 0;
  int bf = 0;
  REP(i, 0, id) {
    val *= 10;
    if (bf > v[i])
      return -1;
    bf = v[i];
    val += v[i];
  }

  if (bf >= v[id])
    return -1;
  val *= 10;
  val += v[id] - 1;

  REP(i, id + 1, m) {
    val *= 10;
    val += 9;
  }

  return val;
}

int main() {
  fastio;
  int T;
  cin >> T;
  REP(test, 1, T + 1) {
    cout << "Case #" << test << ": ";
    string s;
    cin >> s;
    v.clear();
    REP(i, 0, s.size()) { v.pb(s[i] - '0'); }

    m = v.size();
    if (m == 1) {
      cout << v[0] << endl;
      continue;
    }
    ll res = 0;
    REP(i, 0, m - 1) {
      res *= 10;
      res += 9;
    }
    ll tmp = v[0];
    bool flg = false;
    REP(i, 1, v.size()) {
      if (v[i - 1] > v[i])
        flg = true;
      tmp *= 10;
      tmp += v[i];
    }
    if (!flg)
      res = max(res, tmp);
    REP(i, 0, v.size()) {
      ll val = getVal(i);
      res = max(res, val);
    }
    cout << res << endl;
  }
  return 0;
}

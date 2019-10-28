#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (int(i) = 0; (i) < (int)(n); ++(i))
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define fi first
#define se second

const string ng = "IMPOSSIBLE";

using P = pair<int, char>;

bool check(string s) {
  int S = s.size();
  if (s[0] == s[S - 1])
    return false;
  rep(i, S - 1) if (s[i] == s[i + 1]) return false;
  return true;
}

string small_solve() {
  int n, R, O, Y, G, B, V;
  cin >> n >> R >> O >> Y >> G >> B >> V;

  int m = max({R, Y, B});
  if (2 * m > n) {
    // printf(" INPUT %d %d %d\n", R,Y,B);
    return ng;
  }
  // return " ";

  vector<P> p;
  p.pb(P(R, 'R'));
  p.pb(P(Y, 'Y'));
  p.pb(P(B, 'B'));
  sort(all(p));

  string s(n, ' ');
  rep(i, p[2].fi) s[2 * i] = p[2].se;

  int st = n - 1;
  if (n % 2 == 1)
    --st;
  rep(i, p[1].fi) s[st - 2 * i] = p[1].se;

  rep(i, n) if (s[i] == ' ') s[i] = p[0].se;

  assert(check(s));

  return s;
}

int main() {
  int T;
  cin >> T;
  rep(t, T) {
    printf("Case #%d: ", t + 1);
    cout << small_solve() << endl;
  }
  return 0;
}

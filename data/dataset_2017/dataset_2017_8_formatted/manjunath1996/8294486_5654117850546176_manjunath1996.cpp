#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define dbg(x) cout << #x << "=" << x << endl
#define MOD 786433
#define pb push_back
#define iosbase ios_base::sync_with_stdio(false)
#define dbg(x) cout << #x << "=" << x << endl

vector<pair<double, double>> node;
int main() {

  ll t, n, tc, N, R, O, Y, G, B, V, fl, tk;
  string ans;
  cin >> t;
  for (tc = 1; tc <= t; tc++) {
    fl = 0;
    ans = "";
    printf("Case #%lld: ", tc);
    cin >> N >> R >> O >> Y >> G >> B >> V;
    N--;
    if (R >= Y && R >= B) {
      ans += 'R';
      R--;

    } else if (Y >= R && Y >= B) {
      ans += 'Y';
      Y--;
    } else {
      ans += 'B';
      B--;
    }

    for (int i = 0; i < N; i++) {
      tk = 0;
      if (R > Y && R > B) {

        if (ans[ans.length() - 1] != 'R') {
          ans += 'R';
          R--;
          tk = 1;
        } else {
          if (Y > B) {
            ans += 'Y';
            Y--;
            tk = 1;
          } else if (Y < B) {
            ans += 'B';
            B--;
            tk = 1;
          }
        }
      } else if (Y > R && Y > B) {

        if (ans[ans.length() - 1] != 'Y') {
          ans += 'Y';
          Y--;
          tk = 1;
        } else {
          if (R > B) {
            ans += 'R';
            R--;
            tk = 1;
          } else if (R < B) {
            ans += 'B';
            B--;
            tk = 1;
          }
        }
      } else if (B > R && B > Y) {
        if (ans[ans.length() - 1] != 'B') {
          ans += 'B';
          B--;
          tk = 1;
        } else {
          if (R > Y) {
            ans += 'R';
            R--;
            tk = 1;
          } else if (R < Y) {
            ans += 'Y';
            Y--;
            tk = 1;
          }
        }
      }

      if (tk == 0) {

        if (tk == 0 && R >= Y && R >= B && ans[0] == 'R') {
          if (ans[ans.length() - 1] != 'R') {
            ans += 'R';
            R--;
            tk = 1;
          }
        }
        if (tk == 0 && Y >= R && Y >= B && ans[0] == 'Y') {
          if (ans[ans.length() - 1] != 'Y') {
            ans += 'Y';
            Y--;
            tk = 1;
          }
        }
        if (tk == 0 && B >= R && B >= Y && ans[0] == 'B') {
          if (ans[ans.length() - 1] != 'B') {
            ans += 'B';
            B--;
            tk = 1;
          }
        }
      }
      if (tk == 0) {

        if (tk == 0 && R >= Y && R >= B) {
          if (ans[ans.length() - 1] != 'R') {
            ans += 'R';
            R--;
            tk = 1;
          } else {
            if (Y > B) {
              ans += 'Y';
              Y--;
              tk = 1;
            } else {
              ans += 'B';
              B--;
              tk = 1;
            }
          }
        }
        if (tk == 0 && Y >= R && Y >= B) {
          if (ans[ans.length() - 1] != 'Y') {
            ans += 'Y';
            Y--;
            tk = 1;
          } else {
            if (R > B) {
              ans += 'R';
              R--;
              tk = 1;
            } else {
              ans += 'B';
              B--;
              tk = 1;
            }
          }
        }
        if (tk == 0 && B >= R && B >= Y) {
          if (ans[ans.length() - 1] != 'B') {
            ans += 'B';
            B--;
            tk = 1;
          } else {
            if (R > Y) {
              ans += 'R';
              R--;
              tk = 1;
            } else {
              ans += 'Y';
              Y--;
              tk = 1;
            }
          }
        }
      }

      if (tk == 0 || min(R, min(Y, B)) < 0)
        fl = 1;
    }
    if (ans[0] == ans[ans.length() - 1])
      fl = 1;

    if (fl == 1)
      cout << "IMPOSSIBLE\n";
    else
      cout << ans << endl;
  }
}
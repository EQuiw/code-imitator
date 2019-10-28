#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define dbg(x) cout << #x << "=" << x << endl
#define N 2001025
#define MOD 786433
#define pb push_back
#define iosbase ios_base::sync_with_stdio(false)
#define dbg(x) cout << #x << "=" << x << endl

int main() {

  int tc, flag;
  ll ans = 0;
  string s;

  cin >> tc;
  for (int ca = 1; ca <= tc; ca++) {
    ans = 0;
    cin >> s;
    while (true) {
      flag = -1;
      for (int i = 0; i < s.length(); i++) {
        if (s[i] < s[i - 1]) {
          flag = i;
          break;
        }
      }
      if (flag == -1)
        break;
      s[flag - 1]--;
      for (int i = flag; i < s.length(); i++) {
        s[i] = '9';
      }
    }

    for (int i = 0; i < s.length(); i++) {
      ans = ans * 10LL + (s[i] - '0');
    }

    printf("Case #%d: %lld\n", ca, ans);
  }
}
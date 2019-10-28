#include <bits/stdc++.h>

//#define int long long

using namespace std;

const int MAXN = 1001 * 1001, MOD = 1e9 + 7;

int32_t main() {
  ios::sync_with_stdio(0);
  int t;
  cin >> t;
  for (int _ = 1; _ <= t; _++) {
    string s;
    int k;
    cin >> s >> k;
    int n = s.size();
    int x = 0;
    for (int i = 0; i + k <= n; i++) {
      if (s[i] == '-') {
        x++;
        //			cout << i << '\n' ;
        for (int j = i; j < i + k; j++)
          s[j] = (s[j] == '-' ? '+' : '-');
      }
    }
    bool f = 0;
    for (int i = 0; i < n; i++)
      if (s[i] != '+')
        f = 1;
    //	cout << s << '\n' ;
    //	printf("Case #%d: %d\n",_,x) ;
    cout << "Case #" << _ << ": ";
    if (f)
      cout << "IMPOSSIBLE\n";
    else
      cout << x << '\n';
  }
}

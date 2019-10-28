#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
void solve() {
  string s;
  int k;
  cin >> s >> k;

  int n = s.size();
  int ans = 0;
  for (int(i) = 0; (i) < (int)(n - k + 1); ++(i)) {
    if (s[i] == '-') {
      for (int(j) = 0; (j) < (int)(k); ++(j))
        s[i + j] = (s[i + j] == '+') ? '-' : '+';
      // cout<<"flip: "<<i<<" "<<s<<endl;
      ++ans;
    }
  }

  bool valid = true;
  for (int(i) = 0; (i) < (int)(n); ++(i))
    valid &= (s[i] == '+');
  if (valid)
    printf("%d\n", ans);
  else
    printf("IMPOSSIBLE\n");
}

int main() {
  int T;
  cin >> T;
  for (int(t) = 0; (t) < (int)(T); ++(t)) {
    printf("Case #%d: ", t + 1);
    solve();
  }
  return 0;
}

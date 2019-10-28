#include <bits/stdc++.h>
#define pb push_back
using namespace std;
typedef long long ll;
typedef long double ld;

int T, n;
string s;

void sub(int k) {
  if (s[k] == '0')
    s[k] = '9', sub(k - 1);
  else
    s[k] = s[k] - 1;
}

void dp(int k) {
  // cout << s <<endl;
  bool corr = true;
  for (int i = 0; i < k; i++) {
    if (s[i] > s[i + 1])
      corr = false;
  }
  if (corr)
    return;
  s[k] = '9';
  sub(k - 1);
  dp(k - 1);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cin >> T;
  for (int it = 0; it < T; it++) {
    cin >> s;
    n = s.size();
    dp(n - 1);
    if (s[0] == '0')
      s.erase(0, 1);
    cout << "Case #" << it + 1 << ": ";
    cout << s << endl;
  }
}

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int maxk = 19;

int ans[maxk];

int main() {

  int tt;
  cin >> tt;
  for (int qq = 1; qq <= tt; qq++) {
    printf("Case #%d: ", qq);
    ll n;
    cin >> n;
    vi d;
    while (n) {
      d.push_back(n % 10);
      n /= 10;
    }
    int m = d.size();
    ans[0] = d[0];
    for (int i = 1; i < m; i++) {
      int cur = d[i];
      if (cur <= ans[i - 1])
        ans[i] = cur;
      else {
        ans[i] = cur - 1;
        for (int j = 0; j < i; j++)
          ans[j] = 9;
      }
    }
    if (ans[m - 1])
      cout << ans[m - 1];
    for (int i = m - 2; i >= 0; i--)
      cout << ans[i];
    cout << endl;
  }

  return 0;
}

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#else
#define eprintf(...)
#endif

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int maxk = 19;

int ans[maxk];

int main() {
#ifdef LOCAL
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int tt;
  cin >> tt;
  for (int qq = 1; qq <= tt; qq++) {
    printf("Case #%d: ", qq);
    ll n;
    cin >> n;
    vi d;
    while (n) {
      d.pb(n % 10);
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
#ifdef LOCAL
  eprintf("Time %.2f\n", (double)clock() / CLOCKS_PER_SEC);
#endif
  return 0;
}
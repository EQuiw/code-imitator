#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define ft first
#define sd second
#define sz(x) ((int) (x).size())
#define all(x) (x).begin(), (x).end()

#ifdef LOCAL
#define eprint(x) cerr << #x << " = " << x << endl
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprint(x)
#define eprintf(...)
#endif

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int N = 100;

int e[N], s[N], d[N][N];
ld dp[N];

int main() {
#ifdef LOCAL
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int tt;
  cin >> tt;
  for (int qq = 1; qq <= tt; qq++) {
    printf("Case #%d: ", qq);
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++)
      cin >> e[i] >> s[i];
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        cin >> d[i][j];
    int u, v;
    cin >> u >> v;
    dp[n - 1] = 0;
    for (int i = n - 2; i >= 0; i--) {
      dp[i] = -1;
      ll sum = 0;
      for (int j = i + 1; j < n; j++) {
        sum += d[j - 1][j];
        if (sum <= e[i] && dp[j] >= -0.5) {
          ld add = sum * 1.0 / s[i];
          if (dp[i] == -1.0 || dp[j] + add < dp[i])
            dp[i] = dp[j] + add;
        }
      }
    }
    printf("%.10f\n", (double) dp[0]);
  }
#ifdef LOCAL
  eprintf("Time %.2f\n", (double) clock() / CLOCKS_PER_SEC);
#endif
  return 0;
}
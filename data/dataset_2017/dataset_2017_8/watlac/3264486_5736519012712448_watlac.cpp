#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define sz(x) ((int) (x).size())
#define all(x) (x).begin(), (x).end()

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#else
#define eprintf(...)
#endif

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

int main() {
#ifdef LOCAL
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int tt;
  cin >> tt;
  for (int qq = 1; qq <= tt; qq++) {
    printf("Case #%d: ", qq);
    string s;
    int k;
    cin >> s >> k;
    int ans = 0;
    for (int i = 0; i < sz(s); i++) {
      if (s[i] == '-') {
        if (i + k > sz(s)) {
          ans = -1;
          break;
        }
        else {
          for (int j = 0; j < k; j++)
            s[i + j] = (s[i + j] == '+' ? '-' : '+');
          ans++;
        }
      }
    }
    if (ans == -1) {
      cout << "IMPOSSIBLE" << endl;
    }
    else {
      cout << ans << endl;
    }
  }
#ifdef LOCAL
  eprintf("Time %.2f\n", (double) clock() / CLOCKS_PER_SEC);
#endif
  return 0;
}
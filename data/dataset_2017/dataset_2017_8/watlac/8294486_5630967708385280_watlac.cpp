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

const int N = 1e3;

int main() {
#ifdef LOCAL
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int tt;
  cin >> tt;
  for (int qq = 1; qq <= tt; qq++) {
    printf("Case #%d: ", qq);
    ld d;
    int n;
    cin >> d >> n;
    vector< pair<ld, ld> > h(n);
    for (int i = 0; i < n; i++)
      cin >> h[i].ft >> h[i].sd;
    sort(all(h));
    for (int i = n - 2; i >= 0; i--) {
      ld p1 = h[i].ft, v1 = h[i].sd;
      ld p2 = h[i + 1].ft, v2 = h[i + 1].sd;
      if (v1 < v2)
        continue;
      ld t = (p2 - p1) / (v1 - v2);
      ld x = t * v1;
      if (p1 + x > d)
        continue;
      double v = (d - p1) / (t + (d - (p1 + x)) / v2);
      h[i].sd = v;
    }
    ld ans = h[0].sd * d / (d - h[0].ft);
    printf("%.10lf\n", (double) ans);
  }
#ifdef LOCAL
  eprintf("Time %.2f\n", (double) clock() / CLOCKS_PER_SEC);
#endif
  return 0;
}
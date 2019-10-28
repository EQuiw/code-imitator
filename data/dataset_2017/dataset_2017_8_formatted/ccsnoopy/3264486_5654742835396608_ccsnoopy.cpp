#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long long LL;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

#ifdef DEBUG
#define cek(x) cout << x
#else
#define cek(x)                                                                 \
  if (false) {                                                                 \
  }
#endif // DEBUG

#define fi first
#define se second
#define INF 1000000000
#define INFLL 1000000000000000000LL
#define EPS 1e-9
#define PI acos(-1.0)
#define pb push_back
#define TC() while (tc--)
#define FOR(i, n) for (int i = 0; i < n; i++)
#define FORN(i, n) for (int i = 0; i <= n; i++)
#define REP(i, a, b) for (int i = a; i < b; i++)
#define REPN(i, a, b) for (int i = a; i <= b; i++)
#define reset(a, b) memset(a, b, sizeof(a))
#define ALL(v) v.begin(), v.end()
#define SORT(v) sort(ALL(v))
#define SORTA(v, n) sort(v, v + n)
#define SZ(v) (int)v.size()
#define sc(x) scanf("%d", &x)

void open() {
  freopen("D:/OneDrive/Code/GCJ/C-small-1-attempt0.in", "r", stdin);
  freopen("D:/OneDrive/Code/GCJ/out.txt", "w", stdout);
}

int main(void) {
  open();
  int tc;
  sc(tc);
  for (int ct = 1; ct <= tc; ct++) {
    int n, k;
    sc(n);
    sc(k);
    priority_queue<int> pq;
    pq.push(n);

    printf("Case #%d: ", ct);

    while (k--) {
      int top = pq.top();
      pq.pop();
      int mid = top - 1;
      int l, r;
      l = mid / 2;
      r = (mid + 1) / 2;
      if (k == 0) {
        printf("%d %d\n", r, l);
      }
      if (l) {
        pq.push(l);
      }

      if (r) {
        pq.push(r);
      }
    }

    cerr << "Test " << ct << " done \n";
  }
  return 0;
}

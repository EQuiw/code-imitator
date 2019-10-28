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
  freopen("D:/OneDrive/Code/GCJ/B-small-attempt1.in", "r", stdin);
  freopen("D:/OneDrive/Code/GCJ/out1.txt", "w", stdout);
}

void pr(int idx) {
  switch (idx) {
  case 0:
    printf("R");
    break;
  case 1:
    printf("O");
    break;
  case 2:
    printf("Y");
    break;
  case 3:
    printf("G");
    break;
  case 4:
    printf("B");
    break;
  case 5:
    printf("V");
    break;
  }
}

int main(void) {
  open();
  int tc;
  sc(tc);

  for (int ct = 1; ct <= tc; ct++) {
    int n;
    sc(n);
    int arr[10];
    printf("Case #%d: ", ct);
    FOR(i, 6) { sc(arr[i]); }
    bool imp = false;
    FOR(i, 6) {
      if (arr[i] * 2 > n) {
        imp = true;
        printf("IMPOSSIBLE\n");
        break;
      }
    }

    if (imp)
      continue;

    int maxidx = 0;
    FOR(i, 6) {
      if (arr[maxidx] < arr[i])
        maxidx = i;
    }
    bool palinggede = true;
    int last = maxidx;
    pr(maxidx);
    arr[maxidx]--;
    int first = last;

    while (true) {
      bool ada = false;
      FOR(i, 6) {
        if (arr[i] > 0)
          ada = true;
      }

      if (!ada)
        break;

      if (last == 0) {
        if (arr[2] > arr[4]) {
          last = 2;
        } else if (arr[2] < arr[4]) {
          last = 4;
        } else {
          if (first == 2) {
            last = 2;
          } else
            last = 4;
        }
      } else if (last == 2) {
        if (arr[0] > arr[4]) {
          last = 0;
        } else if (arr[0] < arr[4]) {
          last = 4;
        } else {
          if (first == 0) {
            last = 0;
          } else
            last = 4;
        }
      } else {
        if (arr[0] > arr[2]) {
          last = 0;
        } else if (arr[0] < arr[2]) {
          last = 2;
        } else {
          if (first == 0) {
            last = 0;
          } else
            last = 2;
        }
      }
      pr(last);
      arr[last]--;
    }
    printf("\n");

    cerr << "Test " << ct << " done \n";
    if (first == last) {
      cerr << "last equals first\n";
    }
  }
  return 0;
}

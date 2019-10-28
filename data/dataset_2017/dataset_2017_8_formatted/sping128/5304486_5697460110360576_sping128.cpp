#include <bits/stdc++.h>

using namespace std;

#define SZ(x) ((int)(x).size())
#define PB(x) push_back(x)
#define MEMSET(x, v) memset(x, v, sizeof(x))
#define REP(i, n) for (int(i) = 0; (i) < (n); ++(i))
#define x first
#define y second
#define INF (0x3f3f3f3f)

typedef long long LL;
typedef pair<int, int> P2;
template <class A, class B> inline bool mina(A &x, B y) {
  return (x > y) ? (x = y, 1) : 0;
}
template <class A, class B> inline bool maxa(A &x, B y) {
  return (x < y) ? (x = y, 1) : 0;
}

const int MAXN = 55;
const int MAXP = 55;
int N, P;
int in[MAXN];
int gram[MAXN][MAXP];
int cur[MAXN];

void solve() {

  cin >> N >> P;
  REP(i, N)
  cin >> in[i];
  REP(i, N) {
    REP(j, P) { cin >> gram[i][j]; }
  }
  REP(i, N) { sort(gram[i], gram[i] + P); }
  MEMSET(cur, 0);
  int ans = 0;

  int maxx = in[0];
  REP(i, N) { maxx = max(maxx, in[i]); }
  for (int servings = 1; servings <= 2000000 / maxx; servings++) {
    REP(i, N) {
      while (cur[i] < P && gram[i][cur[i]] * 100 < 90 * in[i] * servings)
        cur[i]++;
    }
    bool good = true;
    REP(i, N) {
      if (cur[i] >= P) {
        good = false;
        break;
      }
    }
    if (!good)
      break;
    bool succ = true;
    REP(i, N) {
      if (gram[i][cur[i]] * 100 > 110 * in[i] * servings) {
        succ = false;
        break;
      }
    }
    if (succ) {
      ans++;
      REP(i, N) cur[i]++;
      servings--;
    }
  }
  cout << ans << endl;
}

int main() {
  int test;
  cin >> test;
  REP(tt, test) {
    cout << "Case #" << (tt + 1) << ": ";
    solve();
  }

  return 0;
}

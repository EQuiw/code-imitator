#include <bits/stdc++.h>
#define ff first
#define ss second
#define ALL(x) (x).begin(), (x).end()
#define D(x) cout << ">> " << #x << " = >" << x << "<" << endl
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define FORD(i, a, b) for (int i = (a); i >= (b); --i)
#define PB push_back
#define R1(a) scanf("%d", &a)
#define R2(a, b) scanf("%d%d", &a, &b)
#define R3(a, b, c) scanf("%d%d%d", &a, &b, &c)
#define P(cond)                                                                \
  do {                                                                         \
    if (!(cond)) {                                                             \
      puts("Nespravny vstup.");                                                \
      return 1;                                                                \
    }                                                                          \
  } while (0)
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> Matrix;

const int INF = 1e9 + 7;
const double PI = acos(-1);
const double EPS = 1e-9;

const int N = 1e3 + 5;
int occup[N], R[N], L[N];
ll t, n, k;

void precompute() {
  L[0] = 0;
  R[n + 1] = 0;
  FOR(i, 1, n + 2)
  L[i] = occup[i] ? 0 : L[i - 1] + 1;
  FORD(i, n, 0)
  R[i] = occup[i] ? 0 : R[i + 1] + 1;
}

int main() {
  cin >> t;

  FOR(caseNr, 1, t + 1) {
    cout << "Case #" << caseNr << ": ";
    cin >> n >> k;
    memset(occup, 0, sizeof(occup));
    occup[0] = 1;
    occup[n + 1] = 1;
    int best;
    while (k--) {
      precompute();
      best = 1;
      FOR(i, 1, n + 1) {
        if (occup[i])
          continue;
        if (min(L[i], R[i]) > min(L[best], R[best]))
          best = i;
        else if (min(L[i], R[i]) == min(L[best], R[best]) &&
                 max(L[i], R[i]) > max(L[best], R[best]))
          best = i;
      }
      occup[best] = 1;
    }
    cout << max(L[best], R[best]) - 1 << " " << min(L[best], R[best]) - 1
         << endl;
  }
  return 0;
}

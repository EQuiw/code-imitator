#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> VI;
typedef pair<int, int> PII;

#define debug(args...)                                                         \
  {                                                                            \
    vector<string> _v = split(#args, ',');                                     \
    err(_v.begin(), args);                                                     \
    puts("");                                                                  \
  }
vector<string> split(const string &s, char c) {
  vector<string> v;
  stringstream ss(s);
  string x;
  while (getline(ss, x, c))
    v.push_back(x);
  return v;
}
void err(vector<string>::iterator it) {}
template <typename T, typename... Args>
void err(vector<string>::iterator it, T a, Args... args) {
  cerr << it->substr((*it)[0] == ' ', it->length()) << " = " << a << ", ";
  err(++it, args...);
}

#if ((_WIN32 || __WIN32__) && __cplusplus < 201103L)
#define lld I64d
#else
#define lld lld
#endif

#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define tr(c, it) for (auto it = c.begin(); it != c.end(); it++)
#define clr(a, b) memset(a, b, sizeof(a))
#define forn(i, n) for (int i = 0; i < n; i++)

const int INF = 0x3f3f3f3f;

const double eps = 1e-8;

int T;
const int N = 1111;

LL d;
LL pos[N];
int v[N];
int n;

bool check(double cur_v) {
  // for(int i=1; i<=m; i++)
  return true;
}

int main() {
#ifdef LOCAL
  // freopen("in", "r", stdin);
  freopen("A-small-attempt0.in", "r", stdin);
  // freopen("A-small-attempt1.in", "r", stdin);
  // freopen("A-small-attempt2.in", "r", stdin);
  // freopen("A-large.in", "r", stdin);
  freopen("out", "w", stdout);
#endif

  int cas = 1;
  scanf("%d", &T);

  while (T--) {
    printf("Case #%d: ", cas++);

    cin >> d >> n;
    double tt = 0;

    for (int i = 1; i <= n; i++) {
      cin >> pos[i] >> v[i];

      double tmp_t = 1.0 * (d - pos[i]) / v[i];
      tt = max(tmp_t, tt);
    }
    double ans = 1.0 * d / tt;

    // double lo = 1, hi = 1e9;
    // while(hi - lo > eps)
    //{
    // double mid = (lo + hi) / 2.0;
    // bool ok = check(mid);
    // if(ok) lo = mid;
    // else hi = mid;
    //}

    // double ans = lo;
    printf("%.6f\n", ans);
  }

  return 0;
}

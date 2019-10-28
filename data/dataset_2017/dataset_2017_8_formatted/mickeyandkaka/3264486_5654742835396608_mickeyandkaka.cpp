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
typedef pair<LL, LL> PII;

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

int T;

LL n, k;

PII dfs(LL n, LL k) {
  if (n == 1)
    return {0, 0};

  if (n & 1) {
    if (k == 1)
      return {n / 2, n / 2};
    return dfs(n / 2, (k - 2) / 2 + 1);
  } else {
    if (k == 1)
      return {n / 2 - 1, n / 2};
    k--;
    if (k & 1)
      return dfs(n / 2, (k + 1) / 2);
    else
      return dfs(n / 2 - 1, k / 2);
  }
}

int main() {
#ifdef LOCAL
  // freopen("in", "r", stdin);
  freopen("C-small-1-attempt0.in", "r", stdin);
  // freopen("C-large.in", "r", stdin);
  freopen("out", "w", stdout);
#endif

  int cas = 1;
  scanf("%d", &T);

  while (T--) {
    cin >> n >> k;
    PII ans = dfs(n, k);

    printf("Case #%d: %lld %lld\n", cas++, ans.second, ans.first);
  }

  return 0;
}

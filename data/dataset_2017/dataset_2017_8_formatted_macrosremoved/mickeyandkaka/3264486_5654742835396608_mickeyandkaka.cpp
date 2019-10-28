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

  int cas = 1;
  scanf("%d", &T);

  while (T--) {
    cin >> n >> k;
    PII ans = dfs(n, k);

    printf("Case #%d: %lld %lld\n", cas++, ans.second, ans.first);
  }

  return 0;
}

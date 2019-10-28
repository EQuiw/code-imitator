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

int n, p;
int r[55];
int q[55][55];
int per[55];

bool check(int req, int val) {
  int hi = val / (req * 0.9);
  int lo = val / (req * 1.1);

  for (int k = lo; k <= hi; k++) {
    if (0.9 * k * req <= val && 1.1 * k * req >= val)
      return true;
  }
  return false;
}

bool check2(int r1, int r2, int v1, int v2) {

  int lo = v1 / (r1 * 1.1);
  int hi = v1 / (r1 * 0.9);

  lo = max(lo, int(v2 / (r2 * 1.1)));
  hi = min(hi, int(v2 / (r2 * 0.9)));

  for (int k = lo; k <= hi; k++) {
    if (0.9 * k * r1 <= v1 && 1.1 * k * r1 >= v1 && 0.9 * k * r2 <= v2 &&
        1.1 * k * r2 >= v2)
      return true;
  }
  return false;
}

int main() {
  int cas = 1;
  scanf("%d", &T);

  while (T--) {
    int ans = 0;
    printf("Case #%d: ", cas++);

    scanf("%d%d", &n, &p);
    for (int i = 0; i < n; i++)
      scanf("%d", &r[i]);

    for (int i = 0; i < n; i++)
      for (int j = 0; j < p; j++)
        scanf("%d", &q[i][j]);

    if (n == 1) {
      for (int i = 0; i < p; i++) {
        bool fg = check(r[0], q[0][i]);
        if (fg)
          ans++;
      }
      printf("%d\n", ans);
      continue;
    } else {
      for (int i = 0; i < p; i++)
        per[i] = i;

      do {
        int tmpans = 0;
        for (int i = 0; i < p; i++) {
          int a = q[0][i];
          int b = q[1][per[i]];
          bool fg = check2(r[0], r[1], a, b);
          if (fg)
            tmpans++;
        }
        ans = max(ans, tmpans);

      } while (next_permutation(per, per + p));
      printf("%d\n", ans);
    }
  }

  return 0;
}

#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
#define rep(i, n) for (int i = 0; i < ((int)(n)); i++)
#define reg(i, a, b) for (int i = ((int)(a)); i <= ((int)(b)); i++)
#define irep(i, n) for (int i = ((int)(n)) - 1; i >= 0; i--)
#define ireg(i, a, b) for (int i = ((int)(b)); i >= ((int)(a)); i--)
typedef long long int lli;
typedef pair<int, int> mp;
#define fir first
#define sec second
#define IINF INT_MAX
#define LINF LLONG_MAX
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define pque(type) priority_queue<type, vector<type>, greater<type>>
#define memst(a, b) memset(a, b, sizeof(a))
#define iter(v, ite) for (auto ite = (v).begin(); ite != (v).end(); ite++)
#define mimunum(v, x)                                                          \
  distance((v).begin(), lower_bound((v).begin(), (v).end(), x))

int n, k;

int main(void) {
  int qn;
  scanf("%d", &qn);
  reg(qqq, 1, qn) {
    scanf("%d%d", &n, &k);
    priority_queue<int> que;
    que.push(n);
    rep(i, k - 1) {
      int x = que.top();
      que.pop();
      x--;
      if (x <= 0)
        continue;
      que.push(x - x / 2);
      if (x / 2 > 0)
        que.push(x / 2);
    }
    int t = que.top();
    t--;

    printf("Case #%d: %d %d\n", qqq, t - t / 2, t / 2);
  }
  return 0;
}

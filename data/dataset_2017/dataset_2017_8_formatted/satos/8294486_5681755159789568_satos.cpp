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

int n;
lli vs[105][105];
double wes[105][105];

lli he[105];
double hs[105];

template <class T> void verfo(T vect[105][105]) {
  rep(k, n) rep(i, n) rep(j, n) {
    T a = vect[i][k], b = vect[k][j];
    T &c = vect[i][j];
    if (a < 0 || b < 0)
      continue;
    if (c < 0 || (a + b < c))
      c = a + b;
  }
}

void init() {
  verfo<lli>(vs);
  /*
  rep(i,n){
          rep(j,n)printf("%d ",vs[i][j]);
          puts("");
  }*/
  rep(i, n) {
    rep(j, n) {
      wes[i][j] = -1;
      if (i == j || vs[i][j] < 0)
        continue;
      if (vs[i][j] > he[i])
        continue;
      wes[i][j] = vs[i][j] / hs[i];
    }
    wes[i][i] = 0;
  }

  verfo<double>(wes);
}

int main(void) {
  int qn;
  scanf("%d", &qn);
  reg(qqq, 1, qn) {
    int m;
    scanf("%d%d", &n, &m);
    rep(i, n) { scanf("%lld%lf", &he[i], &hs[i]); }
    rep(i, n) rep(j, n) { scanf("%lld", &vs[i][j]); }
    rep(i, n) vs[i][i] = 0;
    init();

    printf("Case #%d: ", qqq);
    rep(i, m) {
      int a, b;
      scanf("%d%d", &a, &b);
      a--;
      b--;
      printf("%lf ", wes[a][b]);
    }
    puts("");
  }
  return 0;
}

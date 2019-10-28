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

typedef long long int lli;
typedef pair<int, int> mp;
int n;
lli vs[105][105];
double wes[105][105];

lli he[105];
double hs[105];

template <class T> void verfo(T vect[105][105]) {
  for (int k = 0; k < ((int)(n)); k++)
    for (int i = 0; i < ((int)(n)); i++)
      for (int j = 0; j < ((int)(n)); j++) {
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
  for (int i = 0; i < ((int)(n)); i++) {
    for (int j = 0; j < ((int)(n)); j++) {
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
  for (int qqq = ((int)(1)); qqq <= ((int)(qn)); qqq++) {
    int m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < ((int)(n)); i++) {
      scanf("%lld%lf", &he[i], &hs[i]);
    }
    for (int i = 0; i < ((int)(n)); i++)
      for (int j = 0; j < ((int)(n)); j++) {
        scanf("%lld", &vs[i][j]);
      }
    for (int i = 0; i < ((int)(n)); i++)
      vs[i][i] = 0;
    init();

    printf("Case #%d: ", qqq);
    for (int i = 0; i < ((int)(m)); i++) {
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

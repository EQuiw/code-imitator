#include <algorithm>
#include <cstdio>

using namespace std;

int N;

struct Node {
  int l;
  int h;
} have[60][60];

bool cmp(Node A, Node B) {
  if (A.h == B.h)
    return A.l < B.l;
  return A.h < B.h;
}

int main() {
  int T, ans, P, l, h, tmp, max;
  int need[60];
  bool edge[60][60][60];
  scanf("%d", &T);
  for (int rr = 1; rr <= T; ++rr) {
    scanf("%d %d", &N, &P);
    max = -1;
    ans = 0;
    for (int i = 0; i < N; ++i) {
      scanf("%d", &need[i]);
    }
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < P; ++j) {
        scanf("%d", &tmp);
        tmp *= 10;
        h = tmp / (9 * need[i]);
        l = tmp / (11 * need[i]);
        if (tmp % (11 * need[i]) > 0)
          ++l;
        if (l == 0)
          ++l;
        if (h < l)
          h = l = -1;
        have[i][j].l = l;
        have[i][j].h = h;
      }
      sort(have[i], have[i] + P, cmp);
    }

    ///		for(int i=0;i<N;++i){
    //			for(int j=0;j<P;++j){
    //				printf("[%d,%d] ",have[i][j].l,have[i][j].h);
    //			}
    //			puts("");
    //		}

    if (N == 2) {
      int i = 0, j = 0;
      while (i < P && have[0][i].l == -1)
        ++i;
      while (j < P && have[1][j].l == -1)
        ++j;
      while (i < P && j < P) {
        //				printf("i=%d j=%d\n",i,j);
        if (have[0][i].h >= have[1][j].l && have[0][i].l <= have[1][j].l) {
          ++i;
          ++j;
          ++ans;
        } else if (have[1][j].h >= have[0][i].l &&
                   have[1][j].l <= have[0][i].l) {
          ++i;
          ++j;
          ++ans;
        } else if (have[0][i].l >= have[1][j].l &&
                   have[0][i].h <= have[1][j].h) {
          ++i;
          ++j;
          ++ans;
        } else if (have[0][i].l <= have[1][j].l &&
                   have[0][i].h >= have[1][j].h) {
          ++i;
          ++j;
          ++ans;
        } else if (have[0][i].l > have[1][j].h) {
          ++j;
        } else if (have[1][j].l > have[0][i].h) {
          ++i;
        } else {
          printf("else\n");
        }
      }
    } else if (N == 1) {
      int i = 0;
      while (i < P && have[0][i].l == -1)
        ++i;
      ans = P - i;
    } else {
    }

    /*		for(int i=1;i<N;++i){
                            j=k=0;
                            while(have[i-1][j].l == -1) ++j;
                            while(have[i][k].l == -1) ++k;
                            while(j<P && k<P){
                                    if(have[i-1][j].l <= have[i][k].l &&
       have[i-1][j].h >= have[i][k].h){ edge[i-1][j][k] = true;
                                            ++j;
                                            ++k;
                                    }
                                    else if(have[i-1].h
                            }
                            for(int j=0;j<P;++j){
                                    for(int k=1;k<P;++k){
                                            if(have[i-1][j]
                                    }
                            }
                    }*/

    printf("Case #%d: %d\n", rr, ans);
  }
  return 0;
}

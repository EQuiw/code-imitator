#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

int N,P;
int s[200];
int r[200][200];
int b[200];
int tb[200];

int ll[200][200];
int mm[200][200];

bool dfs(int cur, int less, int most){
  return 0;
}

int main(void){
    int t;
    scanf("%d",&t);
    for(int tt=1;tt<=t;tt++){
        scanf("%d%d",&N,&P);
        for(int i=0;i<N;++i)
          scanf("%d",&s[i]);
        for(int i=0;i<N;++i) {
          for(int j=0;j<P;++j) {
            scanf("%d",&r[i][j]);
          }
          sort(r[i], r[i]+P);
          for(int j=0;j<P;++j) {
            ll[i][j] = ceil(1.0*r[i][j]/(1.1*s[i]));
            mm[i][j] = floor(1.0*r[i][j]/(0.9*s[i]));
          }
        }

        /*
        for(int i=0;i<N;++i) {
          for(int j=0;j<P;++j) {
            printf("[%4d,%4d] ", ll[i][j], mm[i][j]);
          }
          puts("");
        }
        continue;
        */

        int ans=0;
        memset(b,0,sizeof(b));

        /*
        for(int i=0;i<P;++i)
        {
          int low = s[0]-(s[0]/10);
          int high = s[0]+((s[0]+9)/10);

          int most = r[0][i]/low;
          int less = (r[0][i]+high-1)/high;

          for(int k=less;k<=most;++k){
            bool ok=true;
            for(int j=0;j<N && ok;++j){
              if (r[j][i]*10 < k*s[j]*9) ok=false;
              if (r[j][i]*10 > k*s[j]*11) ok=false;
            }
            if (ok) {
              ++ans;
              break;
            }
          }

        }
        */

        while(1){
          bool stop=false;
          for(int i=0;i<N;++i) {
            if (b[i]>=P) stop=true;
          }
          if (stop) break;

          int cur=0;
          for(int i=0;i<N;++i) {
            cur = max(cur, ll[i][b[i]]);
          }

          bool ok=true;
          for(int i=0;i<N;++i) {
            for (int j=b[i];j<=P;++j) {
              if (j==P || cur < ll[i][j]) { 
                b[i]=j;
                ok=false;
                break;
              }
              if (ll[i][j] > mm[i][j]) {
                continue;
              }
              if (cur <= mm[i][j]) {
                tb[i]=j;
                break;
              }
            }
          }

          // printf("%d: %d %d\n", cur, ok, b[0]);
          if (!ok) continue;

          ++ans;
          for(int i=0;i<N;++i) {
            b[i]=tb[i]+1;
          }
        }

        printf("Case #%d: %d\n", tt, ans);
    }
    return 0;
}


#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int N,Q,U,V;
int e[200];
double s[200];
int d[200][200];
int go[200];

double ans[200];
int main(void){
    int t;
    scanf("%d",&t);
    for(int tt=1;tt<=t;tt++){
        scanf("%d%d",&N,&Q);
        for(int i=0;i<N;++i)
          scanf("%d%lf",&e[i],&s[i]);
        for(int i=0;i<N;++i)
          for(int j=0;j<N;++j)
            scanf("%d",&d[i][j]);

        for(int k=0;k<N;++k)
          for(int i=0;i<N;++i)
            for(int j=0;j<N;++j)
            {
              if(i==j || d[i][k]<0 || d[k][j]<0) continue;
              if(d[i][j]<0 || d[i][j] >= d[i][k]+d[k][j]){
                d[i][j]=d[i][k]+d[k][j];
              }
            }

        printf("Case #%d:", tt);

        for(;Q--;){
          scanf("%d%d",&U,&V);
          --U,--V;
          for(int i=0;i<N;++i) {
            ans[i]=-1;
            go[i]=false;
          }
          ans[U]=0;
          // go[U]=true;

          int cur=U;
          while(1){
            go[cur]=true;
            for(int i=0;i<N;++i){
              if(d[cur][i]>e[cur] || d[cur][i]<0)
                continue;
              if(ans[i]<0 || ans[i]>ans[cur]+d[cur][i]/s[cur])
                ans[i]=ans[cur]+d[cur][i]/s[cur];
            }

            double mind=-1;
            for(int i=0;i<N;++i){
              if(go[i] || ans[i]<0) continue;
              if(mind<0 || mind>ans[i]){
                cur=i;
                mind=ans[i];
              }
            }

            if(mind<0) break;
          }

          printf(" %lf", ans[V]);
        }

        puts("");
    }
    return 0;
}


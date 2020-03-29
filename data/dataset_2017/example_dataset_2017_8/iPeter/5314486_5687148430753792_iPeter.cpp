#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

int N,C,M;
int cnt[1100];
class tic{
public:
  int P,B;
  bool operator<(tic d)const{
    if(P==d.P)return B<d.B;
    return P<d.P;
  }
}s[2000];

vector<int> v[2000];
int p[1100][1100];

int main(void){
    int t;
    scanf("%d",&t);
    for(int tt=1;tt<=t;tt++){
      scanf("%d%d%d",&N,&C,&M);
      for(int i=1;i<=N;++i)v[i].clear();

      for(int i=0;i<M;++i){
        scanf("%d%d",&s[i].P,&s[i].B);

        v[s[i].P].push_back(s[i].B);
      }
      for(int i=1;i<=N;++i)sort(v[i].begin(),v[i].end());

      int ans=0,pro=0,rid=0;
      memset(p,0,sizeof(p));
      for(int i=1;i<=N;++i){
        // printf("%d: ",i);
        for(int j=0;j<v[i].size();++j){
          // printf("%2d",v[i][j]);

          bool ok=false;
          for(int r=0;r<rid;++r){
            int b = v[i][j];

            if(p[r][i]>0) continue;
            int x;
            for(x=1;x<i && p[r][x]!=b;++x);
            if(x<i) continue;
            p[r][i] = b;
            ok = true;
            break;
          }

          if(!ok){
            for(int r=0;r<rid;++r){
              int x;
              for(x=1;x<i && p[r][x]!=0;++x);
              if(x==i) continue;

              p[r][x] = v[i][j];
              ++pro;
              ok = true;
              break;
            }
          }

          if(!ok){
            p[rid++][i] = v[i][j];
          }
        }
        // puts("");
      }

      printf("Case #%d: %d %d\n", tt, rid, pro);
    }
    return 0;
}


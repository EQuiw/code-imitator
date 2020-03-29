#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int N,P,g[300];
int main(void){
    int t;
    scanf("%d",&t);
    for(int tt=1;tt<=t;tt++){
      scanf("%d%d",&N,&P);
      for(int i=0;i<N;++i)
        scanf("%d",&g[i]);
      
      int ans=0;
      if(P==2){
        int k=0;
        for(int i=0;i<N;++i)
          if(g[i]%2==0)
            ++k;
        ans = k+(N-k+1)/2;
      }else if(P==3){
        int k1=0,k2=0;
        for(int i=0;i<N;++i) {
          if(g[i]%3==1) ++k1;
          else if(g[i]%3==2) ++k2;
        }
        if(k1>k2){ int z=k1;k1=k2;k2=z; }

        ans = (N-k1-k2)+k1+((k2-k1)+2)/3;

      }else {
      }
        
      printf("Case #%d: %d\n", tt, ans);
    }
    return 0;
}


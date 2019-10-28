#include <cstdio>
#include <algorithm>

using namespace std;

int d,n;
int k[1010],s[1010];
int main (){
    int T;
    scanf("%d",&T);
    for(int I = 1 ; I <= T ; I ++){
        scanf("%d%d",&d,&n);
        for(int i = 0 ; i < n ; i ++){
            scanf("%d%d",k+i,s+i);
        }
        double maxt=0;
        for(int i = 0 ; i < n ; i ++){
            double t = ((double)(d-k[i])) / s[i];
            maxt=max(maxt,t);
        }
        printf("Case #%d: %.15f\n",I,d/maxt);
    }

}

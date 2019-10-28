#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n;
double m,s[2000],d[2000];
int main(void){
    int t;
    scanf("%d",&t);
    for(int tt=1;tt<=t;tt++){
        scanf("%lf%d",&m,&n);
        double lo = 0;
        for(int i=0;i<n;++i){
          scanf("%lf%lf",&d[i],&s[i]);
          lo = max(lo, (m-d[i])/s[i]);
        }

        // printf("%lf\n", lo);
        printf("Case #%d: %.8lf\n", tt, m/lo);
    }
    return 0;
}


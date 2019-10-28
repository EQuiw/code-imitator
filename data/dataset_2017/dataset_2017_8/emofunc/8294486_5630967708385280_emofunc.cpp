#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;
int T_T;
int d,n;
int k[1111],s[1111];
int main(void)
{
    #ifdef LOCAL
    freopen("A-small-attempt0.in","r",stdin);
    freopen("out-small.txt","w",stdout);
    #endif
    scanf("%d",&T_T);
    for (int cas=1;cas<=T_T;cas++)
    {
        scanf("%d%d",&d,&n);
        for (int i=1;i<=n;i++) scanf("%d%d",&k[i],&s[i]);
        double mxt = 0.0;
        for (int i=1;i<=n;i++) {
            mxt = max(mxt,(double)(d-k[i])/(double)s[i]);
        }
        printf("Case #%d: %.6lf\n",cas,(double)d/mxt);
    }
    return 0;
}

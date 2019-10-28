#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define LL long long
using namespace std;
int T_T;
LL n;
bool check(LL x)
{
    int last = 10;
    while (x)
    {
        if (x%10 > last) return 0;
        last = x % 10;
        x /= 10;
    }
    return 1;
}
int main(void)
{
//    freopen("B-small-attempt0.in","r",stdin);
//    freopen("out-small.txt","w",stdout);
    scanf("%d",&T_T);
    for (int cas=1;cas<=T_T;cas++)
    {
        scanf("%lld",&n);
        LL ans;
        for (LL i=n;i>=0;i--) if (check(i)) {ans=i; break; }
        printf("Case #%d: %lld\n",cas,ans);
    }
    return 0;
}

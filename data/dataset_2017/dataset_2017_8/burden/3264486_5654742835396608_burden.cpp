#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define LL long long

using namespace std;

LL n,k,u,v,t,ans,L,R;
pair<LL,LL> a[100][10];

int main()
{
    //freopen("c.in","r",stdin);
    //freopen("c.out","w",stdout);
    int T,w=0;
    for (scanf("%d",&T); T--; )
    {
        scanf("%lld%lld",&n,&k);
        printf("Case #%d: ",++w);

        if (k==1)
        {
            ans=n;
            if (ans%2LL==0) L=ans/2LL,R=L-1; else L=ans/2LL,R=L;
            printf("%lld %lld\n",L,R);
            continue;
        }
        for (int i=1; i<=90; i++)
        for (int j=1; j<=5; j++) a[i][j].first=0,a[i][j].second=0;
        a[1][1].first=n,a[1][1].second=1;
        for (u=2,v=4; ; u++,v=v*2LL)
        {
            if (a[u-1][1].first>0)
            {
                if (a[u-1][1].first%2LL==0)
                {
                    a[u][1].first=a[u-1][1].first/2LL,a[u][1].second+=a[u-1][1].second;
                    a[u][2].first=a[u-1][1].first/2LL-1LL,a[u][2].second+=a[u-1][1].second;
                } else
                {
                    a[u][1].first=a[u-1][1].first/2LL,a[u][1].second+=a[u-1][1].second*2;
                }
            }

            if (a[u-1][2].first>0)
            {
                if (a[u-1][2].first%2LL==0)
                {
                    a[u][1].first=a[u-1][2].first/2LL,a[u][1].second+=a[u-1][2].second;
                    a[u][2].first=a[u-1][2].first/2LL-1LL,a[u][2].second+=a[u-1][2].second;
                } else
                {
                    a[u][2].first=a[u-1][2].first/2LL,a[u][2].second+=a[u-1][2].second*2;
                }
            }
            //printf("%lld %lld %lld %lld\n",a[u][1].first,a[u][1].second,a[u][2].first,a[u][2].second);
            if (v-1LL>=k) break;
        }

        v=v/2LL-1LL,t=k-v;
        if (a[u][1].second>=t) ans=a[u][1].first; else ans=a[u][2].first;

        if (ans%2LL==0) L=ans/2LL,R=L-1; else L=ans/2LL,R=L;
        printf("%lld %lld\n",L,R);
    }
    return 0;
}

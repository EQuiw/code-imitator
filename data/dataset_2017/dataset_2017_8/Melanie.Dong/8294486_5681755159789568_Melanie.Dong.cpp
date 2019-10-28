#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=1e4+5;
const double eps=1e-3;
const LL INF=1e18;

int e[110], s[110], ans[110];
double d[110][110], dp[110][110];
int main()
{
    freopen("C-small-attempt0.in","r",stdin);
    freopen("C-small-attempt0.out","w",stdout);
    int t,ca=1;
    scanf("%d", &t);
    while(t--)
    {
        printf("Case #%d: ", ca++);
        int n, q;
        scanf("%d%d", &n, &q);
        for(int i=1; i<=n; i++)
            scanf("%d%d", &e[i], &s[i]);
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
            {
                cin>>d[i][j];
                if(d[i][j]==-1)
                    d[i][j]=INF;
            }
        for(int k=1; k<=n; ++k)
            for(int i=1; i<=n; ++i)
                for(int j=1; j<=n; ++j)
                    if(d[i][k]+d[k][j]<d[i][j])
                        d[i][j]=d[i][k]+d[k][j];
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
                if(d[i][j]<=e[i]) dp[i][j]=1.0*d[i][j]/s[i];
                else dp[i][j]=INF;
        for(int k=1; k<=n; ++k)
            for(int i=1; i<=n; ++i)
                for(int j=1; j<=n; ++j)
                    if(dp[i][k]+dp[k][j]<dp[i][j])
                        dp[i][j]=dp[i][k]+dp[k][j];
        while(q--)
        {
            int l,r;
            scanf("%d%d", &l, &r);
            printf("%.9f", dp[l][r]);
        }
        puts("");
    }
    return 0;
}

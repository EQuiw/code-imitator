#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#define MAXN 50
#define MAXP 50
#define INF 1000000000
using namespace std;

pair<int,int> adj[MAXN+1][MAXP+1];
int cnt[MAXN+1],cur[MAXN+1];
int r[MAXN+1],q[MAXP+1];
int n,p;

int main()
{
    freopen("B-small-attempt0.in","r",stdin);
    freopen("B-small-attempt0.out","w",stdout);
    int c,t,i,j,flg,ans,maxl,maxi,minr,mini;
    scanf("%d",&t);
    for(c=0;c<t;c++)
    {
        memset(cnt,0,sizeof(cnt));
        scanf("%d %d",&n,&p);
        for(i=0;i<n;i++)
        {
            scanf("%d",&r[i]);
        }
        for(i=0;i<n;i++)
        {
            for(j=0;j<p;j++)
            {
                scanf("%d",&q[j]);
            }
            sort(q,q+p);
            for(j=0;j<p;j++)
            {
                if(((q[j]*9+9)/10+r[i]-1)/r[i]<=((q[j]*10)/9)/r[i])
                {
                    adj[i][cnt[i]++]=make_pair(((q[j]*9+9)/10+r[i]-1)/r[i],((q[j]*10)/9)/r[i]);
                }
            }
        }
        memset(cur,0,sizeof(cur));
        flg=1;
        ans=0;
        while(flg==1)
        {
            for(i=0;i<n;i++)
            {
                if(cur[i]>=cnt[i])
                {
                    flg=0;
                    break;
                }
            }
            if(flg==0)
            {
                break;
            }
            maxl=-1;
            maxi=-1;
            minr=INF;
            mini=-1;
            for(i=0;i<n;i++)
            {
                if(maxl<adj[i][cur[i]].first)
                {
                    maxl=adj[i][cur[i]].first;
                    maxi=i;
                }
                if(minr>adj[i][cur[i]].second)
                {
                    minr=adj[i][cur[i]].second;
                    mini=i;
                }
            }
            if(maxl<=minr)
            {
                ans++;
                for(i=0;i<n;i++)
                {
                    cur[i]++;
                }
            }
            else
            {
                cur[mini]++;
            }
        }
        printf("Case #%d: %d\n",c+1,ans);
    }
    return 0;
}

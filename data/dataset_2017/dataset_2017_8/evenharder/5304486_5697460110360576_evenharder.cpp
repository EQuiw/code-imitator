#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <utility>
#include <cmath>
#define _FILE_INPUT 0

int n,p;
int s[51];
int a[51][51];
int l[51];//index
std::pair<int, int> d[51];//number of sets
int done;
int ans;
std::pair<int, int> getRange(int x, int b)
{
    return std::make_pair(int(ceil(x/(1.1*b))), int(floor(x/(0.9*b))));
}
std::pair<int, int> getIntersect(std::pair<int, int> p1, std::pair<int, int> p2)
{
    if(p1.first>p2.first)
    {
        return getIntersect(p2,p1);
    }
    return std::make_pair(p2.first, std::min(p1.second, p2.second));
}
void recur(int x)
{
    if(done) return;
    if(x>n)
    {
        ans++;
        done=1;
        return;
    }
    while(l[x]<=p)
    {
        auto pi = getRange(a[x][l[x]], s[x]);
        if(pi.first<=pi.second)
        {
            d[x] = getIntersect(d[x-1], pi);
            if(d[x-1].second<d[x].first) return;
            if(d[x].first<=d[x].second)
            {
                recur(x+1);
                if(done) return;
            }
        }
        l[x]++;
    }
    done=2;
    return;
}
void process()
{
    int t;
    scanf("%d",&t);
    for(int t_=0;t_<t;t_++)
    {
        memset(l,0,sizeof(l));
        memset(d,0,sizeof(d));
        done=0;
        ans=0;
        scanf("%d%d",&n,&p);
        d[0]=std::make_pair(0,1000000);
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&s[i]);
            l[i]=1;
        }
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=p;j++)
            {
                scanf("%d",&a[i][j]);
            }
            std::sort(a[i]+1,a[i]+p+1);
        }
        while(done!=2)
        {
            done=0;
            recur(1);
            for(int i=1;i<=n;i++)
            {
                l[i]++;
            }
        }
        printf("Case #%d: ",t_+1);
        printf("%d\n",ans);
    }
}

int main()
{
    #if _FILE_INPUT
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
    #endif

    process();

    #if _FILE_INPUT
    fclose(stdin);
    fclose(stdout);
    #endif
}
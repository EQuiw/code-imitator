#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <string>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <set>
#include <map>
#include <queue>
#include <vector>
#define LL long long
#define CLR(a,x) memset(a,x,sizeof(a))
using namespace std;
const double DINF=(double)1e50;
const LL LINF=(LL)1e18;
const int N=110;
template <typename T>inline void read(T &x)
{
    x=0;bool f=false;char ch=getchar();
    while (ch<'0'||'9'<ch) {if (ch=='-') f=!f;ch=getchar();}
    while ('0'<=ch&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
    if (f) x=-x;
}
inline void MIN(LL &x,LL y) {if(y<x) x=y;}
int n,q,x,E[N],S[N];
LL G[N][N];
double ans[N][N],dis[N];
bool inq[N];
queue<int> Q;
void spfa(int st,double *c)
{
    while (!Q.empty()) Q.pop();
    for(int i=1;i<=n;i++) c[i]=DINF;

    c[st]=0.0;
    inq[st]=true;
    Q.push(st);
    while(!Q.empty())
    {
        int u=Q.front(); Q.pop(); inq[u]=false;
        for(int i=1;i<=n;i++)
        {
            if(G[u][i]>E[u]) continue;
            double ti=(double)G[u][i]/S[u];
            if(c[i]>ti+c[u])
            {
                c[i]=ti+c[u];
                if(!inq[i]) inq[i]=1, Q.push(i);
            }
        }
    }
}
int main()
{
    #ifdef VGel
    freopen("C-small-attempt0.in","r",stdin);
    freopen("C.out","w",stdout);
    #endif // VGel
    int T_T;read(T_T);
    for (int T=1;T<=T_T;T++)
    {
        scanf("%d%d",&n,&q);
        for(int i=1;i<=n;i++) read(E[i]),read(S[i]);

        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++){read(x);if(x==-1) G[i][j]=LINF;else G[i][j]=x;}

        for(int k=1;k<=n;k++)
            for(int i=1;i<=n;i++)
                for(int j=1;j<=n;j++)
                    MIN(G[i][j],G[i][k]+G[k][j]);

        for(int i=1;i<=n;i++) spfa(i,ans[i]);

        printf("Case #%d:",T);
        while(q--)
        {
            int st,ed;
            read(st),read(ed);
            printf(" %.10lf",ans[st][ed]);
        }
        putchar('\n');
    }
    return 0;
}

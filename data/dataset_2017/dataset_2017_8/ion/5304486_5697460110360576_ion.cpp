/* ***************************************
Author        :Scau.ion
Created Time  :2017/04/15 09:44:05 UTC+8
File Name     :ion.cpp
*************************************** */

#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define ULL unsigned long long
#define PB push_back
#define MP make_pair
#define PII pair<int,int>
#define VI vector<int>
#define VPII vector<PII>
#define X first
#define Y second
#define IOS ios::sync_with_stdio(0);cin.tie(0);
#define IN freopen("B-small-attempt1.in", "r", stdin);
#define OUT freopen("B-small-attempt1.out", "w", stdout);

const double eps=1e-9;

int sgn(double x)
{
    if (fabs(x)<eps) return 0;
    if (x>0) return 1;
    return -1;
}

int ri[10];
int qi[10][10];
int ans;
bool vis[10];
int n,p;

void dfs(int st,int gs)
{
    if (st>p)
    {
        ans=max(ans,gs);
        return;
    }
    dfs(st+1,gs);
    for (int j=1;j<=p;++j)
    {
        if (vis[j]==0)
        {
            int l=0,r=1e6+1;
            while (l+1<r)
            {
                int mid=(l+r)/2;
                double mi1=(double)mid*ri[1]*0.9;
                double mi2=(double)mid*ri[2]*0.9;
                if (sgn(qi[1][st]-mi1)>-1&&sgn(qi[2][j]-mi2)>-1) l=mid;
                else r=mid;
            }
            double ma1=(double)l*ri[1]*1.1;
            double ma2=(double)l*ri[2]*1.1;
            if (sgn(ma1-qi[1][st])>-1&&sgn(ma2-qi[2][j])>-1)
            {
                vis[j]=1;
                dfs(st+1,gs+1);
                vis[j]=0;
            }
        }
    }
    return;
}

int main()
{
    IN;
    OUT;
    IOS;
    int t;
    cin>>t;
    for (int i=1;i<=t;++i)
    {
        cin>>n>>p;
        for (int j=1;j<=n;++j)
            cin>>ri[j];
        for (int j=1;j<=n;++j)
            for (int k=1;k<=p;++k)
                cin>>qi[j][k];
        ans=0;
        if (n==1)
        {
            for (int j=1;j<=p;++j)
            {
                int l=0,r=1e6+1;
                while (l+1<r)
                {
                    int mid=(l+r)/2;
                    double mi=(double)mid*ri[1]*0.9;
                    if (sgn(qi[1][j]-mi)>-1) l=mid;
                    else r=mid;
                }
                double ma=(double)l*ri[1]*1.1;
                if (sgn(ma-qi[1][j])>-1) ++ans;
            }
        }
        else 
        {
            memset(vis,0,sizeof vis);
            dfs(1,0);
        }
        cout<<"Case #"<<i<<": "<<ans<<endl;
    }
    return 0;
}

#include<cmath>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
#define pack pair<int,int>
#define u first
#define v second

int solve(const vector<vector<pack>>& p, int n)
{
    const int N=1<<20;
    vector<vector<int>> a(N+1, vector<int>(n, 0));
    vector<vector<int>> s(N+1, vector<int>(n, 0));
    
    for(int i=0; i<n; i++)
        for(const pack& d : p[i])
        {
            a[d.u][i]++;
            s[min(d.v, N)][i]++;
        }
    
    a[0].assign(n, 0);
    vector<int> d(n, 0);
    int ans=0;
    
    for(int i=1; i<N; i++)
    {
        for(int j=0; j<n; j++)
        {
            int tmp=min(s[i][j], d[j]);
            s[i][j]-=tmp;
            d[j]-=tmp;
            a[i][j]+=a[i-1][j]-s[i][j];
        }
        
        int cnt=N;
        
        for(int j=0; j<n; j++)
            cnt=min(cnt, a[i][j]);
        
        for(int j=0; j<n; j++)
            d[j]+=cnt, a[i][j]-=cnt;
        
        ans+=cnt;
    }
    
    return ans;
}

int main()
{
    int ncase;
    scanf("%d", &ncase);
    
    for(int cases=1; cases<=ncase; cases++)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        vector<vector<pack>> a(n);
        vector<int> r(n);
        
        for(int i=0; i<n; i++)
            scanf("%d", &r[i]);
        
        for(int i=0; i<n; i++)
        {
            double x=r[i]*1.1;
            double y=r[i]*0.9;
            
            for(int j=0; j<m; j++)
            {
                int p;
                scanf("%d", &p);
                a[i].push_back(pack(ceil(p/x), floor(p/y+1)));
            }
        }
        
        printf("Case #%d: %d\n", cases, solve(a, n));
    }
}

/*

6

2 1
500 300
900
660

2 1
500 300
1500
809

2 2
50 100
450 449
1100 1101

2 1
500 300
300
500

1 8
10
11 13 17 11 16 14 12 18

3 3
70 80 90
1260 1500 700
800 1440 1600
1700 1620 900

*/

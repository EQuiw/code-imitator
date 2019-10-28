#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
    int ncase;
    scanf("%d", &ncase);
    
    for(int cases=1; cases<=ncase; cases++)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        vector<double> e(n), s(n);
        vector<vector<double>> d(n, vector<double>(n));
        
        for(int i=0; i<n; i++)
            scanf("%lf%lf", &e[i], &s[i]);
        
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                scanf("%lf", &d[i][j]);
        /*
        for(int k=0; k<n; k++)
            for(int i=0; i<n; i++)
                for(int j=0; j<n; j++)
                    if( d[i][k]>=0 && d[k][j]>=0 )
                        d[i][j]=min(d[i][j], d[i][k]+d[k][j]);
        */
        
        for(printf("Case #%d:", cases); m>0; m--)
        {
            int u, v;
            u--, v--;
            scanf("%d%d", &u, &v);
            vector<double> p(n, 0), t(n, 1e100);
            t[0]=0;
            
            for(int i=1; i<n; i++)
                p[i]=p[i-1]+d[i-1][i];
            
            for(int i=0; i<n; i++)
                for(int j=i; j<n && p[j]-p[i]<=e[i]; j++)
                    t[j]=min(t[j], t[i]+(p[j]-p[i])/s[i]);
            
            printf(" %.10f", t[n-1]);
        }
        
        printf("\n");
    }
}

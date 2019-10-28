#include<cstdio>
#include<algorithm>
using namespace std;

int main()
{
    int ncase;
    scanf("%d", &ncase);
    
    for(int cases=1; cases<=ncase; cases++)
    {
        int d, n;
        double ans=0;
        
        for(scanf("%d%d", &d, &n); n>0; n--)
        {
            double p, s;
            scanf("%lf%lf", &p, &s);
            ans=max(ans, (d-p)/s);
        }
        
        printf("Case #%d: %.10f\n", cases, d/ans);
    }
}

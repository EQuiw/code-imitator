#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    freopen("A-small-attempt0.in","r",stdin);
    freopen("A-small-attempt0.out","w",stdout);
    int c,t,i,d,n,k,s;
    double m;
    scanf("%d",&t);
    for(c=0;c<t;c++)
    {
        scanf("%d %d",&d,&n);
        m=0.0;
        for(i=0;i<n;i++)
        {
            scanf("%d %d",&k,&s);
            m=max(m,1.0*(d-k)/s);
        }
        printf("Case #%d: %.6f\n",c+1,d/m);
    }
    return 0;
}

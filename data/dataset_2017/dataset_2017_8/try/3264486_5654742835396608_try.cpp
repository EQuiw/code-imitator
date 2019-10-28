#include <cstdio>
#include <iostream>
#include <queue>
#include <functional>
using namespace std;

priority_queue<int> Q,E;
int n,k;

int main()
{
    freopen("C-small-1-attempt0.in","r",stdin);
    freopen("C-small-1-attempt0.out","w",stdout);
    int c,t,i,x,y,z;
    scanf("%d",&t);
    for(c=0;c<t;c++)
    {
        scanf("%d %d",&n,&k);
        Q=E;
        Q.push(n);
        for(i=0;i<k;i++)
        {
            x=Q.top();
            Q.pop();
            y=x/2;
            z=(x-1)/2;
            Q.push(y);
            Q.push(z);
        }
        printf("Case #%d: %d %d\n",c+1,y,z);
    }
    return 0;
}

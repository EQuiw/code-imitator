#include <cstdio>
#include <iostream>
#include <algorithm>
#define MAXN 1000
using namespace std;

char ans[MAXN+1];
int ord[MAXN+1];
int n,m,r,o,y,g,b,v;

int main()
{
    freopen("B-small-attempt0.in","r",stdin);
    freopen("B-small-attempt0.out","w",stdout);
    int c,t,i;
    scanf("%d",&t);
    for(c=0;c<t;c++)
    {
        scanf("%d %d %d %d %d %d %d",&n,&r,&o,&y,&g,&b,&v);
        printf("Case #%d: ",c+1);
        if((r*2>n)||(y*2>n)||(b*2>n))
        {
            printf("IMPOSSIBLE\n");
            continue;
        }
        m=0;
        for(i=0;i<n;i=i+2)
        {
            ord[m++]=i;
        }
        for(i=1;i<n;i=i+2)
        {
            ord[m++]=i;
        }
        m=0;
        if((r>=y)&&(y>=b))
        {
            while(--r>=0)
            {
                ans[ord[m++]]='R';
            }
            while(--y>=0)
            {
                ans[ord[m++]]='Y';
            }
            while(--b>=0)
            {
                ans[ord[m++]]='B';
            }
        }
        else if((r>=b)&&(b>=y))
        {
            while(--r>=0)
            {
                ans[ord[m++]]='R';
            }
            while(--b>=0)
            {
                ans[ord[m++]]='B';
            }
            while(--y>=0)
            {
                ans[ord[m++]]='Y';
            }
        }
        else if((y>=b)&&(b>=r))
        {
            while(--y>=0)
            {
                ans[ord[m++]]='Y';
            }
            while(--b>=0)
            {
                ans[ord[m++]]='B';
            }
            while(--r>=0)
            {
                ans[ord[m++]]='R';
            }
        }
        else if((y>=r)&&(r>=b))
        {
            while(--y>=0)
            {
                ans[ord[m++]]='Y';
            }
            while(--r>=0)
            {
                ans[ord[m++]]='R';
            }
            while(--b>=0)
            {
                ans[ord[m++]]='B';
            }
        }
        else if((b>=r)&&(r>=y))
        {
            while(--b>=0)
            {
                ans[ord[m++]]='B';
            }
            while(--r>=0)
            {
                ans[ord[m++]]='R';
            }
            while(--y>=0)
            {
                ans[ord[m++]]='Y';
            }
        }
        else
        {
            while(--b>=0)
            {
                ans[ord[m++]]='B';
            }
            while(--y>=0)
            {
                ans[ord[m++]]='Y';
            }
            while(--r>=0)
            {
                ans[ord[m++]]='R';
            }
        }
        ans[m]='\0';
        printf("%s\n",ans);
    }
    return 0;
}

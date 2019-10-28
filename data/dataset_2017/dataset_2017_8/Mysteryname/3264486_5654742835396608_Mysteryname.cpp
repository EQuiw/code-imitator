
/*
Contest: Google Code Jam 2017 [Qualification Round]
Problem: C. Bathroom Stalls (30 Points)

Author: Phawin Prongpaophan
*/
#include<stdio.h>
#include<algorithm>
#include<utility>
#define LL long long
#define P pair <LL,LL>
#define x first
#define y second
#define mp make_pair
using namespace std;




P solve(LL pos,LL n)
{
    if(pos==1)
    {
        P ret;
        ret.x = (n+1)/2;
        ret.y = (n+1)-(ret.x);
        return ret;
    }
    //Go!
    LL smallHalf = (n-1)/2;
    LL bigHalf = (n-1) - smallHalf;
    LL rem = pos-1;
    if(rem%2==1)    //Big
    {
        return solve((rem+1)/2,bigHalf);
    }
    return solve(rem/2,smallHalf);
}



int main()
{
    freopen("C-small-1-attempt0.in","r",stdin);
    freopen("C-Small1Output.txt","w",stdout);
    int tc; scanf("%d",&tc);
    for(int p=1;p<=tc;p++)
    {
        printf("Case #%d: ",p);
        LL n,k; scanf("%lld%lld",&n,&k);
        P ans = solve(k,n);
        printf("%lld %lld\n",ans.y-1,ans.x-1);
    }
    return 0;
}


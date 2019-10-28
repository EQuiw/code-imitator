
/*
Contest: Google Code Jam 2017 [Qualification Round]
Problem: B. Tidy Numbers (20 Points)

Author: Phawin Prongpaophan
*/
#include<stdio.h>
#include<algorithm>
#define LL long long
using namespace std;

LL powTen[19];
LL someOne[19];


void preProcess()
{
    powTen[0] = 1; for(int i=1;i<19;i++) powTen[i] = powTen[i-1]*10;
    someOne[0] = 1;
    for(int i=1;i<19;i++)
    {
        someOne[i] = (10*someOne[i-1])+1;
    }
}

int getHighestDigit(LL val)
{
    for(int i=18;i>=0;i--)
    {
        if(val/powTen[i]>0) return i;
    }
}

LL getTidy(LL val)
{
    if(val<10) return val;
    int sd = getHighestDigit(val);
    LL firstDigit = val/powTen[sd];
    LL remaining = val-(firstDigit*powTen[sd]);
    LL det = firstDigit*someOne[sd-1];
    if(remaining<det) return ((firstDigit*powTen[sd])-1);
    return (firstDigit*powTen[sd]) + getTidy(remaining);
}

LL solve()
{
    LL w; scanf("%lld",&w);
    LL ret = getTidy(w);
    return ret;
}


int main()
{
    freopen("B-small-attempt0.in","r",stdin);
    freopen("B-SmallOutput.txt","w",stdout);
    preProcess();
    int tc; scanf("%d",&tc);
    for(int p=1;p<=tc;p++)
    {
        printf("Case #%d: ",p);
        LL ans = solve();
        printf("%lld\n",ans);
    }
    return 0;
}

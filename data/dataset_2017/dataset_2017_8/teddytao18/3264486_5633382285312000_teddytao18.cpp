#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;
#define ll long long

int numdig(ll n)
{
    int res;
    for (res=0;n;n/=10)
        res++;
    return res;
}

ll dfs(ll n, int b, ll curr, int last)
{
    if (!b)
        return curr;
    int z;
    curr*=10;
    z=n/(ll)pow(10,b-1);
    if (z<last)
        return 0;
    if (z==last)
        return dfs(n%(ll)pow(10,b-1),b-1,curr+z,z);
    return max((curr+z)*(ll)pow(10,b-1)-1, dfs(n%(ll)pow(10,b-1),b-1,curr+z,z));
}

int main()
{
    int T;
    scanf("%d",&T);
    for (int t=1;t<=T;t++)
    {
        int b;
        ll n,ans;
        scanf("%lld",&n);
        b=numdig(n);
        ans=dfs(n,b,0,0);
        printf("Case #%d: %lld\n",t,ans);
    }
}

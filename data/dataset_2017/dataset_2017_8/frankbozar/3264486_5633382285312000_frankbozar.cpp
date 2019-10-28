#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;

vector<lld> gen(int n=18)
{
    vector<vector<lld>> a(n+1);
    a[0].push_back(0);
    vector<lld> ans;
    
    for(int i=1; i<=n; i++)
    {
        for(lld p : a[i-1])
        {
            for(lld j=max(p%10, 1LL); j<=9; j++)
            {
                a[i].push_back(p*10+j);
                ans.push_back(p*10+j);
            }
        }
    }
    
    return ans;
}

int main()
{
    int ncase;
    scanf("%d", &ncase);
    vector<lld> t=gen();
    
    for(int cases=1; cases<=ncase; cases++)
    {
        lld n;
        scanf("%lld", &n);
        printf("Case #%d: %lld\n", cases, *--upper_bound(t.begin(), t.end(), n));
    }
}

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=1e4+5;
const double eps=1e-3;
const int INF=1e9;

int main()
{
    freopen("A-small-attempt0.in", "r", stdin);
    freopen("A-small-attempt0.out", "w", stdout);
    int t, ca=1;
    scanf("%d", &t);
    while(t--)
    {
        printf("Case #%d: ", ca++);
        int n, d;
        scanf("%d%d", &d, &n);
        double maxn=0;
        for(int i=0;i<n;i++)
        {
            int k, s;
            scanf("%d%d", &k, &s);
            maxn=max(maxn, (d-k)*1.0/s);
        }
        printf("%.6f\n", d*1.0/maxn);
    }
    return 0;
}

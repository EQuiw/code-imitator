#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i,n) for(int (i)=0;(i)<(int)(n);++(i))
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define fi first
#define se second

double solve()
{
    int d,n;
    cin >>d >>n;

    double t=0;
    rep(i,n)
    {
        int k,s;
        cin >>k >>s;

        double dist = d-k;
        double tmp = dist/s;
        t = max(t,tmp);
    }

    return d/t;
}

int main()
{
    int T;
    cin >>T;
    rep(t,T)
    {
        printf("Case #%d: %.10f\n", t+1, solve());
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i,n) for(int (i)=0;(i)<(int)(n);++(i))
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define fi first
#define se second

const double INF=1e12;

ll d[100][100];
double T[100][100];

void solve()
{
    int n,q;
    cin >>n >>q;

    vector<int> e(n),s(n);
    rep(i,n) cin >>e[i] >>s[i];

    rep(i,n)rep(j,n)
    {
        int tmp;
        cin >>tmp;
        if(tmp == -1) d[i][j]=LLONG_MAX/4;
        else d[i][j]=tmp;
    }

    rep(k,n)rep(i,n)rep(j,n) d[i][j] = min(d[i][j], d[i][k]+d[k][j]);

    // rep(i,n)rep(j,n) printf(" d[%d][%d] = %lld\n", i,j,d[i][j]);

    fill(T[0],T[100],INF);
    rep(i,n)
    {
        // iをスタートにするので、iにいる馬を使う
        rep(j,n)
        {
            if(i==j)
            {
                T[i][i]=0;
                continue;
            }

            if(d[i][j]<=e[i]) T[i][j] = (double)d[i][j]/s[i];
        }
    }

    rep(k,n)rep(i,n)rep(j,n) T[i][j] = min(T[i][j], T[i][k]+T[k][j]);

    rep(QUERY,q)
    {
        int u,v;
        cin >>u >>v;
        --u;
        --v;

        double ans=T[u][v];
        assert(ans<INF);
        printf(" %.10f", ans);
    }
    printf("\n");
}

int main()
{
    int cases;
    cin >>cases;
    rep(t,cases)
    {
        printf("Case #%d:", t+1);
        solve();
    }
    return 0;
}

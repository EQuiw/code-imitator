#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
typedef long long ll;
typedef pair<int,int> pt;
const double base = ll(1000000007)*ll(1000000);
const int maxn = 1002;

int n, Q;
int D[maxn][maxn];
ll sum[maxn], E[maxn], S[maxn];
int kt[maxn][maxn], timeht;
double f[maxn][maxn], res;

ll get(int i,int j) {
    return sum[j] - sum[i];
}

double dfs(int city,int last) {
    if (kt[city][last]!=timeht) {
        kt[city][last] = timeht;
        f[city][last] = base;
    }
    else return f[city][last];

    if (city==n) return f[city][last] = 0;

    for (int i=city+1;i<=n;i++) {
        if (get(last,i) <= E[last])
                f[city][last] = min(f[city][last], double(get(city,i))/S[last] + dfs(i,last));

        if (last!=city) f[city][last] = min(f[city][last], dfs(city,city));
    }

    return f[city][last];
}

void solve(int test) {
    int i,j,k,u,v,s,t;
    sum[0] = sum[1] = 0;

    scanf("%d%d",&n,&Q);
    for (i=1;i<=n;i++) scanf("%I64d%I64d",&E[i],&S[i]);
    for (i=1;i<=n;i++) {for (j=1;j<=n;j++) scanf("%d",&D[i][j]); sum[i+1] = sum[i] + D[i][i+1];}
    scanf("%d%d",&s,&t);

    timeht++;
    res = dfs(1,1);

    printf("Case #%d: %.6lf\n",test,res);
}

int main()
{
    int i,t;
    freopen("C.in","r",stdin);
    freopen("C1.out","w",stdout);

    scanf("%d",&t);
    for (i=1;i<=t;i++) solve(i);

    return 0;
}

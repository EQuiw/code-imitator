#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
typedef long long ll;
typedef pair<int,int> pt;
const int base = 1000000007;
const int maxn = 100002;
const double esp = 1e-9;

int n, D;
double res;
pt a[maxn];

bool ok(double v) {
    int i,j;
    for (i=1;i<=n;i++) if (a[i].y < v-esp) {
        double t = double(a[i].x) / (v - a[i].y);
        double x = v*t;
        if (x < double(D)-esp) return false;
    }
    return true;
}

void solve(int test) {
    int i,j,k,u,v;
    double l,r,x;

    scanf("%d%d",&D,&n); res = base;
    for (i=1;i<=n;i++) {scanf("%d%d",&a[i].x,&a[i].y); res = min(res,double(a[i].y));}

   /* l = 0; r = 1000000000;
    while (abs(r-l) / res > esp) {
        x = (l+r) / 2;
        if (ok(x)) {res = x; l = x+esp;}
        else r = x-esp;
    }*/
    sort(a+1,a+n+1);
    double slowest = esp;
    for (i=n;i>=1;i--) {
        slowest = max(slowest, double(D-a[i].x)/a[i].y);
    }
    res = D / slowest;

    printf("Case #%d: %.6lf\n",test,res);
}

int main()
{
    int i,t;
    freopen("A.in","r",stdin);
    freopen("A1.out","w",stdout);

    scanf("%d",&t);
    for (i=1;i<=t;i++) solve(i);

    return 0;
}

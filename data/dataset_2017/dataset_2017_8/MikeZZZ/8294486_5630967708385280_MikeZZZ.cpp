#include <bits/stdc++.h>
using namespace std;
const int N = 1000 + 5;
typedef long long LL;
int T, Case, n;
LL D, x[N], s[N];

int main() {
    freopen("A-small-attempt0.in", "r", stdin);
    freopen("out0.out", "w", stdout);
    scanf("%d", &T);
    while(T--) {
        scanf("%lld%d", &D, &n);
        double t = 0;
        for(int i = 0; i < n; i++) {
            LL x, s;
            scanf("%lld%lld", &x, &s);
            t = max(t, 1.0*(D-x)/s);
        }
        printf("Case #%d: %.10f\n", ++Case, D/t);
    }
    return 0;
}

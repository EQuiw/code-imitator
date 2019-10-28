#include <iostream>
#include <cstdio>

using namespace std;

#define INF 0x7f7f7f7f7f7f7f7f

int main() {
    freopen("A-small-attempt1.in", "r", stdin);
    freopen("A-small-attempt1.out", "w", stdout);
    int T, cnt = 0;
    scanf("%d", &T);
    while(T--) {
        double D; int N;
        scanf("%lf%d", &D, &N);
        double k, s, ans = 0.0;
        for(int i = 1; i <= N; i++) {
            scanf("%lf%lf", &k, &s);
            double tmp = 1.0 * (D - k) / s;
            if(tmp > ans) ans = tmp;
        }
        printf("Case #%d: %.8lf\n", ++cnt, D / ans);
    }
}

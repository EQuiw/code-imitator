#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

bool flag[1010];

int main() {
    freopen("C-small-1-attempt0.in", "r", stdin);
    freopen("C-small-1-attempt0.out", "w", stdout);
    int T, cnt = 0;
    scanf("%d", &T);
    while(T--) {
        memset(flag, false, sizeof(flag));
        int n, k;
        scanf("%d%d", &n, &k);
        flag[0] = flag[n+1] = true;
        for(int i = 1; i <= k; i++) {
            int nl, nr, ans, mmin = -1, mmax = -1;
            for(int j = 1; j <= n; j++) if(!flag[j]) {
                int ls, rs;
                for(int l = j-1; l >= 0; l--) if(flag[l]) {
                    ls = j - l - 1; break;
                }
                for(int l = j+1; l <= n+1; l++) if(flag[l]) {
                    rs = l - j - 1; break;
                }
                if(min(ls, rs) == mmin) {
                    if(max(ls, rs) > mmax) nl = ls, nr = rs, ans = j, mmax = max(ls, rs);
                }
                if(min(ls, rs) > mmin) {
                    nl = ls, nr = rs, ans = j, mmin = min(ls, rs), mmax = max(ls, rs);
                }
            }
            //printf("%d\n", ans);
            flag[ans] = true;
            if(i == k) {
                printf("Case #%d: %d %d\n", ++cnt, max(nl, nr), min(nl, nr));
            }
        }
    }
}

#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define N 110

int T, t = 1;

int n, q;
int housekm[N], housesp[N];
int dis[N][N];
int querys[N], querye[N];
double ans[N];
double dp[N];

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &q);
        for(int i = 0; i < n; ++i) {
            scanf("%d%d", &housekm[i], &housesp[i]);
        }
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                scanf("%d", &dis[i][j]);
            }
        }
        for(int i = 0; i < q; ++i) {
            scanf("%d%d", &querys[i], &querye[i]);
            --querys[i];
            --querye[i];
            for(int j = 0; j < n; ++j){
                dp[j] = -1;
            }
            dp[querys[i]] = 0;
            for(int j = 0; j < n; ++j){
                int last = housekm[j];
                for(int k = j + 1; k < n; ++k){
                    last -= dis[k - 1][k];
                    if(last >= 0){
                        if(dp[k] < 0 || dp[k] > dp[j] + 1.0 * (housekm[j] - last) / housesp[j]){
                            dp[k] = dp[j] + 1.0 * (housekm[j] - last) / housesp[j];
                        }
                    }else{
                        break;
                    }
                }
            }
            ans[i] = dp[querye[i]];
        }
        printf("Case #%d:", t++);
        for(int i = 0; i < q; ++i){
            printf(" %f", ans[i]);
        }
        printf("\n");
    }
    return 0;
}

#include <cstdio>
#include <cstring>

char S[1005];
int K;

int solve() {
    int n = strlen(S);
    int ret = 0;
    for (int i = 0; i < n; i++) {
        if (S[i] != '+' && i+K <= n) {
            ret++;
            for (int j = i; j < i+K; j++) {
                S[j] = ((S[j] == '+') ? '-' : '+');
            }
        }
    }
    for (int i = 0; i < n; i++) if (S[i] == '-') return -1;
    return ret;
}

int main() {
    int T; scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        scanf("%s%d", S, &K);
        int ans = solve();
        printf("Case #%d: ", t);
        if (ans == -1) {
            printf("IMPOSSIBLE\n");
        } else {
            printf("%d\n", ans);
        }
    }
    return 0;
}
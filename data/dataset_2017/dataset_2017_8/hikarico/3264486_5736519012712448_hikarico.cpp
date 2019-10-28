#include <bits/stdc++.h>
using namespace std;
const int N = 1005;

int k, t;
char s[N];

int main() {
    int tc = 0;
    scanf("%d", &t);
    while (t--) {
        scanf("%s%d", s, &k);
        int n = strlen(s);
        for (int i = 0; i < n; ++i) {
            if (s[i] == '+')
                s[i] = 1;
            else
                s[i] = 0;
        }
        int flips = 0;
        for (int i = 0; i+k <= n; ++i) {
            if (s[i] == 0) {
                // flip
                flips += 1;
                for (int j = 0; j < k; ++j)
                    s[j+i] ^= 1;
            }
        }
        int one = 0;
        for (int i = 0; i < n; ++i)
            if (s[i] == 1)
                ++one;
        printf("Case #%d: ", ++tc);
        if (one == n) printf("%d\n", flips);
        else printf("IMPOSSIBLE\n");
    }
}

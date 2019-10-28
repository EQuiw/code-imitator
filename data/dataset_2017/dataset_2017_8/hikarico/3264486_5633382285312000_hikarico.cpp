#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int t, tc;
char s[20];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%s", s);
        int n = strlen(s);
        int reset = n;
        for (int i = 1; i < n; ++i) {
            while (reset <= i) {
                s[reset++] = '9';
            }
            if (s[i-1] <= s[i])
                continue;
            else {
                reset = i;
                s[i-1] -= 1;
                i -= 2;
            }
        }
        int i = 0;
        while (i < n - 1 && s[i] == '0')
            ++i;
        printf("Case #%d: %s\n", ++tc, s + i);
    }
}

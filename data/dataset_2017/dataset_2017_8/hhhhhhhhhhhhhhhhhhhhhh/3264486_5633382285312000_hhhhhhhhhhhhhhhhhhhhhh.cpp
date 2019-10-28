#include <bits/stdc++.h>
using namespace std;

char s[110], ans[110];

int main() {
    freopen("B-small-attempt1.in", "r", stdin);
    freopen("B-small-attempt1.out", "w", stdout);

    int test;
    scanf("%d", &test);

    for(int _ = 1; _ <= test; _++) {
        scanf("%s", s);
        int lens = strlen(s);
        long long ret = 0;
        for(int i = 0; i < lens; i++) {
            bool judge = true;
            for(int j = i + 1; j < lens; j++) {
                if(s[j] < s[i]) {
                    judge = false;
                    break;
                } else if(s[j] > s[i]) {
                    break;
                }
            }
            if(judge) ans[i] = s[i];
            else {
                ans[i] = s[i] - 1;
                for(int j = i + 1; j < lens; j++) {
                    ans[j] = '9';
                }
                break;
            }
        }
        for(int i = 0; i < lens; i++) {
            ret = ret * 10 + ans[i] - '0';
        }
        printf("Case #%d: %I64d\n", _, ret);
    }

    return 0;
}

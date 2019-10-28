#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define LL long long

int num[20];

int main() {
    freopen("B-small-attempt2.in", "r", stdin);
    freopen("B-small-attempt2.out", "w", stdout);
    int T, cnt = 0;
    scanf("%d", &T);
    while(T--) {
        memset(num, 0, sizeof(num));
        LL n;
        scanf("%lld", &n);
        while(n) {
            num[++num[0]] = n % 10, n /= 10;
        }
        for(int i = 1; i <= num[0]; i++) {
            if(num[i] < num[i+1]) {
                for(int j = 1; j <= i; j++) num[j] = 9;
                num[i+1]--;
            }
        }
        while(num[num[0]] == 0) num[0]--;
        printf("Case #%d: ", ++cnt);
        for(int i = num[0]; i; i--) {
            printf("%d", num[i]);
        }
        printf("\n");
    }
}

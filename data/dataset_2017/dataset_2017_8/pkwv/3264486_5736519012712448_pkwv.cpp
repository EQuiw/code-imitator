#include<bits/stdc++.h>
#include<stdio.h>
#include<string.h>

using namespace std;
typedef long long ll;
typedef double db;
const int N = 1005;

char s[N];
int num[N];

int main() {
#ifdef PKWV
    freopen("A-small-attempt0.in","r",stdin);
    freopen("A-small-attempt0.out","w",stdout);
#endif // PKWV
    int T;
    scanf("%d",&T);
    for(int ca = 1; ca <= T; ca ++) {
        int k;
        scanf("%s%d",s,&k);
        int n = strlen(s);
        for(int i = 0; i < n; i++) {
            num[i] = 0;
        }
        int total = 0, res = 0;
        bool ok(true);
        for(int i = 0; i < n; i ++) {
            if(i - k >= 0) total -= num[i-k];
//            printf("~~  %d  %d\n", i, total);
            int c = s[i] == '-'? 1: 0;
            if((total + c) % 2 == 0) {
                num[i] = 0;
            } else {
                if(i + k <= n) {
                    num[i] = 1;
                    ++ total;
                } else {
                    ok = false;
                    break;
                }
            }
            res += num[i];
//            printf("i:  %d  num:  %d\n", i, num[i]);
        }
        printf("Case #%d: ", ca);
        if(ok) printf("%d\n", res);
        else printf("IMPOSSIBLE\n");
    }
    return 0;
}

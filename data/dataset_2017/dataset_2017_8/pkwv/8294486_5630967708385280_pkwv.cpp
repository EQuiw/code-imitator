#include<bits/stdc++.h>
#include<stdio.h>
#include<string.h>

using namespace std;
typedef long long ll;
typedef double db;
const int N = 100005;

int main() {
#ifdef PKWV
    freopen("A-small-attempt0.in","r",stdin);
    freopen("A-small-attempt0.out","w",stdout);
#endif // PKWV
    int T;
    scanf("%d",&T);
    for(int ca=1; ca<=T; ca++) {
        int d,n;
        scanf("%d%d",&d,&n);
        db t(0);
        for(int i=0; i<n; i++) {
            int k,s;
            scanf("%d%d",&k,&s);
            t = max(t, (db)(d-k)/(db)s);
        }
        printf("Case #%d: %f\n",ca, d/t);
    }
    return 0;
}

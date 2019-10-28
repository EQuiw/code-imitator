#include <bits/stdc++.h>
using namespace std;
const int N = 20 + 5;
int T, Case;
map<int,int> cnt;
int n, k;

int main() {
    freopen("out.txt","w",stdout);
    freopen("C-small-1-attempt0.in","r",stdin);
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &k); k--;
        cnt.clear();
        cnt[n] = 1;
        while(k > 0) {
            auto p = *cnt.rbegin();
            int x = min(k, p.second);
            k -= x;
            if((cnt[p.first] -= x) == 0) cnt.erase(p.first);
            if(p.first&1) {
                cnt[p.first/2] += x*2;
            }else {
                cnt[p.first/2] += x;
                cnt[p.first/2-1] += x;
            }
        }
        auto p = cnt.rbegin();
        int mi, mx;
        if(p->first&1) mi = mx = p->first/2;
        else mi = p->first/2-1, mx = p->first/2;
        printf("Case #%d: %d %d\n", ++Case, mx, mi);
    }
    return 0;
}

#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>

using namespace std;

#define DEBUG 0

typedef long long LL;

map<LL, LL> cnt;
map<LL, LL>::reverse_iterator it;

int main() {
    if (!DEBUG) {
        freopen("in", "r", stdin);
        freopen("out", "w", stdout);
    }
    int t, T = 1;
    LL n, m;

    scanf("%d", &t);
    while (t--) {
        scanf("%lld%lld", &n, &m);
        --m;
        cnt.clear();
        cnt[n] = 1;
        while (m) {
            it = cnt.rbegin();
            LL seg = it->first;
            LL num = min(it->second, m);
            cnt[seg] -= num;
            if (cnt[seg] == 0) {
                cnt.erase(seg);
            }
            m -= num;
            if (seg & 1) {
                cnt[seg / 2] += num * 2;
            } else {
                cnt[seg / 2] += num;
                cnt[seg / 2 - 1] += num;
            }
        }
        it = cnt.rbegin();
        LL seg = it->first;
        LL mx = seg / 2, mn = seg / 2;
        if (!(seg & 1)) {
            --mn;
        }
        printf("Case #%d: %lld %lld\n", T++, mx, mn);
    }
    return 0;
}
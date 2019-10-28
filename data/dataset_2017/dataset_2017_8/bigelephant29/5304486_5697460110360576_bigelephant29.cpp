#include<cstdio>
#include<algorithm>
#include<vector>
#include<functional>
#include<cstring>
using namespace std;
const int MAX = 50 + 10;
const int INF = 2147483647;
int need[MAX];
int rec[MAX][MAX];
int left[MAX];
vector<pair<int,int>> vp[MAX];
int main() {
    int TN;
    scanf("%d", &TN);
    for(int casen = 1 ; casen <= TN ; casen++) {
        printf("Case #%d: ", casen);
        int n, m;
        scanf("%d %d", &n, &m);
        for(int i = 0 ; i < n ; i++) {
            scanf("%d", &need[i]);
        }
        for(int i = 0 ; i < n ; i++) {
            for(int j = 0 ; j < m ; j++) {
                scanf("%d", &rec[i][j]);
            }
        }
        for(int i = 0 ; i < n ; i++) {
            sort(rec[i], rec[i]+m);
        }
        int cnt = 0;
        for(int i = 0 ; i < n ; i++) {
            for(int j = 0 ; j < m ; j++) {
                int tmp = (rec[i][j] + need[i] - 1) / need[i];
                if(tmp == 0) continue;
                if(!(9*tmp*need[i]<=10*rec[i][j]&&10*rec[i][j]<=11*tmp*need[i])) tmp--;
                int l = tmp;
                int r = tmp;
                while(l-1 > 0 && 9 * (l-1) * need[i] <= 10 * rec[i][j] &&
                                10 * rec[i][j]<= 11 * (l-1) * need[i]) l--;
                while(9 * (r+1) * need[i] <= 10 * rec[i][j] &&
                      10 * rec[i][j] <= 11* (r+1) * need[i]) r++;
                if(9*l*need[i]<=10*rec[i][j]&&10*rec[i][j]<=11*l*need[i]) {
                    vp[i].push_back(make_pair(l, r));
                }
            }
        }
        memset(left, 0, sizeof(left));
        while(1) {
            int tl = -INF, tr = INF;
            for(int i = 0 ; i < n ; i++) {
                tl = max(tl, vp[i][left[i]].first);
                tr = min(tr, vp[i][left[i]].second);
            }
            if(tl <= tr) {
                cnt++;
                for(int i = 0 ; i < n ; i++) {
                    left[i]++;
                }
            } else {
                for(int i = 0 ; i < n ; i++) {
                    if(vp[i][left[i]].second == tr) {
                        left[i]++;
                    }
                }
            }
            bool get = false;
            for(int i = 0 ; i < n ; i++) {
                if(left[i] >= vp[i].size()) {
                    get = true;
                    break;
                }
            }
            if(get) break;
        }
        printf("%d\n", cnt);
        for(int i = 0 ; i < n ; i++) {
            vp[i].clear();
        }
    }
    return 0;
}

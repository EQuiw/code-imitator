#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<tuple>
using namespace std;
const int MAX = 100 + 10;

int  e[MAX];
double s[MAX];
double ans[MAX][MAX];
int dis[MAX][MAX];

int main() {
    int TN;
    scanf("%d", &TN);
    for(int casen = 1 ; casen <= TN ; casen++) {
        printf("Case #%d:", casen);
        int n, q;
        scanf("%d %d", &n, &q);
        for(int i = 0 ; i < n ; i++) {
            scanf("%d %lf", &e[i], &s[i]);
        }
        for(int i = 0 ; i < n ; i++) {
            for(int j = 0 ; j < n ; j++) {
                ans[i][j] = -1;
                if(i == j) ans[i][j] = 0;
                scanf("%d", &dis[i][j]);
            }
        }

        // solve
        vector< pair<double, int> > v;
        for(int i = 0 ; i < n ; i++) {
            v.push_back(make_pair(s[i], i));
        }
        sort(v.begin(), v.end());
        reverse(v.begin(), v.end()); // fast first

        for(int i = 0 ; i < n ; i++) {
            int now = v[i].second;
            queue<tuple<int, int, double>> q;
            q.push(make_tuple(now, e[now], 0.0));
            while(!q.empty()) {
                tuple<int, int, double> tmp = q.front();
                q.pop();
                int pt = get<0>(tmp);
                int con = get<1>(tmp);
                double nn = get<2>(tmp);
                for(int j = 0 ; j < n ; j++) {
                    if(dis[pt][j] != -1 && con >= dis[pt][j]) {
                        if(ans[now][j] < 0.0 || nn + dis[pt][j] / s[now] < ans[now][j]) {
                            ans[now][j] = nn + dis[pt][j] / s[now];
                            q.push(make_tuple(j, con - dis[pt][j], ans[now][j]));
                        }
                    }
                }
            }
        }
        for(int k = 0 ; k < n ; k++) {
            for(int i = 0 ; i < n ; i++) {
                for(int j = 0 ; j < n ; j++) {
                    if(ans[i][k] >= 0.0 && ans[k][j] >= 0.0 &&
                       (ans[i][j] < 0 || ans[i][k] + ans[k][j] < ans[i][j])) {
                        ans[i][j] = ans[i][k] + ans[k][j];
                    }
                }
            }
        }
        while(q--) {
            int u, v;
            scanf("%d %d", &u, &v);
            u--, v--;
            printf(" %.9f", ans[u][v]);
        }
        puts("");
    }
    return 0;
}

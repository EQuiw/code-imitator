#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <cassert>
using namespace std;


const double eps = 1e-8;
const double pi = acos(-1.0);

const int N = 1005;

double e[N], s[N];
double d[N][N];

double dp[N];

void floyd(int n) {
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) {
                if (d[i][k] == -1 || d[k][j] == -1) continue;
                if (d[i][j] > d[i][k] + d[k][j])
                    d[i][j] = d[i][k] + d[k][j];
            }
}

double get(int i, int j){
    double ret=0;
    for (int p = i + 1; p <= j; p++) {
        ret += d[p - 1][p];
    }
    return ret;
}

int main() {
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    int T;
    cin >> T;

    for (int cas = 1; cas <= T; cas++) {
        int n, q;
        cin >> n >> q;

        for (int i = 1; i <= n; i++) {
            cin >> e[i] >> s[i];
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                cin >> d[i][j];
            }
        }

        int a,b;
        for (int i = 1; i <= q; i++) {
            cin>>a>>b;
        }


//        floyd(n);


        for (int i = 0; i <= n; i++) {
            dp[i] = 1e60;
        }
        dp[n] = 0;
        for (int i = n - 1; i >= 1; i--) {
            for (int j = i + 1; j <= n; j++) {
                double dis = get(i, j);
                if (dis==-1||dis > e[i]) {
                    continue;
                }


                double time = dis / s[i];
//                cout << i << " dis " << j << " " << dis << endl;
                dp[i] = min(dp[i], time + dp[j]);
            }
//            cout << i << " dp " << dp[i] << endl;
        }

        printf("Case #%d: %.8f\n", cas, dp[1]);
    }
    return 0;
}


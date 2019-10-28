/*input
2
3 1
2 3
2 4
4 4
-1 1 -1
-1 -1 1
-1 -1 -1
1 3
4 1
13 10
1 1000
10 8
5 5
-1 1 -1 -1
-1 -1 1 -1
-1 -1 -1 10
-1 -1 -1 -1
1 4
*/
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>
using namespace std;
#define sp ' '
#define endl '\n'
#define fi first
#define se second
#define mp make_pair
#define int long long
#define N 105
const int INF = 1e18;
int n, q;
pair<int, int> a[N];
vector < vector<pair<int, int> > > e(N);
int d2[N][N];
double dis[N];

void solve(int l, int r) {
	priority_queue<pair<double, int> , vector<pair<double, int> >, greater<pair<double, int> > > pq;
	fill(dis, dis + N, 1e15);
	dis[l] = 0.0;
	pq.push(mp(0, l));
	while (!pq.empty()) {
		int u = pq.top().se; pq.pop();
		for (int i = 1; i <= n; i++) {
			if (i == u || d2[u][i] == INF) continue;
			if (d2[u][i] <= a[u].fi && dis[i] > dis[u] + (d2[u][i] * 1.0) / (a[u].se * 1.0)) {
				dis[i] = dis[u] + (d2[u][i] * 1.0) / (a[u].se * 1.0);
				pq.push(mp(dis[i], i));
			}
		}
	}
	cout << setprecision(10) << fixed << dis[r] << endl;
}

void dijkstra(int wh , int sta) {
	priority_queue<pair<int, int> , vector<pair<int, int> >, greater<pair<int, int> > > pq;
	for (int i = 0; i <= n; i++) d2[wh][i] = INF;
	d2[wh][sta] = 0; pq.push(mp(0, sta));
	while (!pq.empty()) {
		int u = pq.top().se; pq.pop();
		for (int j = 0; j < e[u].size(); j++) {
			int v = e[u][j].fi; int w = e[u][j].se;
			if (d2[wh][v] > d2[wh][u] + w) {
				d2[wh][v] = d2[wh][u] + w;
				pq.push(mp(d2[wh][v], v));
			}
		}
	}
}

signed main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
#ifdef UncleGrandpa
	freopen("1test.inp", "r", stdin);
	freopen("1test.out", "w", stdout);
#endif
	int T; cin >> T; int ct = 0;
	while (T--) {
		ct++;
		e.assign(N, vector<pair<int, int> >());
		cin >> n >> q;
		for (int i = 1; i <= n; i++) {
			cin >> a[i].fi >> a[i].se;
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				int t; cin >> t;
				if (t != -1) e[i].push_back(mp(j, t));
			}
		}
		for (int i = 1; i <= n; i++) {
			dijkstra(i, i);
		}
		while (q--) {
			int u, v; cin >> u >> v;
			cout << "Case #" << ct << ": ";
			solve(u, v);
		}
	}

}
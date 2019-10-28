#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<string>
#include<iomanip>
#include<vector>
#include<map>
#include<set>
#include<queue>

using namespace std;

const int N = 110;

int e[N], s[N];
int n;
int dt[N];
int sum[N];

struct node
{
	int v;
	double w;
	node(int _v = 0, double _w = 0) : v(_v), w(_w) {
	}
};

vector <node> adj[N];
bool vst[N];
double d[N];

void work()
{
	int qq;
	cin >> n >> qq;
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", &e[i], &s[i]);
	}
	sum[1] = 0;
	for (int u, i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			scanf("%d", &u);
			if (i + 1 == j) {
				dt[i + 1] = u;
				sum[i + 1] = sum[i] + dt[i + 1];
			}
		}
	}
	cin >> qq >> qq;
	for (int i = 1; i <= n; ++i) {
		adj[i].clear();
	}
	for (int i = 1; i < n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			if (sum[j] - sum[i] <= e[i]) {
				adj[i].push_back(node(j, (double)(sum[j] - sum[i]) / s[i]));
			}
			else {
				break;
			}
		}
	}
	queue <int> q;
	q.push(1);
	vst[1] = true;
	fill(d + 1, d + n + 1, 1e20);
	d[1] = 0;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		vst[u] = false;
		for (int i = 0; i < (int)adj[u].size(); ++i) {
			int v = adj[u][i].v;
			double w = adj[u][i].w;
			if (d[v] > d[u] + w) {
				d[v] = d[u] + w;
				if (!vst[v]) {
					q.push(v);
					vst[v] = true;
				}
			}
		}
	}
	cout << fixed << setprecision(9) << d[n] << endl;
}

int main()
{
	freopen("my.in", "r", stdin);
	freopen("out.txt", "w", stdout);

	int q;
	cin >> q;
	for (int i = 1; i <= q; ++i) {
		printf("Case #%d: ", i);
		work();
	}
	return 0;
}

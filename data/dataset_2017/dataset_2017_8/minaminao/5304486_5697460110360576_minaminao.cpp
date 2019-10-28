#include "bits/stdc++.h"
using namespace std;
#ifdef _DEBUG
#include "dump.hpp"
#else
#define dump(...)
#endif

#define int long long
#define rep(i,a,b) for(int i=(a);i<(b);i++)
#define rrep(i,a,b) for(int i=(b)-1;i>=(a);i--)
#define all(c) begin(c),end(c)
const int INF = sizeof(int) == sizeof(long long) ? 0x3f3f3f3f3f3f3f3fLL : 0x3f3f3f3f;
const int MOD = (int)(1e9) + 7;
template<class T> bool chmax(T &a, const T &b) { if (a < b) { a = b; return true; } return false; }
template<class T> bool chmin(T &a, const T &b) { if (b < a) { a = b; return true; } return false; }

using Weight = int;
using Flow = int;
struct Edge {
	int s, d; Weight w; Flow c;
	Edge() {};
	Edge(int s, int d, Weight w = 1) : s(s), d(d), w(w), c(w) {};
};
bool operator<(const Edge &e1, const Edge &e2) { return e1.w < e2.w; }
bool operator>(const Edge &e1, const Edge &e2) { return e2 < e1; }
inline ostream &operator<<(ostream &os, const Edge &e) { return (os << '(' << e.s << ", " << e.d << ", " << e.w << ')'); }

using Edges = vector<Edge>;
using Graph = vector<Edges>;
using Array = vector<Weight>;
using Matrix = vector<Array>;

void add_arc(Graph &g, int s, int d, Weight w = 1) {
	g[s].emplace_back(s, d, w);
}
void add_edge(Graph &g, int a, int b, Weight w = 1) {
	add_arc(g, a, b, w);
	add_arc(g, b, a, w);
}

struct Dinic {
	int n, s, t;
	vector<int> level, prog, que;
	vector<vector<Flow>> cap, flow;
	vector<vector<int>> g;
	Flow inf;
	Dinic(const Graph &graph)
		: n(graph.size()),
		cap(n, vector<Flow>(n)),
		flow(n, vector<Flow>(n)),
		g(n, vector<int>()),
		inf(numeric_limits<Flow>::max() / 8) {
		for (int i = 0; i < n; i++) {
			for (auto &e : graph[i]) {
				int u = e.s, v = e.d;
				Flow c = e.c;
				cap[u][v] += c;
				cap[v][u] += c;
				flow[v][u] += c;
				g[u].push_back(v);
				g[v].push_back(u);
			}
		}
	}
	inline Flow residue(int u, int v) { return cap[u][v] - flow[u][v]; }
	Flow solve(int s_, int t_) {
		this->t = t_, this->s = s_;
		que.resize(n + 1);
		Flow res = 0;
		while (levelize()) {
			prog.assign(n, 0);
			res += augment(s, inf);
		}
		return res;
	}
	bool levelize() {
		int l = 0, r = 0;
		level.assign(n, -1);
		level[s] = 0;
		que[r++] = s;
		while (l != r) {
			int v = que[l++];
			if (v == t) break;
			for (const int &d : g[v])
				if (level[d] == -1 && residue(v, d) != 0) {
					level[d] = level[v] + 1;
					que[r++] = d;
				}
		}
		return level[t] != -1;
	}
	Flow augment(int v, Flow lim) {
		Flow res = 0;
		if (v == t) return lim;
		for (int &i = prog[v]; i < (int)g[v].size(); i++) {
			const int &d = g[v][i];
			if (residue(v, d) == 0 || level[v] >= level[d]) continue;
			const Flow aug = augment(d, min(lim, residue(v, d)));
			flow[v][d] += aug;
			flow[d][v] -= aug;
			res += aug;
			lim -= aug;
			if (lim == 0) break;
		}
		return res;
	}
};

signed main() {
	cin.tie(0);
	ios::sync_with_stdio(false);
	freopen("B-small-attempt0.in", "r", stdin);
	freopen("B-small-attempt0.txt", "w", stdout);
	//freopen("in.txt", "r", stdin);
	////freopen("out.txt", "w", stdout);
	int T; cin >> T;
	for (int t = 0; t < T; t++) {
		int N, P; cin >> N >> P;
		vector<int> R(N); rep(i, 0, N) {
			cin >> R[i];
		}
		vector<vector<int>> Q(N, vector<int>(P));
		rep(i, 0, N) rep(j, 0, P) { cin >> Q[i][j]; }


		if (N == 1) {
			int ans = 0;
			rep(i, 0, P) {
				int a = ceil(Q[0][i] * 100 / 110.0 / R[0]);
				int b = Q[0][i] * 100 / 90.0 / R[0];
				if (a <= b)ans++;
			}
			cout << "Case #" << t + 1 << ": " << ans << endl;
			continue;
		}

		sort(all(Q[0]));
		sort(all(Q[1]));
		dump(R);
		int ans = 0;
		do {
			int cnt = 0;
			rep(i, 0, P) {
				int a = ceil(Q[0][i] * 100 / 110.0 / R[0]);
				int b = Q[0][i] * 100 / 90.0 / R[0];
				int c = ceil(Q[1][i] * 100 / 110.0 / R[1]);
				int d = Q[1][i] * 100 / 90.0 / R[1];
				//dump(a, b, c, d);
				if (a <= d&&c <= b)cnt++;
			}
			chmax(ans, cnt);
		} while (next_permutation(all(Q[1])));

		cout << "Case #" << t + 1 << ": " << ans << endl;
	}
	return 0;
}
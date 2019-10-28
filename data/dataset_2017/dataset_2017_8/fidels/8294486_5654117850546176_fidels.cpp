#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#define START_R 0
#define END_R R
#define START_O R
#define END_O R+O
#define START_Y R+O
#define END_Y R+O+Y
#define START_G R+O+Y
#define END_G R+O+Y+G
#define START_B R+O+Y+G
#define END_B R+O+Y+G+B
#define START_V R+O+Y+G+B
#define END_V R+O+Y+G+B+V

#define MAXN 2048
#define MAXE 2097152
#define INF 1000000000

#define OTHER(x, y) ( e[(x)].a == y ? e[(x)].b : e[(x)].a )
#define RESIDUAL(x, y) ( (y) == e[(x)].a ? e[(x)].cd-e[(x)].f : e[(x)].cr+e[(x)].f )

struct node {
	vector<int> c;
    int point;
} n[MAXN];

struct edge {
	int a, b, cd, cr, f;
} e[MAXE];

int EDGES;

void init(int N) {
	for (int i=0; i<N; i++) n[i].c.clear();
	EDGES = 0;
}

void add_edge(int a, int b, int cd, int cr) {
	e[EDGES].a = a; e[EDGES].b = b;
	e[EDGES].cd = cd; e[EDGES].cr = cr;
	n[e[EDGES].a].c.push_back(EDGES);
	n[e[EDGES].b].c.push_back(EDGES);
	EDGES++;
}

bool bfs(int *r, int N, int SOURCE, int SINK) {
	int i, S, E, s[MAXN], cur, next, cure;

	for (i=0; i<N; i++) {r[i] = -1; n[i].point = 0;} r[SOURCE] = 0;
	S = E = 0; s[E++] = SOURCE;
	while (S < E) {
		cur = s[S++];
		for (i=0; i<(int)n[cur].c.size(); i++) {
			cure = n[cur].c[i];
			next = OTHER(cure, cur);
			if (r[next] == -1 && RESIDUAL(cure, cur) > 0) {
				s[E++] = next;
				r[next] = r[cur]+1;
			}
		}
	}
	return r[SINK] != -1;
}

int dfs(int *r, int SOURCE, int SINK, int cur, int flowcap) {
	if (cur == SINK) return flowcap;

	int curflow = 0;
	for (; curflow<flowcap && n[cur].point<(int)n[cur].c.size(); n[cur].point++) {
		int cure = n[cur].c[n[cur].point];
		int next = OTHER(cure, cur);

		if (r[next] == r[cur]+1 && RESIDUAL(cure, cur) > 0) {
			int tmp = dfs(r, SOURCE, SINK, next, min(flowcap-curflow, RESIDUAL(cure, cur)));
			curflow += tmp;
			if (cur == e[cure].a) e[cure].f += tmp;
			else e[cure].f -= tmp;
		}
	}
	return curflow;
}

int dinic(int N, int SOURCE, int SINK) {
	int r[MAXN];
	for (int i=0; i<EDGES; i++) e[i].f = 0;

	int FLOW = 0;
	while (bfs(r, N, SOURCE, SINK)) FLOW += dfs(r, SOURCE, SINK, SOURCE, INF);
	return FLOW;
}

int R, O, Y, G, B, V, sig[MAXN];
bool v[MAXN];
char last;

char color(int id) {
	if (START_R <= id && id < END_R) return 'R';
	if (START_O <= id && id < END_O) return 'O';
	if (START_Y <= id && id < END_Y) return 'Y';
	if (START_G <= id && id < END_G) return 'G';
	if (START_B <= id && id < END_B) return 'B';
	if (START_V <= id && id < END_V) return 'V';
}

void print(int cur) {
	do {
		cout << color(cur);
		v[cur] = true; last = color(cur);
		cur = sig[cur];
	} while (!v[cur]);
}

int main() {
	int T, t, N, i, j, SOURCE, SINK;
	
	cin >> T;
	for (t=1; t<=T; t++) {
		cin >> N >> R >> O >> Y >> G >> B >> V;
		
		init(2*N+2);
		SOURCE = 2*N; SINK = 2*N+1;
		for (i=0; i<N; i++) add_edge(SOURCE, i, 1, 0);
		for (i=N; i<2*N; i++) add_edge(i, SINK, 1, 0);
		for (i=START_R; i<END_R; i++) for (j=START_Y; j<END_Y; j++) add_edge(i, N+j, 1, 0);
		for (i=START_R; i<END_R; i++) for (j=START_B; j<END_B; j++) add_edge(i, N+j, 1, 0);
		for (i=START_R; i<END_R; i++) for (j=START_G; j<END_G; j++) add_edge(i, N+j, 1, 0);
		for (i=START_B; i<END_B; i++) for (j=START_Y; j<END_Y; j++) add_edge(i, N+j, 1, 0);
		for (i=START_B; i<END_B; i++) for (j=START_R; j<END_R; j++) add_edge(i, N+j, 1, 0);
		for (i=START_B; i<END_B; i++) for (j=START_O; j<END_O; j++) add_edge(i, N+j, 1, 0);
		for (i=START_Y; i<END_Y; i++) for (j=START_R; j<END_R; j++) add_edge(i, N+j, 1, 0);
		for (i=START_Y; i<END_Y; i++) for (j=START_B; j<END_B; j++) add_edge(i, N+j, 1, 0);
		for (i=START_Y; i<END_Y; i++) for (j=START_V; j<END_V; j++) add_edge(i, N+j, 1, 0);
		for (i=START_O; i<END_O; i++) for (j=START_B; j<END_B; j++) add_edge(i, N+j, 1, 0);
		for (i=START_G; i<END_G; i++) for (j=START_R; j<END_R; j++) add_edge(i, N+j, 1, 0);
		for (i=START_V; i<END_V; i++) for (j=START_Y; j<END_Y; j++) add_edge(i, N+j, 1, 0);
		
		cout << "Case #" << t << ": ";
		if (dinic(2*N+2, SOURCE, SINK) == N) {
			for (i=0; i<EDGES; i++) if (e[i].a < N && e[i].f == 1) sig[e[i].a] = e[i].b-N;
			
			memset(v, false, sizeof(v));
			for (i=START_B; i<END_B; i++) if (!v[i]) print(i);
			if (last == 'Y') {
				for (i=START_R; i<END_R; i++) if (!v[i]) print(i);
				for (i=START_V; i<END_V; i++) if (!v[i]) print(i);
			} else {
				for (i=START_Y; i<END_Y; i++) if (!v[i]) print(i);
				for (i=START_G; i<END_G; i++) if (!v[i]) print(i);
			}
			cout << endl;
		} else cout << "IMPOSSIBLE" << endl;
	}

	return 0;
}

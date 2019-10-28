#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
struct node {
  vector<int> c;
  int point;
} n[2048];

struct edge {
  int a, b, cd, cr, f;
} e[2097152];

int EDGES;

void init(int N) {
  for (int i = 0; i < N; i++)
    n[i].c.clear();
  EDGES = 0;
}

void add_edge(int a, int b, int cd, int cr) {
  e[EDGES].a = a;
  e[EDGES].b = b;
  e[EDGES].cd = cd;
  e[EDGES].cr = cr;
  n[e[EDGES].a].c.push_back(EDGES);
  n[e[EDGES].b].c.push_back(EDGES);
  EDGES++;
}

bool bfs(int *r, int N, int SOURCE, int SINK) {
  int i, S, E, s[2048], cur, next, cure;

  for (i = 0; i < N; i++) {
    r[i] = -1;
    n[i].point = 0;
  }
  r[SOURCE] = 0;
  S = E = 0;
  s[E++] = SOURCE;
  while (S < E) {
    cur = s[S++];
    for (i = 0; i < (int)n[cur].c.size(); i++) {
      cure = n[cur].c[i];
      next = (e[(cure)].a == cur ? e[(cure)].b : e[(cure)].a);
      if (r[next] == -1 &&
          ((cur) == e[(cure)].a ? e[(cure)].cd - e[(cure)].f
                                : e[(cure)].cr + e[(cure)].f) > 0) {
        s[E++] = next;
        r[next] = r[cur] + 1;
      }
    }
  }
  return r[SINK] != -1;
}

int dfs(int *r, int SOURCE, int SINK, int cur, int flowcap) {
  if (cur == SINK)
    return flowcap;

  int curflow = 0;
  for (; curflow < flowcap && n[cur].point < (int)n[cur].c.size();
       n[cur].point++) {
    int cure = n[cur].c[n[cur].point];
    int next = (e[(cure)].a == cur ? e[(cure)].b : e[(cure)].a);

    if (r[next] == r[cur] + 1 &&
        ((cur) == e[(cure)].a ? e[(cure)].cd - e[(cure)].f
                              : e[(cure)].cr + e[(cure)].f) > 0) {
      int tmp = dfs(r, SOURCE, SINK, next,
                    min(flowcap - curflow,
                        ((cur) == e[(cure)].a ? e[(cure)].cd - e[(cure)].f
                                              : e[(cure)].cr + e[(cure)].f)));
      curflow += tmp;
      if (cur == e[cure].a)
        e[cure].f += tmp;
      else
        e[cure].f -= tmp;
    }
  }
  return curflow;
}

int dinic(int N, int SOURCE, int SINK) {
  int r[2048];
  for (int i = 0; i < EDGES; i++)
    e[i].f = 0;

  int FLOW = 0;
  while (bfs(r, N, SOURCE, SINK))
    FLOW += dfs(r, SOURCE, SINK, SOURCE, 1000000000);
  return FLOW;
}

int R, O, Y, G, B, V, sig[2048];
bool v[2048];
char last;

char color(int id) {
  if (0 <= id && id < R)
    return 'R';
  if (R <= id && id < R + O)
    return 'O';
  if (R + O <= id && id < R + O + Y)
    return 'Y';
  if (R + O + Y <= id && id < R + O + Y + G)
    return 'G';
  if (R + O + Y + G <= id && id < R + O + Y + G + B)
    return 'B';
  if (R + O + Y + G + B <= id && id < R + O + Y + G + B + V)
    return 'V';
}

void print(int cur) {
  do {
    cout << color(cur);
    v[cur] = true;
    last = color(cur);
    cur = sig[cur];
  } while (!v[cur]);
}

int main() {
  int T, t, N, i, j, SOURCE, SINK;

  cin >> T;
  for (t = 1; t <= T; t++) {
    cin >> N >> R >> O >> Y >> G >> B >> V;

    init(2 * N + 2);
    SOURCE = 2 * N;
    SINK = 2 * N + 1;
    for (i = 0; i < N; i++)
      add_edge(SOURCE, i, 1, 0);
    for (i = N; i < 2 * N; i++)
      add_edge(i, SINK, 1, 0);
    for (i = 0; i < R; i++)
      for (j = R + O; j < R + O + Y; j++)
        add_edge(i, N + j, 1, 0);
    for (i = 0; i < R; i++)
      for (j = R + O + Y + G; j < R + O + Y + G + B; j++)
        add_edge(i, N + j, 1, 0);
    for (i = 0; i < R; i++)
      for (j = R + O + Y; j < R + O + Y + G; j++)
        add_edge(i, N + j, 1, 0);
    for (i = R + O + Y + G; i < R + O + Y + G + B; i++)
      for (j = R + O; j < R + O + Y; j++)
        add_edge(i, N + j, 1, 0);
    for (i = R + O + Y + G; i < R + O + Y + G + B; i++)
      for (j = 0; j < R; j++)
        add_edge(i, N + j, 1, 0);
    for (i = R + O + Y + G; i < R + O + Y + G + B; i++)
      for (j = R; j < R + O; j++)
        add_edge(i, N + j, 1, 0);
    for (i = R + O; i < R + O + Y; i++)
      for (j = 0; j < R; j++)
        add_edge(i, N + j, 1, 0);
    for (i = R + O; i < R + O + Y; i++)
      for (j = R + O + Y + G; j < R + O + Y + G + B; j++)
        add_edge(i, N + j, 1, 0);
    for (i = R + O; i < R + O + Y; i++)
      for (j = R + O + Y + G + B; j < R + O + Y + G + B + V; j++)
        add_edge(i, N + j, 1, 0);
    for (i = R; i < R + O; i++)
      for (j = R + O + Y + G; j < R + O + Y + G + B; j++)
        add_edge(i, N + j, 1, 0);
    for (i = R + O + Y; i < R + O + Y + G; i++)
      for (j = 0; j < R; j++)
        add_edge(i, N + j, 1, 0);
    for (i = R + O + Y + G + B; i < R + O + Y + G + B + V; i++)
      for (j = R + O; j < R + O + Y; j++)
        add_edge(i, N + j, 1, 0);

    cout << "Case #" << t << ": ";
    if (dinic(2 * N + 2, SOURCE, SINK) == N) {
      for (i = 0; i < EDGES; i++)
        if (e[i].a < N && e[i].f == 1)
          sig[e[i].a] = e[i].b - N;

      memset(v, false, sizeof(v));
      for (i = R + O + Y + G; i < R + O + Y + G + B; i++)
        if (!v[i])
          print(i);
      if (last == 'Y') {
        for (i = 0; i < R; i++)
          if (!v[i])
            print(i);
        for (i = R + O + Y + G + B; i < R + O + Y + G + B + V; i++)
          if (!v[i])
            print(i);
      } else {
        for (i = R + O; i < R + O + Y; i++)
          if (!v[i])
            print(i);
        for (i = R + O + Y; i < R + O + Y + G; i++)
          if (!v[i])
            print(i);
      }
      cout << endl;
    } else
      cout << "IMPOSSIBLE" << endl;
  }

  return 0;
}

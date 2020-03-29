#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct BipartiteMatching {
  int V;
  vector<vector<bool>> G;
  vector<int> match;
  vector<bool> used;

  BipartiteMatching(int v) {
    V = v;
    G = vector<vector<bool>>(v, vector<bool>(v));
    match = vector<int>(v);
    used = vector<bool>(v);
  }

  void add_edge(int v, int u) { G[v][u] = G[u][v] = true; }

  bool dfs(int v) {
    used[v] = true;
    for (int i = 0; i < V; i++) {
      if (!G[v][i])
        continue;
      int u = i, w = match[u];
      if (w < 0 || (!used[w] && dfs(w))) {
        match[v] = u;
        match[u] = v;
        return true;
      }
    }
    return false;
  }

  int calc() {
    int res = 0;
    fill(match.begin(), match.end(), -1);
    for (int v = 0; v < V; v++) {
      if (match[v] < 0) {
        fill(used.begin(), used.end(), false);
        if (dfs(v)) {
          res++;
        }
      }
    }
    return res;
  }
};

int P[1000];
int B[1000];

void solve() {
  int N, C, M;
  cin >> N >> C >> M;

  BipartiteMatching bp(M);
  for (int i = 0; i < M; i++) {
    cin >> P[i] >> B[i];
    P[i]--, B[i]--;
  }

  if (C != 2)
    return;

  for (int i = 0; i < M; i++) {
    for (int j = i + 1; j < M; j++) {
      if (P[i] == P[j] || B[i] == B[j])
        continue;
      bp.add_edge(i, j);
    }
  }

  bp.calc();

  set<int> s;
  int cnt[2] = {0, 0};
  for (int i = 0; i < M; i++) {
    if (bp.match[i] != -1)
      continue;
    s.insert(P[i]);
    cnt[B[i]]++;
  }

  if (s.size() == 0) {
    cout << 0 << endl;
    return;
  }

  if (s.size() != 1 || *s.begin() == 0) {
    cout << 0 << endl;
  } else {
    cout << min(cnt[0], cnt[1]) << endl;
  }
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  int T;
  cin >> T;
  for (int i = 0; i < T; i++) {
    cerr << i << endl;
    cout << "Case #" << i + 1 << ": ";
    solve();
  }
}
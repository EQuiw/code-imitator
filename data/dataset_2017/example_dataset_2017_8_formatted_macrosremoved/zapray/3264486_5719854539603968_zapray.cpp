
#include <algorithm>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
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
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;

using namespace std;

char B[105][105];

// A class to represent Bipartite graph for Hopcroft
// Karp implementation
// http://www.geeksforgeeks.org/hopcroft-karp-algorithm-for-maximum-matching-set-2-implementation/
class BipGraph {
public:
  // m and n are number of vertices on left
  // and right sides of Bipartite Graph
  int m, n;
  // adj[u] stores adjacents of left side
  // vertex 'u'. The value of u ranges from 1 to m.
  // 0 is used for dummy vertex
  vector<list<int>> adj;
  // These are basically arrays needed
  // for hopcroftKarp()
  vector<int> pairU, pairV, dist;

  BipGraph(int m, int n);     // Constructor
  void addEdge(int u, int v); // To add edge

  // Returns true if there is an augmenting path
  bool bfs();

  // Adds augmenting path if there is one beginning
  // with u
  bool dfs(int u);

  // Returns size of maximum matcing
  int hopcroftKarp();
};

// Returns size of maximum matching
int BipGraph::hopcroftKarp() {
  // pairU[u] stores pair of u in matching where u
  // is a vertex on left side of Bipartite Graph.
  // If u doesn't have any pair, then pairU[u] is NIL
  pairU = vector<int>(m + 1);

  // pairV[v] stores pair of v in matching. If v
  // doesn't have any pair, then pairU[v] is NIL
  pairV = vector<int>(n + 1);

  // dist[u] stores distance of left side vertices
  // dist[u] is one more than dist[u'] if u is next
  // to u'in augmenting path
  dist = pairU = vector<int>(m + 1);

  // Initialize NIL as pair of all vertices
  for (int u = 0; u < m; u++)
    pairU[u] = 0;
  for (int v = 0; v < n; v++)
    pairV[v] = 0;

  // Initialize result
  int result = 0;

  // Keep updating the result while there is an
  // augmenting path.
  while (bfs()) {
    // Find a free vertex
    for (int u = 1; u <= m; u++)

      // If current vertex is free and there is
      // an augmenting path from current vertex
      if (pairU[u] == 0 && dfs(u))
        result++;
  }
  return result;
}

// Returns true if there is an augmenting path, else returns
// false
bool BipGraph::bfs() {
  queue<int> Q; // an integer queue

  // First layer of vertices (set distance as 0)
  for (int u = 1; u <= m; u++) {
    // If this is a free vertex, add it to queue
    if (pairU[u] == 0) {
      // u is not matched
      dist[u] = 0;
      Q.push(u);
    }

    // Else set distance as infinite so that this vertex
    // is considered next time
    else
      dist[u] = INT_MAX;
  }

  // Initialize distance to NIL as infinite
  dist[0] = INT_MAX;

  // Q is going to contain vertices of left side only.
  while (!Q.empty()) {
    // Dequeue a vertex
    int u = Q.front();
    Q.pop();

    // If this node is not NIL and can provide a shorter path to NIL
    if (dist[u] < dist[0]) {
      // Get all adjacent vertices of the dequeued vertex u
      list<int>::iterator i;
      for (i = adj[u].begin(); i != adj[u].end(); ++i) {
        int v = *i;

        // If pair of v is not considered so far
        // (v, pairV[V]) is not yet explored edge.
        if (dist[pairV[v]] == INT_MAX) {
          // Consider the pair and add it to queue
          dist[pairV[v]] = dist[u] + 1;
          Q.push(pairV[v]);
        }
      }
    }
  }

  // If we could come back to NIL using alternating path of distinct
  // vertices then there is an augmenting path
  return (dist[0] != INT_MAX);
}

// Returns true if there is an augmenting path beginning with free vertex u
bool BipGraph::dfs(int u) {
  if (u != 0) {
    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i) {
      // Adjacent to u
      int v = *i;

      // Follow the distances set by BFS
      if (dist[pairV[v]] == dist[u] + 1) {
        // If dfs for pair of v also returns
        // true
        if (dfs(pairV[v]) == true) {
          pairV[v] = u;
          pairU[u] = v;
          return true;
        }
      }
    }

    // If there is no augmenting path beginning with u.
    dist[u] = INT_MAX;
    return false;
  }
  return true;
}

// Constructor
BipGraph::BipGraph(int m, int n) {
  this->m = m;
  this->n = n;
  adj.clear();
  adj.resize(m + 1);
}

// To add edge from u to v and v to u
void BipGraph::addEdge(int u, int v) {
  adj[u].push_back(v); // Add u to v¡¯s list.
}

void output(int n) {
  int score = 0, changed = 0;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) {
      if (B[i][j] == '+' || B[i][j] == 'T')
        score += 1;
      if (B[i][j] == 'x' || B[i][j] == 'X')
        score += 1;
      if (B[i][j] == 'o' || B[i][j] == 'O')
        score += 2;

      if (B[i][j] == 'T' || B[i][j] == 'X' || B[i][j] == 'O')
        changed += 1;
    }
  printf("%d %d\n", score, changed);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) {
      if (B[i][j] == 'T')
        printf("+ ");
      else if (B[i][j] == 'X')
        printf("x ");
      else if (B[i][j] == 'O')
        printf("o ");
      else
        continue;
      printf("%d %d\n", i, j);
    }
}

int main() {
  int T;
  cin >> T;
  for (int cs = 1; cs <= T; cs++) {
    printf("Case #%d: ", cs);
    int n, m;
    cin >> n >> m;
    memset(B, 0, sizeof(B));
    while (m--) {
      char c;
      int x, y;
      cin >> c >> x >> y;
      B[x][y] = c;
    }
    // first add +
    BipGraph g1(2 * n, 2 * n);
    vector<int> killedu(2 * n + 1);
    vector<int> killedv(2 * n + 1);
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++) {
        int u = i + j;
        int v = i - j + n;
        if (B[i][j] == '+' || B[i][j] == 'o') {
          killedu[u] = 1;
          killedv[v] = 1;
        }
      }

    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++) {
        int u = i + j;
        int v = i - j + n;
        if (B[i][j] == 0 && !(killedu[u] || killedv[v]))
          g1.addEdge(i + j, i - j + n);
      }
    int addT = g1.hopcroftKarp();
    for (int u = 1; u <= 2 * n; u++) {
      int v = g1.pairU[u];
      if (v == 0)
        continue;
      int i = (u + v - n) / 2;
      int j = (u - v + n) / 2;
      B[i][j] = 'T';
    }

    // second add x
    BipGraph g2(n, n);
    vector<int> killedi(n + 1);
    vector<int> killedj(n + 1);
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++) {
        if (B[i][j] == 'x' || B[i][j] == 'o') {
          killedi[i] = 1;
          killedj[j] = 1;
        }
      }

    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++) {
        if (B[i][j] == 0 && !(killedi[i] || killedj[j]))
          g2.addEdge(i, j);
      }
    int addX = g2.hopcroftKarp();
    for (int i = 1; i <= n; i++) {
      int j = g2.pairU[i];
      if (j == 0)
        continue;
      B[i][j] = 'X';
    }

    // third replace o

    set<pair<int, int>> candidates;

    do {
      if (candidates.size()) {
        int i = candidates.begin()->first;
        int j = candidates.begin()->second;
        B[i][j] = 'O';
      }
      candidates.clear();

      killedu = vector<int>(2 * n + 1);
      killedv = vector<int>(2 * n + 1);
      killedi = vector<int>(n + 1);
      killedj = vector<int>(n + 1);
      for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
          int u = i + j;
          int v = i - j + n;
          if (B[i][j] == 'x' || B[i][j] == 'X' || B[i][j] == 'o' ||
              B[i][j] == 'O') {
            killedi[i] += 1;
            killedj[j] += 1;
          }
          if (B[i][j] == '+' || B[i][j] == 'T' || B[i][j] == 'o' ||
              B[i][j] == 'O') {
            killedu[u] += 1;
            killedv[v] += 1;
          }
        }

      for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
          int u = i + j;
          int v = i - j + n;
          if (B[i][j] == 0) {
            if (killedi[i] == 0 && killedj[j] == 0 && killedu[u] == 0 &&
                killedv[v] == 0)
              candidates.emplace(i, j);
          } else if (((B[i][j] == 'x' || B[i][j] == 'X') &&
                      (killedu[u] == 0 && killedv[v] == 0)) ||
                     ((B[i][j] == '+' || B[i][j] == 'T') &&
                      (killedi[i] == 0 && killedj[j] == 0))) {
            candidates.emplace(i, j);
          }
        }
    } while (candidates.size());

    /*cout << "candidates: " << candidates.size() << endl;
    for (auto& pr : candidates) {
            printf("(%d, %d), ", pr.first, pr.second);
    }
    puts("");
    */
    output(n);
  }
  return 0;
}

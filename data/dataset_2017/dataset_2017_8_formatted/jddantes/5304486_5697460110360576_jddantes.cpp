#include <bits/stdc++.h>

using namespace std;

int N, P;

int input[52][52];
int input_req[52];

#define INF (1 << 29)
typedef pair<int, int> pi;
typedef pair<pi, pi> ppi;

// Applicable for middle nodes
pi toPi(int node) {
  int i = (node - 1) / P;
  int j = (node - 1) % P;
  return pi(i + 1, j + 1);
}

vector<vector<set<int>>> input_can;

int res[52][52];
vector<vector<int>> adjList;
vector<vector<int>> incList;

bool vis[52 * 52];
int pred[52 * 52];

int main() {
  int cases;

  scanf("%d", &cases);

  for (int e = 0; e < cases; e++) {
    scanf("%d %d", &N, &P);
    input_can.assign(N * P + 2, vector<set<int>>(N * P + 2));

    for (int i = 1; i <= N; i++) {
      scanf("%d", &input_req[i]);
    }

    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= P; j++) {
        scanf("%d", &input[i][j]);

        int inp = input[i][j];
        int lo = ceil((double)inp / 1.1);
        int hi = floor((double)inp / 0.9);

        for (int s = lo; s <= hi; s++) {
          if (s % input_req[i] == 0) {
            input_can[i][j].insert(s / input_req[i]);
            // printf("Can make %d servings with %d grams\n", s/input_req[i],
            // input[i][j]);
          }
        }
      }
    }

    // Build graph
    memset(res, 0, sizeof res);
    adjList.assign(N * P + 2, vector<int>());
    incList.assign(N * P + 2, vector<int>());

    for (int i = 1; i < N; i++) {
      for (int j = 1; j <= P; j++) {
        int node = (i - 1) * P + j;
        for (int k = 1; k <= P; k++) {
          int adjNode = (i)*P + k;
          for (auto can : input_can[i][j]) {
            if (input_can[i + 1][k].count(can)) {
              adjList[node].push_back(adjNode);
              incList[adjNode].push_back(node);
              res[node][adjNode] = 1;
            }
          }
        }
      }
    }

    for (int j = 1; j <= P; j++) {
      if (input_can[1][j].size()) {
        int node = j;
        adjList[0].push_back(node);
        incList[node].push_back(0);
        res[0][node] = 1;
      }
    }
    for (int j = 1; j <= P; j++) {
      int node = (N - 1) * P + j;
      adjList[node].push_back(N * P + 1);
      incList[N * P + 1].push_back(node);
      res[node][N * P + 1] = 1;
    }

    // DEBUG: Print graph
    // for(int i = 0; i<=N*P+1; i++){
    //     printf("%d: ", i);
    //     for(auto adj : adjList[i]){
    //         printf("%d ", adj);
    //     }
    //     printf("\n");
    // }

    int cnt = 0;
    while (1) {
      bool found = false;

      queue<pi> que;
      memset(vis, 0, sizeof vis);
      que.push(pi(0, -1));

      while (!que.empty()) {
        pi p = que.front();
        que.pop();

        int node = p.first;
        int pre = p.second;

        if (vis[node]) {
          continue;
        }
        vis[node] = true;
        pred[node] = pre;

        if (node == N * P + 1) {
          found = true;
          break;
        }

        for (auto adj : adjList[node]) {
          if (vis[adj])
            continue;
          if (res[node][adj]) {
            que.push(pi(adj, node));
          }
        }
        for (auto adj : incList[node]) {
          if (vis[adj])
            continue;
          if (res[node][adj]) {
            que.push(pi(adj, node));
          }
        }
      }

      if (!found) {
        break;
      } else {
        // Edit res
        int cur = N * P + 1;

        while (1) {
          int pre = pred[cur];
          res[pre][cur] -= 1;
          res[cur][pre] += 1;

          if (pre == 0)
            break;

          cur = pre;
        }

        cnt++;
      }
    }

    printf("Case #%d: %d\n", e + 1, cnt);
  }

  return 0;
}
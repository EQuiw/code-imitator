#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> hopcroftCarp(const vector<vector<int>> &adjU,
                                    const vector<vector<int>> &adjV) {
  int N = adjU.size();
  int M = adjV.size();
  vector<int> pairU(N, -1);
  vector<int> pairV(M, -1);
  while (true) {
    vector<int> layerU(N, -1);
    vector<int> layerV(M, -1);
    queue<int> Q;
    queue<int> freeV;
    int maxLayer = M + N;
    for (int i = 0; i < N; i++) {
      if (pairU[i] == -1) {
        layerU[i] = 0;
        for (auto it = adjU[i].begin(); it != adjU[i].end(); ++it) {
          if (layerV[*it] < 0) {
            layerV[*it] = 1;
            if (pairV[*it] == -1) {
              freeV.push(*it);
              maxLayer = 1;
            } else if (freeV.empty())
              Q.push(*it);
          }
        }
      }
    }
    while (!Q.empty()) {
      int v = Q.front();
      Q.pop();
      if (layerV[v] < maxLayer) {
        int u = pairV[v];
        layerU[u] = layerV[v] + 1;
        for (auto it = adjU[u].begin(); it != adjU[u].end(); ++it)
          if (*it != v) {
            if (layerV[*it] < 0) {
              layerV[*it] = layerV[v] + 2;
              if (pairV[*it] == -1) {
                freeV.push(*it);
                maxLayer = layerV[v] + 2;
              } else if (freeV.empty())
                Q.push(*it);
            }
          }
      }
    }
    if (freeV.empty())
      break;
    int np = 0;
    while (!freeV.empty()) {
      int v = freeV.front();
      freeV.pop();
      stack<int> S;
      vector<int> path(maxLayer + 1, -1);
      S.push(v);
      while (!S.empty()) {
        int s = S.top();
        S.pop();
        int layer = layerV[s];
        path[layer] = s;
        layerV[s] = -1;
        if (layer != maxLayer) {
          path[layer + 1] = pairV[s];
          layerU[pairV[s]] = -1;
        }
        for (auto it = adjV[s].begin(); it != adjV[s].end(); ++it)
          if (*it != pairV[s] && layerU[*it] == layer - 1) {
            if (layerU[*it] == 0) {
              path[0] = *it;
              layerU[*it] = -1;
              break;
            }
            if (layerV[pairU[*it]] == layer - 2)
              S.push(pairU[*it]);
          }
        if (path[0] >= 0)
          break;
      }
      if (path[0] >= 0) {
        np++;
        for (int i = 0; i < maxLayer; i += 2) {
          pairU[path[i]] = path[i + 1];
          pairV[path[i + 1]] = path[i];
        }
      }
    }
  }
  vector<pair<int, int>> ret;
  for (int i = 0; i < pairU.size(); i++)
    if (pairU[i] >= 0)
      ret.push_back(make_pair(i, pairU[i]));
  return ret;
}

int main() {
  int T;
  cin >> T;
  for (int testCase = 1; testCase <= T; testCase++) {
    cout << "Case #" << testCase << ": ";
    int N, P;
    cin >> N;
    cin >> P;
    vector<int> R(N);
    for (int i = 0; i < N; i++)
      cin >> R[i];
    vector<vector<int>> Q(N, vector<int>(P));
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < P; j++)
        cin >> Q[i][j];
    }
    if (N == 1) {
      int kits = 0;
      for (int i = 0; i < P; i++) {
        for (int size = 1; size <= Q[0][i]; size++) {
          if (Q[0][i] * 10 >= 9 * size * R[0] &&
              Q[0][i] * 10 <= 11 * size * R[0]) {
            kits++;
            break;
          }
        }
      }
      cout << kits;
    }
    if (N == 2) {
      vector<vector<int>> adjU(P);
      vector<vector<int>> adjV(P);
      for (int i = 0; i < P; i++)
        for (int j = 0; j < P; j++) {
          bool can = false;
          for (int size = 1; size <= 10 * Q[0][i]; size++) {
            if (Q[0][i] * 10 >= 9 * size * R[0] &&
                Q[0][i] * 10 <= 11 * size * R[0] &&
                Q[1][j] * 10 >= 9 * size * R[1] &&
                Q[1][j] * 10 <= 11 * size * R[1]) {
              can = true;
              break;
            }
          }
          if (can) {
            adjU[i].push_back(j);
            adjV[j].push_back(i);
          }
        }
      vector<pair<int, int>> matching = hopcroftCarp(adjU, adjV);
      cout << matching.size();
    }
    cout << endl;
  }
  return 0;
}

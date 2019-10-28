#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

vector<vector<int>> dist;
vector<int> cabmaxdist;
vector<int> cabvel;
int n, q;

double mindist(int ini, int fin) {
  vector<vector<bool>> vis(n, vector<bool>(n, false));
  pair<double, pair<int, pair<int, int>>> ppp, ppp2;
  pair<int, int> p1, p2, p3;
  pair<int, pair<int, int>> pp1, pp2, pp3;
  priority_queue<pair<double, pair<int, pair<int, int>>>> pq;
  p1.first = ini;
  p1.second = cabmaxdist[ini];
  pp1.second = p1;
  pp1.first = ini;
  ppp.first = 0;
  ppp.second = pp1;
  pq.push(ppp);
  while (!pq.empty()) {
    ppp = pq.top();
    pq.pop();
    double distancia = -ppp.first;
    int pos = ppp.second.first;
    int caballo = ppp.second.second.first;
    int distcaballor = ppp.second.second.second;
    if (vis[pos][caballo])
      continue;
    vis[pos][caballo] = true;
    if (pos == fin)
      return distancia;
    ppp2.first = -distancia;
    ppp2.second.first = pos;
    ppp2.second.second.first = pos;
    ppp2.second.second.second = cabmaxdist[pos];
    pq.push(ppp2);
    for (int i = 0; i < n; i++) {
      if (dist[pos][i] >= 0 && dist[pos][i] <= distcaballor) {
        ppp2.first =
            -distancia - double(dist[pos][i]) / double(cabvel[caballo]);
        ppp2.second.first = i;
        ppp2.second.second.first = caballo;
        ppp2.second.second.second = distcaballor - dist[pos][i];
        pq.push(ppp2);
      }
    }
  }
  return -1;
}

int main() {
  int T;
  cin >> T;
  for (int I = 1; I <= T; I++) {
    cout << "Case #" << I << ":";
    cin >> n >> q;
    cabmaxdist = vector<int>(n);
    cabvel = vector<int>(n);
    for (int i = 0; i < n; i++)
      cin >> cabmaxdist[i] >> cabvel[i];
    dist = vector<vector<int>>(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++)
        cin >> dist[i][j];
    }
    for (int i = 0; i < q; i++) {
      int ini, fin;
      cin >> ini >> fin;
      ini--;
      fin--;
      printf(" %.6f", mindist(ini, fin));
    }
    cout << endl;
  }
}

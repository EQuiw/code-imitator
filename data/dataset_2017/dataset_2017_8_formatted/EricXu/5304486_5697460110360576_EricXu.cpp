#include <cmath>
#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <set>
#include <stack>
#include <utility>
#include <vector>
using namespace std;

int m, n, tf = 0, source = 1;
int **net, *previous, *flow;
set<int> visited;
int **weights;

const int MAXINT = 0x7fffffff;

class mypair {
public:
  int node;
  int dist;
  mypair(int n, int d) : node(n), dist(d) {}
};

bool operator<(const mypair &lhs, const mypair &rhs) {
  if (lhs.dist < rhs.dist)
    return true;
  else if (lhs.dist == rhs.dist)
    return (rhs.node < lhs.node);
  else
    return false;
}

void FindFlow(list<pair<int, int>> *ADJ, int n, int s, int t, int *path,
              int &m) {
  int *flow = new int[n];
  int *p = new int[n];
  int i;
  for (i = 0; i < n; i++)
    flow[i] = 0;
  flow[s] = MAXINT;
  for (i = 0; i < n; i++)
    p[i] = -1;
  priority_queue<mypair> Q;
  set<int> visited;
  Q.push(mypair(s, MAXINT));
  while (!Q.empty()) {
    mypair temp = Q.top();
    Q.pop();
    visited.insert(temp.node);
    // find all neighbours and update their dist values, if less update and
    // insert into Q
    list<pair<int, int>>::iterator it;
    for (it = ADJ[temp.node].begin(); it != ADJ[temp.node].end(); it++) {
      if (visited.find(it->first) == visited.end()) {
        if (flow[it->first] < it->second) {
          p[it->first] = temp.node;
          flow[it->first] = it->second;
          Q.push(mypair(it->first, flow[it->first]));
        }
      }
    }
  }

  int nd = t;
  stack<int> stk;
  while (p[nd] != -1) {
    stk.push(nd);
    nd = p[nd];
  }
  stk.push(nd);
  i = 0;
  while (!stk.empty()) {
    path[i] = stk.top();
    // cout << path[i] << " ";
    stk.pop();
    i++;
  }
  // cout << endl;
  m = i;

  delete[] flow;
  delete[] p;
}

int FindSmallestEdge(list<pair<int, int>> *ADJ, int n, int *path, int m) {
  int i, j;
  int smallest = MAXINT;
  list<pair<int, int>>::iterator it;
  for (i = 0; i < m - 1; i++)
    for (it = ADJ[path[i]].begin(); it != ADJ[path[i]].end(); it++)
      if (it->first == path[i + 1])
        if (it->second < smallest)
          smallest = it->second;
  return smallest;
}

void AdjustGraph(list<pair<int, int>> *ADJ, int n, int *path, int m, int temp) {
  int i, j;
  list<pair<int, int>>::iterator it;
  queue<int> re;
  for (i = 0; i < m - 1; i++) {
    for (it = ADJ[path[i]].begin(); it != ADJ[path[i]].end(); it++) {
      if (it->first == path[i + 1]) {
        break;
      }
    }
    if (it->second - temp > 0)
      it->second -= temp;
    else
      ADJ[path[i]].erase(it);
  }
  // backward edge
  for (i = m - 1; i > 0; i--) {
    for (it = ADJ[path[i]].begin(); it != ADJ[path[i]].end(); it++) {
      if (it->first == path[i - 1]) {
        break;
      }
    }
    if (it == ADJ[path[i]].end())
      ADJ[path[i]].push_back(make_pair(path[i - 1], temp));
    else
      it->second += temp;
  }
}

int MaximumFlow(list<pair<int, int>> *ADJ, int n, int s, int t) {
  // find a flow
  int i, j;
  int *path = new int[n];
  for (i = 0; i < n; i++)
    path[i] = -1;
  int m;
  int sum = 0;
  while (1) {
    m = 0;
    FindFlow(ADJ, n, s, t, path, m);
    if (m == 1)
      break;
    int temp = FindSmallestEdge(ADJ, n, path, m);
    // cout << temp << endl;
    AdjustGraph(ADJ, n, path, m, temp);
    sum += temp;
  }
  return sum;
}

bool possible(int a, int b, int *G) {
  int i, j, k;
  int x = round(1.0 * a / G[0]);
  int y = round(1.0 * b / G[1]);
  // cout << x << ", " << y << endl;
  if (x < 1)
    return false;
  // cout << 1.0*x*a << " , " << 1.0*y*b << endl;
  for (k = x; k <= y; k++) {
    if (1.0 * a >= G[0] * k * 0.9 && 1.0 * a <= G[0] * k * 1.1 &&
        1.0 * b >= G[1] * k * 0.9 && 1.0 * b <= G[1] * k * 1.1)
      return true;
  }
  return false;
}

int solve(int n, int p, int *G, int **V) {
  int i, j;
  if (n == 1) {
    int cnt = 0;
    for (i = 0; i < p; i++) {
      int x = round(1.0 * V[0][i] / G[0]);
      if (1.0 * V[0][i] >= 0.9 * G[0] * x && 1.0 * V[0][i] <= 1.1 * G[0] * x)
        cnt++;
    }
    return cnt;
  }
  /*
    for (i=0;i<n;i++) {
      for (j=0;j<p;j++) {
  cout << V[i][j] << " ";
      }
      cout << endl;
    }
  */
  list<pair<int, int>> *adj;
  adj = new list<pair<int, int>>[n * p + 2];
  for (i = 0; i < p; i++) {
    adj[0].push_back(make_pair(i + 1, 1));
  }
  for (i = 0; i < p; i++) {
    for (j = 0; j < p; j++) {
      if (possible(V[0][i], V[1][j], G)) {
        adj[i + 1].push_back(make_pair(p + 1 + j, 1));
      }
    }
  }
  for (i = p + 1; i <= n * p; i++) {
    adj[i].push_back(make_pair(n * p + 1, 1));
  }

  list<pair<int, int>>::iterator it;
  /*for (i=0;i<n*p+2;i++){
    cout << i << ": ";
    for (it=adj[i].begin();it!=adj[i].end();it++) cout << it->first << ":" <<
  it->second << " "; cout << endl;
  }*/

  return MaximumFlow(adj, n * p + 2, 0, n * p + 1);
}

int main() {
  ifstream infile;
  ofstream outfile;
  infile.open("rata.in");
  outfile.open("rata.txt");
  int i, j, k, t, n, p;
  infile >> t;
  for (j = 0; j < t; j++) {
    infile >> n >> p;
    int *G = new int[n];
    int **V = new int *[n];
    for (i = 0; i < n; i++)
      V[i] = new int[p];
    for (i = 0; i < n; i++)
      infile >> G[i];
    for (i = 0; i < n; i++)
      for (k = 0; k < p; k++)
        infile >> V[i][k];
    int r = solve(n, p, G, V);
    outfile << "Case #" << j + 1 << ": " << r << endl;
    delete[] G;
    for (i = 0; i < n; i++)
      delete[] V[i];
    delete[] V;
  }
  return 0;
}

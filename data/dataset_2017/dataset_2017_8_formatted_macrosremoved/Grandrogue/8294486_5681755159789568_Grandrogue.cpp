#include <fstream>
#include <iomanip>
#include <queue>
#include <vector>

using namespace std;

ifstream fin("C-small-attempt2.in");
ofstream fout("out.txt");

double e[100], s[100], x[100];
int n;

double dijkstra(vector<vector<pair<double, int>>> a) {
  vector<double> d(n, 1000000000000000), p(n);
  d[0] = 0.0;
  priority_queue<pair<double, int>> q;
  q.push(make_pair(0, 0));
  while (!q.empty()) {
    int v = q.top().second;
    double cur_d = -q.top().first;
    q.pop();
    if (cur_d > d[v])
      continue;

    for (size_t j = 0; j < a[v].size(); ++j) {
      int to = a[v][j].second;
      double len = a[v][j].first;
      if (d[v] + len < d[to]) {
        d[to] = d[v] + len;
        p[to] = v;
        q.push(make_pair(-d[to], to));
      }
    }
  }
  return d[n - 1];
}

int main() {
  int tests;
  fin >> tests;
  for (int test = 0; test < tests; ++test) {
    vector<vector<pair<double, int>>> a;
    int q;
    fin >> n >> q;
    int h;
    for (int i = 0; i < n; ++i) {
      fin >> e[i] >> s[i];
      vector<pair<double, int>> o;
      a.push_back(o);
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        fin >> h;
        if (j == i + 1) {
          x[j] = h;
        }
      }
    }
    fin >> h >> h;
    double cure = e[0];
    double curs = s[0];
    for (int i = 0; i < n - 1; ++i) {
      double end = 0;
      for (int j = i + 1; j < n; ++j) {
        end += x[j];
        if (end > e[i]) {
          break;
        }
        pair<double, int> g;
        g.first = end / s[i];
        g.second = j;
        a[i].push_back(g);
      }
    }

    fout << fixed << setprecision(8) << "Case #" << test + 1 << ": "
         << dijkstra(a) << endl;
  }
  return 0;
}

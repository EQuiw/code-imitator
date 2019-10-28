#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

long long a[105][105];

int main() {
  ios_base::sync_with_stdio(false);
  ifstream ifs("b.in");
  ofstream ofs("b.out");

  int t;
  ifs >> t;
  for (int test = 0; test < t; ++test) {
    int res = 0;
    int n, q;
    ifs >> n >> q;

    vector<int> d(n), s(n);
    for (int i = 0; i < n; ++i)
      ifs >> d[i] >> s[i];

    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j) {
        ifs >> a[i][j];
        if (i == j)
          a[i][j] = 0;
      }

    for (int k = 0; k < n; ++k)
      for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
          if (a[i][k] != -1 && a[k][j] != -1 &&
              (a[i][j] == -1 || a[i][j] > a[i][k] + a[k][j])) {
            a[i][j] = a[i][k] + a[k][j];
          }

    ofs << "Case #" << test + 1 << ":";
    for (int z = 0; z < q; ++z) {
      int start, fin;
      vector<double> dist(n, 1e+100);
      vector<int> was(n, 0);
      ifs >> start >> fin;
      --start;
      --fin;
      priority_queue<pair<double, int>, vector<pair<double, int>>,
                     greater<pair<double, int>>>
          q;
      q.push({0.0, start});
      dist[start] = 0;
      while (!q.empty()) {
        int cur = q.top().second;
        q.pop();
        if (cur == fin)
          break;
        if (was[cur] == 0) {
          was[cur] = 1;
          for (int next = 0; next < n; ++next) {
            if (was[next] == 0) {
              if (a[cur][next] != -1 && a[cur][next] <= d[cur]) {
                double time = a[cur][next] / (double)s[cur];
                if (dist[cur] + time < dist[next]) {
                  dist[next] = dist[cur] + time;
                  q.push({dist[next], next});
                }
              }
            }
          }
        }
      }
      ofs << ' ' << setprecision(10) << fixed << dist[fin];
    }
    ofs << endl;
  }
  return 0;
}

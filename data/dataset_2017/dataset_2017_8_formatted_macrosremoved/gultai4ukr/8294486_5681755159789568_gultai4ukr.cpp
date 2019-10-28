#include <bits/stdc++.h>
using namespace std;

bool comp(pair<int, char> &l, pair<int, char> &r) { return l.first < r.first; }

int main(int argc, char **argv) {
  ifstream fin("/home/roman/CodeliteProjects/Competitive/GCJ17_R1B/in.txt");
  ofstream fout("/home/roman/CodeliteProjects/Competitive/GCJ17_R1B/out.txt");

  int t;
  fin >> t;
  for (int testcase = 0; testcase < t; ++testcase) {
    int n, q, u, v;
    fin >> n >> q;
    assert(q == 1);
    vector<long long int> e(n), s(n);
    for (int i = 0; i < n; ++i) {
      fin >> e[i] >> s[i];
    }
    vector<vector<long long int>> d(n, vector<long long int>(n));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        fin >> d[i][j];
      }
    }
    fin >> u >> v;

    vector<vector<long long int>> dist(n, vector<long long int>(n, -1));
    for (int from = 0; from < n; ++from) {
      dist[from][from] = 0;
      for (int to = from + 1; to < n; ++to) {
        dist[from][to] = dist[from][to - 1] + d[to - 1][to];
        //				cout << from << ' ' << to << ' ' <<
        // dist[from][to] << endl;
      }
    }

    vector<double> dp(n, 1e18);
    dp[0] = 0;
    for (int to = 1; to < n; ++to) {
      for (int from = 0; from < to; ++from) {
        if (dist[from][to] <= e[from]) {
          dp[to] = min(dp[to], dp[from] + 1.0 * dist[from][to] / s[from]);
        }
      }
    }

    fout << "Case #" << testcase + 1 << ": " << fixed << setprecision(7)
         << dp[n - 1] << endl;
  }

  fin.close();
  fout.close();
  return 0;
}

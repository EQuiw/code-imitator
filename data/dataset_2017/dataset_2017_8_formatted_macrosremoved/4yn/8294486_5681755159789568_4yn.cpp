#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

int tc;

int main() {
  cin >> tc;
  for (int t = 1; t <= tc; t++) {
    int n, q;
    cin >> n >> q;
    int e[109], s[109];
    for (int i = 1; i <= n; i++) {
      cin >> e[i] >> s[i];
    }
    int adj[109][109];
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        cin >> adj[i][j];
      }
    }
    int dist[109];
    // distance to next city for small testcases
    for (int i = 1; i < n; i++) {
      dist[i] = adj[i][i + 1];
    }
    cout << "Case #" << t << ": ";
    for (int nq = 0; nq < q; nq++) {
      int u, v;
      cin >> u >> v;
      double time_taken[109];
      for (int i = 1; i <= n; i++) {
        time_taken[i] = -1;
      }
      time_taken[1] = 0;
      for (int i = 1; i < n; i++) {
        // simulate going to the next possible city with the horse at city i
        // cout << "Using horse from " << i << endl;
        int dist_left = e[i];
        int speed = s[i];
        double cur_time = time_taken[i];
        for (int j = i + 1; j <= n; j++) {
          // move dist[j-1]
          dist_left -= dist[j - 1];
          if (dist_left < 0)
            break;
          cur_time += (dist[j - 1] + 0.0) / s[i];
          // cout << "reach city " << j << " at " << cur_time << endl;
          if (time_taken[j] < 0) {
            time_taken[j] = cur_time;
          } else {
            time_taken[j] = min(time_taken[j], cur_time);
          }
        }
      }
      cout << fixed << setprecision(7) << time_taken[v] << endl;
    }
  }
}

#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

template <class P0, class P1>
ostream &operator<<(ostream &os, const pair<P0, P1> &p) {
  return os << "(" << p.first << "," << p.second << ")";
}
template <class T> void _dump(const T &t) {
  cerr << "[";
  for (auto it = t.begin(); it != t.end(); ++it)
    cerr << " " << *it;
  cerr << " ]"
       << "\n";
}
int main(void) {
  int T;
  cin >> T;

  for (int iCase = 1; iCase <= T; ++iCase) {
    cout << "Case #" << iCase << ":";

    int i, j, k, n, nRoutes;
    cin >> n >> nRoutes;
    vector<int> maxDist(n);
    vector<double> speed(n);
    for (i = 0; i < n; ++i)
      cin >> maxDist[i] >> speed[i];
    vector<vector<int>> dist0(n, vector<int>(n));
    for (i = 0; i < n; ++i)
      for (j = 0; j < n; ++j)
        cin >> dist0[i][j];

    for (int iRoute = 0; iRoute < nRoutes; ++iRoute) {
      int start, finish;
      cin >> start >> finish;
      --start;
      --finish;

      // if (iCase!=92) continue;
      {
        cerr << "maxDist"
             << ": ";
        _dump(maxDist);
      };
      {
        cerr << "speed"
             << ": ";
        _dump(speed);
      };

      //=====SMALL
      vector<double> bestTime(n, -1.0);
      bestTime[0] = 0.0;
      for (int horse = 0; horse < n; ++horse) {
        double time = bestTime[horse];
        double distLeft = maxDist[horse];
        for (i = horse; ++i < n && distLeft >= dist0[i - 1][i];) {
          distLeft -= dist0[i - 1][i];
          time += dist0[i - 1][i] / speed[horse];
          if (time < bestTime[i] || bestTime[i] == -1.0)
            bestTime[i] = time;
        }
        {
          cerr << "bestTime"
               << ": ";
          _dump(bestTime);
        };
      }

      cout << " " << setprecision(8) << bestTime[n - 1];
    }

    cout << "\n";
  }

  return 0;
}

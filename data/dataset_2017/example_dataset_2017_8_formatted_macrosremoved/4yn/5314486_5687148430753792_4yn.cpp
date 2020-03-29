#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

int tc;

int n, c, m;

int p, b;
vector<pii> tix;

vector<vector<int>> rides;

int main() {
  cin >> tc;
  for (int t = 1; t <= tc; t++) {
    // aim for small tc

    tix.clear();
    rides.clear();

    cin >> n >> c >> m;

    vector<int> ride_template(c + 1, 0);

    for (int i = 0; i < m; i++) {
      cin >> p >> b;
      tix.push_back(pii(p, b));
    }

    sort(tix.begin(), tix.end());

    rides.push_back(ride_template);

    int promos = 0;

    for (auto i : tix) {
      // cout << "For ticket " << i.first << " " << i.second << endl;
      if (i.first == 1) {
        if (rides.back()[1] == 0) {
          rides.back()[1] = i.second;
        } else {
          rides.push_back(ride_template);
          rides.back()[1] = i.second;
        }
      } else {
        // i.first == 2;
        bool placed = false;
        // try to place as a 2 first
        for (int j = 0; j < rides.size(); j++) {
          if (rides[j][2] == 0 && rides[j][1] != i.second) {
            // cout << "Place ticket " << i.first << " " << i.second << endl;
            rides[j][2] = i.second;
            placed = true;
            break;
          }
        }
        if (placed)
          continue;
        // then try to promote
        for (int j = 0; j < rides.size(); j++) {
          if (rides[j][1] == 0 && rides[j][2] != i.second) {
            // cout << "Promote ticket " << i.first << " " << i.second << endl;
            rides[j][1] = i.second;
            placed = true;
            promos++;
            break;
          }
        }
        if (placed)
          continue;
        // then as a last resort make a new ride
        rides.push_back(ride_template);
        rides.back()[2] = i.second;
      }
    }

    cout << "Case #" << t << ": " << rides.size() << " " << promos << endl;
  }
}

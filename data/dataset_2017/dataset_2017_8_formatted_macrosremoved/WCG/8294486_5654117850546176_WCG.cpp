#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  int tt;

  cin >> tt;

  for (int t = 1; t <= tt; ++t) {
    int n, r, o, y, g, b, v;
    cin >> n >> r >> o >> y >> g >> b >> v;
    string s = "";

    if ((r > n / 2) || (y > n / 2) || (b > n / 2))
      s = "IMPOSSIBLE";
    else {
      vector<pair<int, string>> v;
      v.push_back({r, "R"});
      v.push_back({y, "Y"});
      v.push_back({b, "B"});
      sort(v.begin(), v.end());
      reverse(v.begin(), v.end());
      while (v[0].first > 0) {
        s += v[0].second;
        v[0].first--;
        if (v[1].first > v[2].first) {
          s += v[1].second;
          v[1].first--;
        } else {
          s += v[2].second;
          v[2].first--;
        }
      }
      while ((v[1].first > 0) || (v[2].first > 0)) {
        if (v[1].first > v[2].first) {
          s += v[1].second;
          v[1].first--;
        } else {
          s += v[2].second;
          v[2].first--;
        }
      }
    }
    cout << "Case #" << t << ": " << s << endl;
  }

  return 0;
}

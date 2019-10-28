

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
  int T;
  cin >> T;
  for (int caso = 1; caso <= T; caso++) {
    int N, R, O, Y, G, B, V;
    cin >> N >> R >> O >> Y >> G >> B >> V;

    bool puedo = true;
    if (N < 2 * R)
      puedo = false;
    if (N < 2 * Y)
      puedo = false;
    if (N < 2 * B)
      puedo = false;
    cout << "Case #" << caso << ": ";
    if (!puedo) {
      cout << "IMPOSSIBLE" << endl;
      continue;
    }
    vector<pair<int, char>> vec;
    vec.push_back(pair<int, char>(R, 'R'));
    vec.push_back(pair<int, char>(Y, 'Y'));
    vec.push_back(pair<int, char>(B, 'B'));
    sort(vec.begin(), vec.end());
    int dif = vec[2].first - vec[1].first;
    string res = "";
    for (int i = 0; i < dif; i++) {
      res.push_back(vec[2].second);
      res.push_back(vec[1].second);
      res.push_back(vec[2].second);
      res.push_back(vec[0].second);
    }
    for (int i = 0; i < vec[0].first - dif; i++) {
      res.push_back(vec[2].second);
      res.push_back(vec[1].second);
      res.push_back(vec[0].second);
    }
    int act = 2;
    while ((int)res.size() < N) {
      if (act == 2) {
        res.push_back(vec[2].second);
        act = 1;
      } else {
        res.push_back(vec[1].second);
        act = 2;
      }
    }
    cout << res << endl;
  }
  return 0;
}

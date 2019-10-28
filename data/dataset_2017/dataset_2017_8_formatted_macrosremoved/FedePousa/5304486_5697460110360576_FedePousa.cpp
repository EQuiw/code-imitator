

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
    int N, P;
    cin >> N >> P;
    vector<int> need(N);
    for (int i = 0; i < N; i++) {
      cin >> need[i];
    }
    vector<vector<int>> pack(N, vector<int>(P));
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < P; j++) {
        cin >> pack[i][j];
      }
    }

    int res = -1;

    if (N == 1) {
      res = 0;
      for (int i = 0; i < P; i++) {
        bool sirve = (int)(ceil((double)pack[0][i] / (1.1 * need[0]))) <=
                     (int)(floor((double)pack[0][i] / (0.9 * need[0])));
        if (sirve)
          res++;
      }
    } else {
      res = 0;
      sort(pack[0].begin(), pack[0].end());
      do {
        int act = 0;
        for (int i = 0; i < P; i++) {
          int bajo = (int)(ceil((double)pack[0][i] / (1.1 * need[0])));
          int alto = (int)(floor((double)pack[0][i] / (0.9 * need[0])));
          if (bajo > alto)
            continue;
          int bajo2 = (int)(ceil((double)pack[1][i] / (1.1 * need[1])));
          int alto2 = (int)(floor((double)pack[1][i] / (0.9 * need[1])));
          if (bajo2 > alto2)
            continue;
          if (bajo > alto2)
            continue;
          if (alto < bajo2)
            continue;
          act++;
        }
        res = max(res, act);
      } while (next_permutation(pack[0].begin(), pack[0].end()));
    }
    cout << "Case #" << caso << ": " << res << endl;
  }
  return 0;
}

#define Federico using
#define Javier namespace
#define Pousa std;
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

Federico Javier Pousa

    int
    main() {
  int T;
  cin >> T;
  for (int caso = 1; caso <= T; caso++) {
    string S;
    int K, res = 0;
    bool pos = true;
    cin >> S >> K;
    for (int i = 0; i < (int)S.size() - K + 1; i++) {
      if (S[i] == '+')
        continue;
      res++;
      for (int j = 0; j < K; j++) {
        if (S[i + j] == '-') {
          S[i + j] = '+';
        } else {
          S[i + j] = '-';
        }
      }
    }
    for (int i = 0; i < (int)S.size(); i++) {
      if (S[i] == '-')
        pos = false;
    }

    cout << "Case #" << caso << ": ";
    if (!pos)
      cout << "IMPOSSIBLE" << endl;
    if (pos)
      cout << res << endl;
  }
  return 0;
}

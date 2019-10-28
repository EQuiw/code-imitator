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
    long long N, K;
    cin >> N >> K;
    map<long long, long long> dicc;
    dicc[N] = 1;
    map<long long, long long>::iterator it = dicc.end();
    it--;
    while (K > it->second) {
      if ((it->first) & 1) {
        dicc[(it->first) >> 1] += 2 * (it->second);
      } else {
        dicc[(it->first) >> 1] += it->second;
        dicc[((it->first) >> 1) - 1] += it->second;
      }
      K -= (it->second);
      it--;
    }
    int izq, der;
    izq = (it->first) >> 1;
    der = izq;
    if (!((it->first) & 1))
      izq--;
    dicc.clear();
    cout << "Case #" << caso << ": " << max(izq, der) << " " << min(izq, der)
         << endl;
  }
  return 0;
}

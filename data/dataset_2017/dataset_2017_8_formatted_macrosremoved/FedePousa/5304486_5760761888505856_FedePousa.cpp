

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
    int R, C;
    cin >> R >> C;
    vector<string> cake;
    string aux;
    for (int i = 0; i < R; i++) {
      cin >> aux;
      cake.push_back(aux);
    }

    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        if (cake[i][j] == '?')
          continue;
        for (int a = 0; a <= i; a++) {
          for (int b = 0; b <= j; b++) {
            if (cake[a][b] == '?')
              cake[a][b] = cake[i][j];
          }
        }
      }
      for (int a = 0; a <= i; a++) {
        char last;
        bool some = false;
        for (int j = 0; j < C; j++) {
          if (cake[a][j] != '?') {
            last = cake[a][j];
            some = true;
          }
        }
        if (!some)
          continue;
        for (int j = 0; j < C; j++) {
          if (cake[a][j] == '?')
            cake[a][j] = last;
        }
      }
    }
    for (int i = 0; i < R; i++) {
      if (cake[i][0] == '?')
        cake[i] = cake[i - 1];
    }

    cout << "Case #" << caso << ":" << endl;
    for (int i = 0; i < R; i++) {
      cout << cake[i] << endl;
    }
  }
  return 0;
}

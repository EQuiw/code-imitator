

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
    string N;
    cin >> N;
    for (int i = 0; i < (int)N.size() - 1; i++) {
      if (N[i] > N[i + 1]) {
        while (i > 0 && N[i] == N[i - 1])
          i--;
        N[i]--;
        i++;
        while (i < (int)N.size()) {
          N[i] = '9';
          i++;
        }
        break;
      }
    }
    if (N[0] == '0')
      N = N.substr(1);
    cout << "Case #" << caso << ": " << N << endl;
  }
  return 0;
}

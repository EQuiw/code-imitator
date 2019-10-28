#include <algorithm>
#include <float.h>
#include <iostream>
#include <limits.h>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <vector>
using namespace std;

int main() {
  int tests;
  cin >> tests;
  for (int t = 0; t < tests; t++) {
    string status;
    cin >> status;
    int K;
    cin >> K;
    int changed = 0;
    for (int i = 0; i < (int)(status.size()) - K + 1; i++) {
      if (status[i] == '-') {
        changed++;
        for (int j = 0; j < K; j++) {
          status[i + j] = (status[i + j] == '+') ? '-' : '+';
        }
      }
    }
    bool ok = true;
    for (int i = 0; i < status.size(); i++) {
      if (status[i] == '-') {
        ok = false;
        break;
      }
    }
    cout << "Case #" << (t + 1) << ": ";
    if (!ok) {
      cout << "IMPOSSIBLE" << endl;
    } else {
      cout << changed << endl;
    }
  }
}

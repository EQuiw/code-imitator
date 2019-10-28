#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
using namespace std;
typedef long long mint;
typedef unsigned long long umint;
int main() {
  freopen("A-small-attempt0.in", "r", stdin);
  freopen("Aout.txt", "w", stdout);
  int T;
  cin >> T;
  char s[1005];
  for (int t = 1; t <= T; t++) {
    cin >> s;
    int k;
    int len = strlen(s);
    vector<int> flips(len, 0);
    cin >> k;
    int flipss = 0;
    int tflips = 0;
    for (int i = 0; i < (len - k + 1); i++) {
      if (i >= k) {
        tflips -= flips[i - k];
      }
      int fp = (tflips & 1);
      int fpped = (s[i] != '+');
      if (fp ^ fpped) {
        flips[i] = 1;
        flipss++;
        tflips++;
      }
    }
    // cout << flipss << endl;
    printf("Case #%d: ", t);
    int i;
    for (i = len - k + 1; i < len; i++) {
      if (i >= k) {
        tflips -= flips[i - k];
      }
      int fp = (tflips & 1);
      int fpped = (s[i] != '+');
      if (fp ^ fpped) {
        cout << "IMPOSSIBLE" << endl;
        break;
      }
    }
    if (i == len) {
      cout << flipss << endl;
    }
  }
  return 0;
}

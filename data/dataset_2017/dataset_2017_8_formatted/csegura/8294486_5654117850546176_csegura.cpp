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

int getMin(int RYB[3]) {
  int minValue = INT_MAX;
  int minIndex = -1;
  for (int i = 0; i < 3; i++) {
    if ((RYB[i] < minValue) && (RYB[i] != 0)) {
      minIndex = i;
      minValue = RYB[i];
    }
  }
  return minIndex;
}

int getMax(int RYB[3], int avoid, int preference) {
  int maxIndex = -1;
  int maxValue = 0;
  if ((preference != avoid) && (RYB[preference] != 0)) {
    maxIndex = preference;
    maxValue = RYB[preference];
  }
  for (int i = 0; i < 3; i++) {
    if (i == avoid)
      continue;
    if (RYB[i] > maxValue) {
      maxIndex = i;
      maxValue = RYB[i];
    }
  }
  return maxIndex;
}

int main() {
  int tests;
  cin >> tests;
  for (int t = 0; t < tests; t++) {
    int N, R, O, Y, G, B, V;
    cin >> N >> R >> O >> Y >> G >> B >> V;
    int RYB[3] = {R, Y, B};
    char RYB_char[3] = {'R', 'Y', 'B'};
    vector<char> solution;
    int minIndex = getMin(RYB);
    RYB[minIndex]--;
    solution.push_back(RYB_char[minIndex]);
    int lastSelected = minIndex;
    for (int i = 1; i < N; i++) {
      int maxIndex = getMax(RYB, lastSelected, minIndex);
      if (maxIndex == -1)
        break;
      RYB[maxIndex]--;
      solution.push_back(RYB_char[maxIndex]);
      lastSelected = maxIndex;
    }
    if (solution.size() == N) {
      cout << "Case #" << (t + 1) << ": ";
      for (int i = 0; i < solution.size(); i++) {
        cout << solution[i];
      }
      cout << endl;
    } else {
      cout << "Case #" << (t + 1) << ": IMPOSSIBLE" << endl;
    }
  }
}

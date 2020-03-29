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
    int N, P;
    cin >> N >> P;
    int solution = 0;
    int counter = 0, counter1 = 0, counter2 = 0;
    for (int i = 0; i < N; i++) {
      int g;
      cin >> g;
      if (P == 2) {
        if ((g % 2) != 0) {
          counter++;
        } else {
          solution++;
        }
      } else if (P == 3) {
        if ((g % 3) == 1) {
          counter1++;
        } else if ((g % 3) == 2) {
          counter2++;
        } else {
          solution++;
        }
      }
    }
    if (P == 2) {
      solution += (counter + 1) / 2;
    } else if (P == 3) {
      int common = min(counter1, counter2);
      solution += common;
      counter1 -= common;
      counter2 -= common;
      if (counter1) {
        solution += (counter1 + 2) / 3;
      } else {
        solution += (counter2 + 2) / 3;
      }
    }
    cout << "Case #" << (t + 1) << ": " << solution << endl;
  }
}

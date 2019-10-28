#include <algorithm>
#include <float.h>
#include <iomanip>
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
    double D;
    long long N;
    cin >> D >> N;
    pair<double, double> horses[N];
    for (int i = 0; i < N; i++) {
      cin >> horses[i].first >> horses[i].second;
    }
    sort(horses, horses + N);
    double whenReaches[N + 1];
    whenReaches[N] = 0;
    for (int i = N - 1; i >= 0; i--) {
      whenReaches[i] =
          max(whenReaches[i + 1], (D - (horses[i].first)) / horses[i].second);
    }
    cout << "Case #" << (t + 1) << ": " << fixed << setprecision(10)
         << D / whenReaches[0] << endl;
  }
}

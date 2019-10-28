
#include <algorithm>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <random> // std::default_random_engine
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;

using namespace std;

int main() {
  int T;
  cin >> T;
  for (int cs = 1; cs <= T; cs++) {
    int n, p;
    cin >> n >> p;
    vector<int> r(n);
    for (int i = 0; i < n; i++)
      cin >> r[i];
    vector<deque<double>> Q(n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < p; j++) {
        int q;
        cin >> q;
        double k = double(q) / r[i];
        Q[i].push_back(k);
      }
    for (int i = 0; i < n; i++)
      sort(Q[i].begin(), Q[i].end());
    int ans = 0;

    bool hasempty = 0;
    while (!hasempty) {
      double minf = 9E9, maxf = 0;
      int minid = 0;
      for (int i = 0; i < n; i++) {
        if (Q[i].front() < minf) {
          minf = Q[i].front();
          minid = i;
        }
        maxf = max(maxf, Q[i].front());
      }
      bool good = 0;
      int midf = int((minf + maxf) / 2);
      for (int k = max(midf - 3, 1); k <= midf + 3; k++) {
        if (minf / k >= 0.9 - 1E-8 && minf / k <= 1.1 + 1E-8 &&
            maxf / k >= 0.9 - 1E-8 && maxf / k <= 1.1 + 1E-8) {
          good = 1;
          cerr << k << endl;
          break;
        }
      }
      if (good) {
        ans++;
        for (int i = 0; i < n; i++) {
          Q[i].pop_front();
          hasempty |= Q[i].empty();
        }
      } else {
        Q[minid].pop_front();
        hasempty |= Q[minid].empty();
      }
    }

    printf("Case #%d: %d\n", cs, ans);
  }

  return 0;
}


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
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;
typedef double ll;

using namespace std;

double arrive[1005];

int main() {
  int T;
  cin >> T;
  for (int cs = 1; cs <= T; cs++) {
    int D, N;
    cin >> D >> N;

    vector<pair<ll, ll>> h;
    for (int i = 0; i < N; i++) {
      ll k, s;
      cin >> k >> s;
      h.push_back(make_pair(k, s));
    }

    sort(h.begin(), h.end());
    int i = N - 1;
    double last = 0;
    for (i = N - 1; i >= 0; i--) {
      arrive[i] = double(D - h[i].first) / h[i].second;
      last = max(last, arrive[i]);
    }
    printf("Case #%d: %.6lf\n", cs, D / last);
  }
  return 0;
}

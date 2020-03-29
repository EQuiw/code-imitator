#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <bitset>
#include <cassert>
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
typedef long long ll;
#define MODD(a, b) (((a) % (b) + (b)) % (b))
#define EPS 1E-5
#define REP(i, s, t) for (int i = (s); i < (t); i++)
#define FILL(x, v) memset(x, v, sizeof(x))

using namespace std;

#define PI 3.14159265358979323846

int main() {
  int T;
  cin >> T;
  for (int cs = 1; cs <= T; cs++) {
    printf("Case #%d: ", cs);

    int n[2];
    cin >> n[0] >> n[1];
    vector<vector<int>> acts;

    int used[2] = {0, 0};

    for (int k = 0; k < 2; k++) {
      for (int i = 0; i < n[k]; i++) {
        int a, b;
        cin >> a >> b;
        acts.push_back(vector<int>({a, b, k}));
        used[k] += b - a;
      }
    }

    sort(acts.begin(), acts.end());
    if (acts.size() == 1) {
      puts("2");
      continue;
    }

    acts.push_back(acts.front());
    acts.back()[0] += 24 * 60;
    acts.back()[1] += 24 * 60;

    int ans = 0;
    for (int k = 0; k < 2; k++) {
      vector<int> gaps;

      for (int i = 1; i < acts.size(); i++) {
        if (acts[i][2] == k && acts[i - 1][2] == k) {
          gaps.push_back(acts[i][0] - acts[i - 1][1]);
        }
      }
      sort(gaps.begin(), gaps.end());
      int filled = 0;
      int left = 720 - used[k];
      for (int i = 0; i < gaps.size(); i++) {
        if (left >= gaps[i]) {
          left -= gaps[i];
          filled++;
        } else
          break;
      }

      ans = max(ans, (n[k] - filled) * 2);
    }

    cout << ans << endl;
  }
  return 0;
}
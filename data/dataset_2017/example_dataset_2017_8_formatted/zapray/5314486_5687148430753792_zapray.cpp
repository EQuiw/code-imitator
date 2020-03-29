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
int n, c, m;

int main() {
  int csn;
  cin >> csn;
  for (int cs = 1; cs <= csn; cs++) {
    printf("Case #%d: ", cs);
    cin >> n >> c >> m;

    vector<list<int>> Q;
    Q.resize(n);
    for (int i = 0; i < m; i++) {
      int b, p;
      cin >> p >> b;
      Q[p - 1].push_back(b);
    }
    vector<list<int>> Q0 = Q;

    int rides = 0;
    int fits = 0;
    while (fits < m) {
      unordered_set<int> ontrain;
      for (int seat = 0; seat < n; seat++) {

        pair<int, list<int>::iterator> cand;
        cand.first = -1;

        for (int i = seat; i < n; i++)
          for (auto it = Q[i].begin(); it != Q[i].end(); it++) {
            int x = *it;
            if (ontrain.count(x) == 0 &&
                (cand.first == -1 || Q[i].size() > Q[cand.first].size())) {
              cand.first = i;
              cand.second = it;
            }
          }

        if (cand.first != -1) {
          ontrain.insert(*cand.second);
          Q[cand.first].erase(cand.second);
          fits++;
        }
      }
      rides++;
    }
    int promo = 0;
    for (int i = 0; i < n; i++) {
      if (Q0[i].size() > rides) {
        promo += Q0[i].size() - rides;
      }
    }
    printf("%d %d\n", rides, promo);
  }

  return 0;
}
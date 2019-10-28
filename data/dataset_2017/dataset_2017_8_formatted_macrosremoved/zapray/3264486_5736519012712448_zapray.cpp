
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
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;

using namespace std;

void flip(string &s, int i, int k) {
  for (int j = 0; j < k; j++) {
    if (s[i + j] == '+')
      s[i + j] = '-';
    else
      s[i + j] = '+';
  }
}

int main() {
  int T;
  cin >> T;
  for (int cs = 1; cs <= T; cs++) {
    string s;
    int k;
    cin >> s >> k;
    int ans = 0;
    for (int i = 0; i + k - 1 < s.size(); i++) {
      if (s[i] == '-') {
        ans++;
        flip(s, i, k);
      }
    }
    bool ok = 1;
    for (char c : s)
      ok &= (c == '+');
    printf("Case #%d: ", cs);
    if (ok)
      printf("%d\n", ans);
    else
      puts("IMPOSSIBLE");
  }

  return 0;
}

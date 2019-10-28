#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

typedef long long ll;
typedef pair<int, int> PII;

int run(string str, int k) {
  int n = (int)str.length() - k;
  int ret = 0;
  for (int i = 0; i <= n; i++) {
    if (str[i] == '-') {
      ret++;
      for (int j = 0; j < k; j++) {
        int p = i + j;
        str[p] = (str[p] == '-' ? '+' : '-');
      }
    }
  }
  for (int i = n + 1; i < str.length(); i++) {
    if (str[i] == '-') {
      ret = 5000;
    }
  }
  return ret;
}

int main() {
  ios::sync_with_stdio(0);
  freopen("1.in", "r", stdin);
  freopen("out.txt", "w", stdout);
  int t;
  int cas = 1;
  cin >> t;
  while (t--) {
    string str;
    int k;
    cin >> str >> k;
    // cout << str << endl;
    // cout << k << endl;
    int ans = run(str, k);
    reverse(str.begin(), str.end());
    ans = min(run(str, k), ans);
    cout << "Case #" << cas++ << ": ";
    if (ans == 5000) {
      cout << "IMPOSSIBLE" << endl;
    } else
      cout << ans << endl;
  }

  return 0;
}

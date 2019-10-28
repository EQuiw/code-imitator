#include <algorithm>
#include <bitset>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>
using namespace std;

typedef unsigned long long int ull;
typedef long long int ll;
typedef vector<vector<ll>> mat;

int main() {
  ios_base::sync_with_stdio(false);
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int t, t1 = 0;
  cin >> t;
  while (t--) {
    t1++;
    cout << "Case #";
    cout << t1;
    cout << ": ";
    string s;
    int k;
    cin >> s >> k;
    int n = s.length();
    int a[100005] = {0};
    for (int i = 0; i <= n - 1; i++)
      if (s[i] == '+')
        a[i] = 1;
    int cnt = 0;
    for (int i = 0; i <= n - k; i++) {
      if (a[i] == 0) {
        cnt++;
        for (int j = i; j <= i + k - 1; j++)
          a[j] = 1 - a[j];
      }
    }

    int f = 0;
    for (int i = 0; i <= n - 1; i++)
      f += a[i];

    if (f != n)
      cout << "IMPOSSIBLE\n";
    else {
      cout << cnt;
      cout << "\n";
    }
  }
  return 0;
}

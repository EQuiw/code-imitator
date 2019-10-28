#include <algorithm>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#include <cmath>
#include <ctime>
#include <iomanip>
#include <queue>
#include <sstream>
#include <stack>
using namespace std;
typedef pair<int, int> PII;
typedef pair<string, string> PSS;
typedef pair<int, PII> PIP;
typedef long long ll;
typedef pair<ll, ll> PLL;

const int N = 1000010;

void solve(int ncase) {
  string s;
  int k;
  cin >> s >> k;
  int flip = 0;
  int sum = 0;
  int mark[1024] = {0};
  for (int i = 0; i <= s.size() - k; i++) {
    sum += mark[i];
    if ((sum + (s[i] == '-')) % 2) {
      mark[k + i]++;
      flip++;
      sum++;
    }
  }
  for (int i = s.size() - k + 1; i < s.size(); i++) {
    sum += mark[i];
    if ((sum + (s[i] == '-')) % 2) {
      cout << "Case #" << ncase << ": "
           << "IMPOSSIBLE" << endl;
      return;
    }
  }
  cout << "Case #" << ncase << ": " << flip << endl;
}

int main() {
  // ios::sync_with_stdio(false);
  cout << std::fixed;
  // cout << setprecision(16) << endl;

  int T = 1;
  scanf("%d", &T);
  // cin >> T;
  // precalc();
  int ncase = 0;
  while (T--) {
    solve(++ncase);
  }
}

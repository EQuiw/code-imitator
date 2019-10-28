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
//#include "utils/haha.h"
using namespace std;
typedef pair<int, int> PII;
typedef pair<string, string> PSS;
typedef pair<int, PII> PIP;
typedef long long ll;
typedef pair<ll, ll> PLL;

void solve(int ncase) {
  cout << "Case #" << ncase << ": ";
  ll d;
  int n;
  cin >> d >> n;
  vector<int> start(n);
  vector<int> speed(n);
  double t = -1;
  for (int i = 0; i < n; i++) {
    cin >> start[i] >> speed[i];
    double tmpt = (d - start[i]) * 1.0 / speed[i];
    if (tmpt > t)
      t = tmpt;
  }
  cout << d / t << endl;
}

int main() {
  // ios::sync_with_stdio(false);
  cout << std::fixed;
  cout << setprecision(16);

  // precalc();
  int T = 1;
  scanf("%d", &T);
  // cin >> T;
  int ncase = 0;
  while (T--) {
    solve(++ncase);
  }
}

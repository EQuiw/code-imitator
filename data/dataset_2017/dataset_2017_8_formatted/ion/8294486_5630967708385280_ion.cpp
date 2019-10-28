/* ***************************************
Author        :Scau.ion
Created Time  :2017/04/22 23:57:01 UTC+8
File Name     :ion.cpp
*************************************** */

#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define ULL unsigned long long
#define PB push_back
#define MP make_pair
#define PII pair<int, int>
#define VI vector<int>
#define VPII vector<PII>
#define X first
#define Y second
#define IOS                                                                    \
  ios::sync_with_stdio(0);                                                     \
  cin.tie(0);
#define IN freopen("A-small-attempt0.in", "r", stdin);
#define OUT freopen("A-small-attempt0.out", "w", stdout);

int main() {
  IN;
  OUT;
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) {
    int d, n;
    cin >> d >> n;
    double ma = 0;
    for (int j = 1; j <= n; ++j) {
      int ki, si;
      cin >> ki >> si;
      int len = d - ki;
      double ti = (double)len / (double)si;
      ma = max(ti, ma);
    }
    double ans = (double)d / ma;
    printf("Case #%d: %.6lf\n", i, ans);
  }
  return 0;
}

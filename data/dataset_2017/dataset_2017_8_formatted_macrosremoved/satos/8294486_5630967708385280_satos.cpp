#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

typedef long long int lli;
typedef pair<int, int> mp;
double d;
int n;
double solve() {
  double ans = -1;
  for (int i = 0; i < ((int)(n)); i++) {
    double k, s;
    scanf("%lf%lf", &k, &s);
    double na = d / ((d - k) / s);
    if (ans < 0 || na < ans)
      ans = na;
  }
  return ans;
}

int main(void) {
  int qn;
  scanf("%d", &qn);
  for (int qqq = ((int)(1)); qqq <= ((int)(qn)); qqq++) {
    scanf("%lf%d", &d, &n);
    printf("Case #%d: %f\n", qqq, solve());
  }
  return 0;
}

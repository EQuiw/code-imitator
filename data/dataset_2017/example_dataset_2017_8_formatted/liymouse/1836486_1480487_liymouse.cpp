#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>

typedef long long i64d;

using namespace std;

int main() {
  freopen("A-small-attempt1.in", "r", stdin);
  // freopen("input.txt" , "r" , stdin);
  freopen("A-small-attempt1.out", "w", stdout);
  int cas;
  scanf("%d", &cas);
  for (int ca = 1; ca <= cas; ca++) {
    printf("Case #%d:", ca);
    int n;
    int a[300];
    int sum = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
      sum += a[i];
    }
    double avg = 2.0 * (double)sum / n;
    double p[300];
    int check[300] = {0};
    int num = 0;
    double tot = sum;
    for (int i = 0; i < n; i++) {
      if (avg <= a[i]) {
        check[i] = 1;
        p[i] = 0;
      } else {
        num++;
        tot += a[i];
      }
    }
    if (num > 0)
      tot = tot / num;
    for (int i = 0; i < n; i++)
      if (check[i] == 0) {
        if (num > 0)
          p[i] = 100.0 * (tot - a[i]) / (double)sum;
        else
          p[i] = 0;
      }
    for (int i = 0; i < n; i++) {
      printf(" %lf", p[i]);
    }
    printf("\n");
  }
  return 0;
}
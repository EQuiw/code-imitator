#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;
const int INF = 0x7fffffff;
const long long INFF = 0x7fffffffffffffff;
const double pi = 3.141592653589793;
const double inf = 1e18;
const double eps = 1e-8;
const long long mod = 1e9 + 7;
/*************************************************************/
int a[20];
int b[20];
int main() {
  long long n;
  long long ans;
  freopen("B-small-attempt1.in", "r", stdin);
  freopen("B-small-attempt1.out", "w", stdout);
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++) {
    memset(a, 0, sizeof(a));
    ans = 0;
    cin >> n;
    long long m = n;
    int cnt = 0;
    while (m > 0) {
      a[cnt++] = m % 10;
      m /= 10;
    }
    for (int j = cnt - 1; j >= 1; j--) {
      if (a[j - 1] < a[j]) {
        a[j] -= 1;
        while (j < cnt - 1) {
          if (a[j + 1] > a[j]) {
            a[j + 1] -= 1;
            j++;
          } else
            break;
        }
        while (j >= 1) {
          a[j - 1] = 9;
          j--;
        }
      }
    }
    long long l = 1;
    for (int j = 0; j < cnt; j++) {
      ans += a[j] * l;
      l *= 10;
    }
    printf("Case #%d: %lld\n", i, ans);
  }
  fclose(stdin);
  fclose(stdout);

  return 0;
}

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;
const int N = 1005;
char str[N];
ll dp[10][20];
int main() {
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("out.txt", "w", stdout);
  int T, ca = 1;
  scanf("%d", &T);
  while (T--) {
    printf("Case #%d: ", ca++);
    scanf("%s", str);
    int n = strlen(str);
    int k = -1;
    for (int i = 0; i < n - 1; i++) {
      if (str[i] > str[i + 1]) {
        k = i;
        break;
      }
    }
    // printf("k:%d \n",k);
    while (k >= 0 && str[k] > str[k + 1]) {
      str[k]--;
      for (int i = k + 1; i < n; i++) {
        str[i] = '9';
        // printf("i:%d \n",i);
      }
      k--;
    }
    ll ret = 0, p = 1;
    for (int i = n - 1; i >= 0; i--, p *= 10) {
      ret += (str[i] - '0') * p;
    }
    printf("%I64d\n", ret);
  }
  return 0;
}

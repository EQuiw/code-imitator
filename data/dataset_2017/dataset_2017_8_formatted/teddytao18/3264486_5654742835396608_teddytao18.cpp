#include <iostream>
#include <map>
#include <math.h>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
using namespace std;
#define ll long long

int main() {
  int T;
  scanf("%d", &T);
  for (int t = 1; t <= T; t++) {
    ll b, h, k, n, num1, num2;
    scanf("%lld %lld", &n, &k);
    b = n;
    num1 = 1;
    num2 = 0;
    for (h = 1; h < k; h *= 2) {
      k -= h;
      if (b % 2) {
        b = b / 2;
        num1 = 2 * num1 + num2;
      } else {
        b = (b - 1) / 2;
        num2 = num1 + 2 * num2;
      }
    }
    printf("Case #%d: ", t);
    if (k <= num2)
      b++;
    if (b % 2)
      printf("%lld %lld\n", b / 2, b / 2);
    else
      printf("%lld %lld\n", b / 2, (b - 1) / 2);
  }
}

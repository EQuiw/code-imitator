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
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("B-small-attempt0.out", "w", stdout);
  int cas;
  scanf("%d", &cas);
  for (int ca = 1; ca <= cas; ca++) {
    printf("Case #%d: ", ca);
    char s[30];
    scanf("%s", s);
    int L = strlen(s);
    for (int i = L - 2; i >= 0; i--)
      if (s[i + 1] < s[i]) {
        s[i]--;
        for (int j = i; j > 0; j--)
          if (s[i] < '0') {
            s[i - 1]--;
            s[i] += 10;
          }
        for (int j = i + 1; j < L; j++)
          s[j] = '9';
      }
    char res[30];
    int k = 0;
    while (s[k] == '0')
      k++;
    for (int i = k; i < L; i++)
      res[i - k] = s[i];
    res[L - k] = 0;
    printf("%s\n", res);
  }
  return 0;
}
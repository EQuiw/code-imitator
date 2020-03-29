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
  freopen("A-small-attempt0.in", "r", stdin);
  freopen("A-small-attempt0.out", "w", stdout);
  int cas;
  string stin[3] = {"ejp mysljylc kd kxveddknmc re jsicpdrysi",
                    "rbcpc ypc rtcsra dkh wyfrepkym veddknkmkrkcd",
                    "de kr kd eoya kw aej tysr re ujdr lkgc jv"};

  string sout[3] = {"our language is impossible to understand",
                    "there are twenty six factorial possibilities",
                    "so it is okay if you want to just give up"};
  char s[200];
  int a[26];

  for (int i = 0; i < 26; i++)
    a[i] = -1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < stin[i].length(); j++)
      if (stin[i][j] != ' ') {
        a[stin[i][j] - 'a'] = sout[i][j] - 'a';
      }
  }
  a[16] = 25;
  a[25] = 16;
  scanf("%d", &cas);
  gets(s);
  for (int ca = 1; ca <= cas; ca++) {
    printf("Case #%d: ", ca);
    gets(s);
    for (int j = 0; j < strlen(s); j++)
      if (s[j] != ' ')
        s[j] = (char)(a[s[j] - 'a'] + 'a');
    printf("%s\n", s);
  }
  return 0;
}

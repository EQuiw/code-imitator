#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
char s[300];
int ca;
void init() {
  scanf("%s", s);
  int len = strlen(s);
  int st = 0;
  for (int i = 1; i < len; i++) {
    if (s[i] < s[i - 1]) {
      s[st] -= 1;
      for (int j = st + 1; j < len; j++)
        s[j] = '9';
      break;
    }
    if (s[i] != s[i - 1])
      st = i;
  }
  int flag = 0;
  printf("Case #%d: ", ca);
  for (int i = 0; i < len; i++) {
    if (flag == 0 && s[i] == '0')
      continue;
    else if (s[i] != '0')
      flag = 1;
    printf("%c", s[i]);
  }
  printf("\n");
}

int main() {
  int T;
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
  scanf("%d", &T);
  for (ca = 1; ca <= T; ca++) {
    init();
  }
}

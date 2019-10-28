#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

int T;
string N;

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int t;
  int i, j;

  cin >> T;
  for (t = 1; t <= T; t++) {
    cin >> N;

    int len = N.size();
    for (i = len - 1; i > 0; i--) {
      if (N[i - 1] > N[i]) {
        for (j = i; j < len; j++)
          N[j] = '9';
        N[i - 1]--;
      }
    }

    printf("Case #%d: ", t);

    bool chk = false;
    for (i = 0; i < len; i++) {
      if (N[i] != '0')
        chk = true;
      if (chk)
        printf("%c", N[i]);
    }
    printf("\n");
  }
  return 0;
}

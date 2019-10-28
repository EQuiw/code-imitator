#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

int main() {
  int T;
  freopen("A-small-attempt1.in", "r", stdin);
  freopen("output.txt", "w", stdout);

  scanf("%d", &T);

  for (int testCase = 1; testCase <= T; testCase++) {
    string str;
    int K;

    cin >> str >> K;

    int res = 0;
    for (int i = 0; i <= str.size() - K; i++) {
      if (str[i] == '-') {
        res++;
        for (int j = i; j < i + K; j++) {
          str[j] = str[j] == '-' ? '+' : '-';
        }
      }
    }

    bool isOK = true;
    for (int i = str.size() - 1; i >= 0; i--) {
      if (str[i] == '-') {
        isOK = false;
        break;
      }
    }
    printf("Case #%d: ", testCase);

    if (isOK) {
      printf("%d", res);
    } else {
      printf("IMPOSSIBLE");
    }

    printf("\n");
  }

  return 0;
}
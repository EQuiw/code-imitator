#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

int T;
string Pancakes;
int K;

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int t;
  int i, j;

  cin >> T;
  for (t = 1; t <= T; t++) {
    cin >> Pancakes >> K;

    bool err = false;
    int res = 0;
    for (i = 0; i < Pancakes.size() - K + 1; i++) {
      if (Pancakes[i] == '-') {
        for (j = 0; j < K; j++) {
          if (Pancakes[i + j] == '-')
            Pancakes[i + j] = '+';
          else
            Pancakes[i + j] = '-';
        }
        res++;
      }
    }
    for (i = 0; i < Pancakes.size(); i++) {
      if (Pancakes[i] == '-')
        err = true;
    }

    printf("Case #%d: ", t);
    if (err)
      printf("IMPOSSIBLE\n");
    else
      printf("%d\n", res);
  }
  return 0;
}
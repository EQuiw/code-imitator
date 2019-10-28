#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;
int main() {
  int T;
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("output.txt", "w", stdout);

  scanf("%d", &T);

  for (int testCase = 1; testCase <= T; testCase++) {
    long long N;
    vector<int> v;
    cin >> N;

    int prev = N % 10;
    N /= 10;
    v.push_back(prev);
    while (N != 0) {
      int now = N % 10;
      if (prev < now) {
        N--;
        now = N % 10;
        for (int i = 0; i < v.size(); i++) {
          v[i] = 9;
        }
      }
      N /= 10;
      v.push_back(now);
      prev = now;
    }

    while (v.back() == 0)
      v.pop_back();

    printf("Case #%d: ", testCase);
    for (int i = v.size() - 1; i >= 0; i--) {
      printf("%d", v[i]);
    }
    printf("\n");
  }

  return 0;
}

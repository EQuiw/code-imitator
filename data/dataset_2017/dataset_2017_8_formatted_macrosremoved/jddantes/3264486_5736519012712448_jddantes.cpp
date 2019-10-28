#include <bits/stdc++.h>

using namespace std;

void toggle(int *mask, int start, int k) {
  int kmask = (1 << k) - 1;
  *mask = (*mask) ^ (kmask << start);
}

int main() {
  int cases;
  scanf("%d", &cases);

  for (int e = 0; e < cases; e++) {
    string str;
    int N;
    int K;
    cin >> str >> K;

    N = str.size();

    int cnt = 0;
    for (int i = 0; i + K - 1 < N; i++) {
      if (str[i] == '+')
        continue;
      for (int j = 0; j < K; j++) {
        str[i + j] = str[i + j] == '+' ? '-' : '+';
      }
      cnt++;
    }

    bool good = true;
    for (int i = 0; i < N; i++) {
      if (str[i] == '-') {
        good = false;
        break;
      }
    }

    if (good) {
      printf("Case #%d: %d\n", e + 1, cnt);
    } else {
      printf("Case #%d: IMPOSSIBLE\n", e + 1);
    }
  }

  return 0;
}

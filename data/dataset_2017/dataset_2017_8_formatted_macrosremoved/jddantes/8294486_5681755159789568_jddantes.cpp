#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

typedef tuple<int, int, ll> t3;

int N;

int input[100][100];
int input_spd[100];
int input_rem[100];

map<t3, double> memo;

double f(int index, int spd, ll rem) {
  if (index == N - 1) {
    return 0;
  }

  t3 state(index, spd, rem);
  auto itr = memo.find(state);
  if (itr != memo.end()) {
    return itr->second;
  }

  double best_ret = (1e200);

  if (rem - input[index][index + 1] >= 0) {
    double this_horse = (double)input[index][index + 1] / (double)spd +
                        f(index + 1, spd, rem - input[index][index + 1]);
    best_ret = min(best_ret, this_horse);
  }

  // Use this horse
  if (input_rem[index] - input[index][index + 1] >= 0) {
    double this_horse =
        (double)input[index][index + 1] / (double)input_spd[index] +
        f(index + 1, input_spd[index],
          input_rem[index] - input[index][index + 1]);
    best_ret = min(best_ret, this_horse);
  }

  memo[state] = best_ret;
  return best_ret;
}

int main() {
  int cases;
  scanf("%d", &cases);

  for (int e = 0; e < cases; e++) {
    int Q;
    scanf("%d %d", &N, &Q);
    for (int i = 0; i < N; i++) {
      scanf("%d %d", &input_rem[i], &input_spd[i]);
    }
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        scanf("%d", &input[i][j]);
      }
    }

    printf("Case #%d:", e + 1);
    for (int q = 0; q < Q; q++) {
      int src, dest;
      scanf("%d %d", &src, &dest);
      memo.clear();
      double ans = f(0, input_spd[0], input_rem[0]);
      printf(" %f", ans);
    }
    printf("\n");
  }
  return 0;
}

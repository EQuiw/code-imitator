#include <bits/stdc++.h>

using namespace std;

#define MAX_N 1000

typedef tuple<int, int, int> t3;

bool vis[MAX_N + 2];
int N, K;

int countStalls(int index, int dir) {
  int cnt = 0;
  for (int i = index + dir; !vis[i]; i += dir) {
    cnt++;
  }
  return cnt;
}

int getLeftmost() {
  for (int i = 0; i <= N + 1; i++) {
    if (!vis[i])
      return i;
  }
}

t3 compare_t3(t3 a, t3 b) { // index, ls, rs
  int min_a = min(get<1>(a), get<2>(a));
  int min_b = min(get<1>(b), get<2>(b));

  if (min_a == min_b) {
    int max_a = max(get<1>(a), get<2>(a));
    int max_b = max(get<1>(b), get<2>(b));

    if (max_a == max_b) {
      if (get<0>(a) < get<0>(b)) {
        return a;
      } else {
        return b;
      }

    } else if (max_a > max_b) {
      return a;
    } else {
      return b;
    }

  } else if (min_a > min_b) {
    return a;
  } else {
    return b;
  }
}

int main() {
  int cases;

  scanf("%d", &cases);

  for (int e = 0; e < cases; e++) {
    scanf("%d %d", &N, &K);
    memset(vis, 0, sizeof vis);
    // printf("Case %d\n", e+1);
    vis[0] = 1;
    vis[N + 1] = 1;

    int best_min = 0;
    int best_max = 0;

    for (int rep = 0; rep < K; rep++) {
      t3 best_t3(N + 1, 0, 0);
      // printf("Person %d\n", rep);
      for (int s = 1; s <= N; s++) {
        if (vis[s])
          continue;
        int ls = countStalls(s, -1);
        int rs = countStalls(s, 1);
        // printf("at s = %d, ls is %d rs is %d\n",s,ls,rs);
        t3 cur_t3(s, ls, rs);
        best_t3 = compare_t3(best_t3, cur_t3);
      }

      int idx = get<0>(best_t3);
      // printf("Person %d chooses %d\n", rep,idx);
      if (rep == K - 1) {
        int ls = countStalls(idx, -1);
        int rs = countStalls(idx, 1);

        // printf("ls %d rs %d\n", ls, rs);

        best_min = min(ls, rs);
        best_max = max(ls, rs);
      }
      vis[idx] = 1;
    }

    printf("Case #%d: %d %d\n", e + 1, best_max, best_min);
  }

  return 0;
}
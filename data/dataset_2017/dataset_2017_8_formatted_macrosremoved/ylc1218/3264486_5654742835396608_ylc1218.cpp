#include <cstdio>
#include <cstdlib>
#include <queue>
using namespace std;

int T, N, K;

int main() {
  scanf("%d", &T);

  int x, y;
  for (int t = 1; t <= T; t++) {
    scanf("%d%d", &N, &K);
    priority_queue<int> que;

    que.push(N);
    while (--K) {
      x = que.top(), que.pop();
      que.push(x / 2);
      que.push((x - 1) / 2);
    }
    x = que.top(), que.pop();

    printf("Case #%d: %d %d\n", t, x / 2, (x - 1) / 2);
  }
  return 0;
}

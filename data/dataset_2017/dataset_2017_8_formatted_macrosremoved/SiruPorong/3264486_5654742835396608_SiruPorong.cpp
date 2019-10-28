#include <functional>
#include <queue>
#include <stdio.h>
#include <vector>

using namespace std;

int n, p;

int main() {
  int i, j, t;

  freopen("output.txt", "w", stdout);
  freopen("input.txt", "r", stdin);

  scanf("%d", &t);

  for (int tt = 1; tt <= t; tt++) {
    scanf("%d%d", &n, &p);
    int answer = 0, ls, rs, s;

    priority_queue<int> q;
    q.push(n);

    for (i = 1; i <= p; i++) {
      s = q.top();
      q.pop();

      if (s / 2)
        q.push(s / 2);
      if ((s - 1) / 2)
        q.push((s - 1) / 2);
    }

    printf("Case #%d: %d %d\n", tt, s / 2, (s - 1) / 2);
  }
  return 0;
}

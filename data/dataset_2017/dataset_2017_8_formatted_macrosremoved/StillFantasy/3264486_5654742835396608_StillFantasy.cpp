#include <bits/stdc++.h>
using namespace std;

int main() {
  int test, kase = 0;
  int n, k;
  scanf("%d", &test);
  while (test--) {
    scanf("%d%d", &n, &k);
    priority_queue<int> q;
    q.push(n);
    for (int i = 0; i < k - 1; i++) {
      int x = q.top();
      q.pop();
      if (x & 1) {
        q.push(x / 2);
        q.push(x / 2);
      } else {
        q.push(x / 2);
        q.push(x / 2 - 1);
      }
    }

    int x = q.top();
    if (x & 1)
      printf("Case #%d: %d %d\n", ++kase, x / 2, x / 2);
    else
      printf("Case #%d: %d %d\n", ++kase, x / 2, x / 2 - 1);
  }
  return 0;
}

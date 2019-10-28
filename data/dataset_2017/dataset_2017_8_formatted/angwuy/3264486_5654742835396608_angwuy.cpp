#include <cstdio>
#include <cstring>
#include <queue>

std::priority_queue<int> heap;

int n, k;

void init() { scanf("%d %d", &n, &k); }

void solve() {
  while (heap.size() > 0)
    heap.pop();
  heap.push(n);
  for (int i = 1; i < k; ++i) {
    int t = heap.top();
    heap.pop();
    int t1 = (t - 1) / 2;
    int t2 = t - 1 - t1;
    heap.push(t1);
    heap.push(t2);
  }
  int t = heap.top();
  heap.pop();
  int t1 = (t - 1) / 2;
  int t2 = t - 1 - t1;
  printf("%d %d\n", t2, t1);
}

int main() {
  int tt;
  scanf("%d", &tt);
  for (int ii = 1; ii <= tt; ++ii) {
    init();
    printf("Case #%d: ", ii);
    solve();
  }
  return 0;
}
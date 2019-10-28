#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

int main(void) {
  int t;
  scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++) {

    int n, k;
    priority_queue<int> q;
    scanf("%d%d", &n, &k);
    q.push(n);
    while (--k) {
      int x = q.top();
      q.pop();
      q.push(x / 2);
      q.push((x - 1) / 2);
    }

    int v = q.top();
    printf("Case #%d: %d %d\n", tt, v / 2, (v - 1) / 2);
  }
  return 0;
}

/*
12
0 xoooooooooooox
1 xoooooxoooooox 6 5
2 xoooooxooxooox 3 2
3 xooxooxooxooox 2 2
4 xooxooxooxoxox 1 1
5 xxoxooxooxoxox 1 0
6 xxoxxoxooxoxox 1 0
7 xxoxxoxxoxoxox 1 0
                 0 0

x------------x 12
x-----1------x 6
x-----1--2---x 5
x--3--1--2---x 3
x--3--1--2-4-x 2
x5-3--1--2-4-x 2
*/

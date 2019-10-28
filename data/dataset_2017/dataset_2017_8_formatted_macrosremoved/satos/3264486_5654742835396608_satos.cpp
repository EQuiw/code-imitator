#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

typedef long long int lli;
typedef pair<int, int> mp;
int n, k;

int main(void) {
  int qn;
  scanf("%d", &qn);
  for (int qqq = ((int)(1)); qqq <= ((int)(qn)); qqq++) {
    scanf("%d%d", &n, &k);
    priority_queue<int> que;
    que.push(n);
    for (int i = 0; i < ((int)(k - 1)); i++) {
      int x = que.top();
      que.pop();
      x--;
      if (x <= 0)
        continue;
      que.push(x - x / 2);
      if (x / 2 > 0)
        que.push(x / 2);
    }
    int t = que.top();
    t--;

    printf("Case #%d: %d %d\n", qqq, t - t / 2, t / 2);
  }
  return 0;
}

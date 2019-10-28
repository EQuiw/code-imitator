#include <algorithm>
#include <assert.h>
#include <functional>
#include <iostream>
#include <map>
#include <math.h>
#include <memory.h>
#include <queue>
#include <set>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> Pi;
int N, M, T, K, tc;

int p[1050];
void solve() {
  string s;
  cin >> s;
  int len = s.size();
  int x = -1;
  for (int i = 0; i < len; i++) {
    p[i + 1] = s[i] - '0';
  }
  for (int i = 1; i <= len - 1; i++) {
    if (p[i] > p[i + 1]) {
      x = i;
      break;
    }
  }

  if (x == -1) {
    cout << s << endl;
    return;
  }
  int y = -1;
  for (int i = x; i >= 1; i--) {
    if (p[i] > p[i - 1]) {
      y = i;
      break;
    }
  }

  if (y == -1) {
    for (int i = 0; i < len - 1; i++)
      printf("9");
    printf("\n");
    return;
  }
  p[y]--;

  bool start = false;
  for (int i = 0; i <= y; i++) {
    if (p[i] != 0)
      start = true;
    if (start)
      printf("%d", p[i]);
  }
  for (int i = y + 1; i <= len; i++)
    printf("9");
  printf("\n");
}

bool ascending(int x) {
  int q[100];
  int pos = 0;

  while (x > 0) {
    q[pos] = x % 10;
    x /= 10;
    pos++;
  }
  for (int i = 0; i < pos - 1; i++) {
    if (q[i] < q[i + 1]) {
      return false;
    }
  }

  return true;
}

void solve2() {
  int x;
  cin >> x;
  for (int i = x; i >= 0; i--) {
    if (ascending(i)) {
      cout << i << endl;
      return;
    }
  }
}

int main(void) {
  freopen("output1.txt", "w", stdout);
  scanf("%d", &tc);
  for (int tcx = 1; tcx <= tc; tcx++) {
    printf("Case #%d: ", tcx);
    solve2();
    // solve();
  }
}

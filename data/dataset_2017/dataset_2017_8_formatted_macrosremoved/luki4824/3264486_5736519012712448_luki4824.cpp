// Oversized Pancake Flipper.cpp : Defines the entry point for the console
// application.
//

#include <cstdio>
#include <queue>
#include <string>
using namespace std;

int solve(string s, int k) {
  queue<int> q;
  int res = 0;
  int i;
  for (i = 0; i + k - 1 < s.length(); ++i) {
    while (!q.empty() && q.front() < i)
      q.pop();
    if ((s[i] == '-' && q.size() % 2 == 0) || (s[i] == '+' && q.size() % 2)) {
      q.push(i + k - 1);
      res++;
    }
    s[i] = '+';
  }
  for (; i < s.length(); ++i) {
    while (!q.empty() && q.front() < i)
      q.pop();
    if ((s[i] == '-' && q.size() % 2 == 0) || (s[i] == '+' && q.size() % 2))
      s[i] = '-';
    else
      s[i] = '+';
  }
  bool allPlus = true;
  for (int i = 0; i < s.length(); ++i)
    allPlus = allPlus && s[i] == '+';
  return allPlus ? res : -1;
}
int main() {
  char c[10001];
  int t, k;
  scanf("%d", &t);
  for (int i = 1; i <= t; ++i) {
    scanf("%s %d", &c, &k);
    string s(c);
    int res = solve(s, k);
    printf("Case #%d: ", i);
    if (res < 0)
      printf("IMPOSSIBLE\n");
    else
      printf("%d\n", res);
  }
  return 0;
}

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#define LL long long
#define eps 1e-8
#define mem(a, b) memset(a, b, sizeof(a))
#define zero(x) ((x > +eps) - (x < -eps))
#define MAX 100010
#define INF 100000000
#define MAXEDGE 50010
#define MAX 2100
using namespace std;
// freopen("", "r", stdin);
// freopen("", "w", stdout);
// printf("Case #%d: ", ii);

int color[6];
char str[1010];
map<int, char> mp;
priority_queue<pair<int, char>> q;

int main() {
  freopen("B-small-attempt2.in", "r", stdin);
  freopen("B-small-attempt2.out", "w", stdout);
  int T;
  int d, n;
  pair<int, char> temp, newd, sp;
  scanf("%d", &T);
  for (int ii = 1; ii <= T; ii++) {
    scanf("%d", &n);
    for (int i = 0; i < 6; i++) {
      scanf("%d", &color[i]);
    }
    while (!q.empty()) {
      q.pop();
    }
    temp.first = color[0];
    temp.second = 'R';
    q.push(temp);
    temp.first = color[2];
    temp.second = 'Y';
    q.push(temp);
    temp.first = color[4];
    temp.second = 'B';
    q.push(temp);
    temp = q.top();
    q.pop();
    newd = q.top();
    q.pop();
    if (temp.first > newd.first + q.top().first) {
      printf("Case #%d: IMPOSSIBLE\n", ii);
      continue;
    }
    mp[3] = temp.second;
    temp.second = 3;
    mp[2] = newd.second;
    newd.second = 2;
    sp = q.top();
    q.pop();
    mp[1] = sp.second;
    sp.second = 1;
    q.push(temp);
    q.push(newd);
    q.push(sp);
    for (int i = 0; i < n; i++) {
      temp = q.top();
      q.pop();
      if (i > 0 && str[i - 1] == mp[temp.second]) {
        if (!q.empty()) {
          newd = q.top();
          q.pop();
          q.push(temp);
          temp = newd;
        } else {
          printf("error\n");
        }
      }
      str[i] = mp[temp.second];
      temp.first--;
      if (temp.first > 0) {
        q.push(temp);
      }
    }
    if (str[n - 1] == str[0]) {
      swap(str[n - 2], str[n - 1]);
      if (str[n - 2] == str[n - 3] || str[n - 1] == str[0]) {
        printf("error.\n");
      }
    }
    for (int i = 1; i < n; i++) {
      if (str[i] == str[i - 1]) {
        printf("error.\n");
      }
    }
    if (str[0] == str[n - 1]) {
      printf("error.\n");
    }
    str[n] = '\0';
    printf("Case #%d: %s\n", ii, str);
  }
  return 0;
}
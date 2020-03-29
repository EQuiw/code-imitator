#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

typedef pair<int, int> par;
typedef long long int tint;
pair<par, int> act[250];

int main() {
  freopen("test.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  int t, c, j;
  int a, b;
  cin >> t;

  for (int caso = (1); caso < (t + 1); caso++) {
    cin >> c >> j;
    for (int i = 0; i < (c); i++) {
      cin >> a >> b;
      act[i] = make_pair(make_pair(a, b), 1);
    }
    for (int i = 0; i < (j); i++) {
      cin >> a >> b;
      act[i + c] = make_pair(make_pair(a, b), 2);
    }
    sort(act, act + c + j);

    int ans = 0;

    if (max(c, j) == 1)
      ans = 2;
    else {
      int t = act[1].first.second - act[0].first.first;
      if (t <= 720)
        ans = 2;
      else
        ans = 4;
    }
    cout << "Case #" << caso << ": " << ans << endl;
  }

  return 0;
}

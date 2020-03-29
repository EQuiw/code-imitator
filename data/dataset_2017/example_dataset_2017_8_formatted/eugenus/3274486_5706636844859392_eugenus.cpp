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

#define forn(i, n) for (int i = 0; i < (n); i++)
#define forsn(i, s, n) for (int i = (s); i < (n); i++)
#define all(v) ((v).begin, (v).end)
#define pb push_back
#define x first
#define y second
#define mp make_pair

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

  forsn(caso, 1, t + 1) {
    cin >> c >> j;
    forn(i, c) {
      cin >> a >> b;
      act[i] = mp(mp(a, b), 1);
    }
    forn(i, j) {
      cin >> a >> b;
      act[i + c] = mp(mp(a, b), 2);
    }
    sort(act, act + c + j);

    int ans = 0;

    if (max(c, j) == 1)
      ans = 2;
    else {
      int t = act[1].x.y - act[0].x.x;
      if (t <= 720)
        ans = 2;
      else
        ans = 4;
    }
    cout << "Case #" << caso << ": " << ans << endl;
  }

  return 0;
}
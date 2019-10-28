/*
 *
 *	Created by Ziyi Tang
 *
 */

//#include <bits/stdc++.h>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pi;
typedef vector<pi> vpi;
typedef vector<vpi> vvpi;
const int INF = 0x3f3f3f;
const ll INFL = (ll)1E18;
const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
#define REP(i, s, t) for (int i = (s); i < (t); i++)
#define FILL(x, v) memset(x, v, sizeof(x))
#define MAXN 1000
#define MOD 1000000007

int main() {
  int T;
  cin >> T;
  REP(t, 1, T + 1) {
    int N, R, O, Y, G, B, V;
    cin >> N >> R >> O >> G >> Y >> B >> V;
    if (R >= G && R >= B && G + B >= R) {
      string re = "";
      int rb = R - G;
      int rgb = B - (R - G);
      int rg = G - rgb;
      REP(i, 0, rgb) re += "RYB";
      REP(i, 0, rg) re += "RY";
      REP(i, 0, rb) re += "RB";
      printf("Case #%d: ", t);
      cout << re << endl;
    } else if (G >= R && G >= B && R + B >= G) {
      string re = "";
      int rb = G - R;
      int rgb = B - rb;
      int rg = R - rgb;
      REP(i, 0, rgb) re += "YRB";
      REP(i, 0, rg) re += "YR";
      REP(i, 0, rb) re += "YB";
      printf("Case #%d: ", t);
      cout << re << endl;
    } else if (B >= G && B >= R && G + R >= B) {
      string re = "";
      int rb = B - R;
      int rgb = G - rb;
      int rg = R - rgb;
      REP(i, 0, rgb) re += "BRY";
      REP(i, 0, rg) re += "BR";
      REP(i, 0, rb) re += "BY";
      printf("Case #%d: ", t);
      cout << re << endl;
    } else {
      printf("Case #%d: IMPOSSIBLE\n", t);
    }
  }
  return 0;
}
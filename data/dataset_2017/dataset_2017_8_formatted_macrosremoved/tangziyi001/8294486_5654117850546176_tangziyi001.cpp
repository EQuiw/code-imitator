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

int main() {
  int T;
  cin >> T;
  for (int t = (1); t < (T + 1); t++) {
    int N, R, O, Y, G, B, V;
    cin >> N >> R >> O >> G >> Y >> B >> V;
    if (R >= G && R >= B && G + B >= R) {
      string re = "";
      int rb = R - G;
      int rgb = B - (R - G);
      int rg = G - rgb;
      for (int i = (0); i < (rgb); i++)
        re += "RYB";
      for (int i = (0); i < (rg); i++)
        re += "RY";
      for (int i = (0); i < (rb); i++)
        re += "RB";
      printf("Case #%d: ", t);
      cout << re << endl;
    } else if (G >= R && G >= B && R + B >= G) {
      string re = "";
      int rb = G - R;
      int rgb = B - rb;
      int rg = R - rgb;
      for (int i = (0); i < (rgb); i++)
        re += "YRB";
      for (int i = (0); i < (rg); i++)
        re += "YR";
      for (int i = (0); i < (rb); i++)
        re += "YB";
      printf("Case #%d: ", t);
      cout << re << endl;
    } else if (B >= G && B >= R && G + R >= B) {
      string re = "";
      int rb = B - R;
      int rgb = G - rb;
      int rg = R - rgb;
      for (int i = (0); i < (rgb); i++)
        re += "BRY";
      for (int i = (0); i < (rg); i++)
        re += "BR";
      for (int i = (0); i < (rb); i++)
        re += "BY";
      printf("Case #%d: ", t);
      cout << re << endl;
    } else {
      printf("Case #%d: IMPOSSIBLE\n", t);
    }
  }
  return 0;
}

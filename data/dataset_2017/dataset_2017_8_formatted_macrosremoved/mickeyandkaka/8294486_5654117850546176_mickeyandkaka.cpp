#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> VI;
typedef pair<int, int> PII;

vector<string> split(const string &s, char c) {
  vector<string> v;
  stringstream ss(s);
  string x;
  while (getline(ss, x, c))
    v.push_back(x);
  return v;
}
void err(vector<string>::iterator it) {}
template <typename T, typename... Args>
void err(vector<string>::iterator it, T a, Args... args) {
  cerr << it->substr((*it)[0] == ' ', it->length()) << " = " << a << ", ";
  err(++it, args...);
}
const int INF = 0x3f3f3f3f;

int T;

int n, r, o, y, g, b, v;

typedef pair<int, char> pp;

char s[1111][1111];

int main() {
  int cas = 1;
  scanf("%d", &T);

  while (T--) {
    printf("Case #%d: ", cas++);

    cin >> n >> r >> o >> y >> g >> b >> v;

    vector<pp> vv;
    vv.push_back({r, 'R'});
    vv.push_back({y, 'Y'});
    vv.push_back({b, 'B'});
    // debug(r, y, b);

    sort(vv.begin(), vv.end());

    if (vv[2].first > vv[0].first + vv[1].first) {
      printf("IMPOSSIBLE\n");
      continue;
    }

    memset(s, 0, sizeof(s));
    for (int i = 1; i <= vv[2].first; i++) {

      s[i][0] = vv[2].second;
      // debug(i, s[i][0]);
    }

    for (int i = 1; i <= vv[1].first; i++) {
      s[i][1] = vv[1].second;
      // debug(i, s[i][1]);
    }

    int row = vv[1].first + 1;
    int col = 1;

    for (int i = 1; i <= vv[0].first; i++) {
      if (row > vv[2].first) {
        col++;
        row = 1;
      }

      s[row][col] = vv[0].second;
      row++;
    }

    string ans = "";
    for (int i = 1; i <= vv[2].first; i++) {
      for (int j = 0; j < 3; j++) {
        // debug(i, j, s[i][j]);
        if (s[i][j] != '\0')
          ans += s[i][j];
      }
    }
    cout << ans << endl;
  }

  return 0;
}

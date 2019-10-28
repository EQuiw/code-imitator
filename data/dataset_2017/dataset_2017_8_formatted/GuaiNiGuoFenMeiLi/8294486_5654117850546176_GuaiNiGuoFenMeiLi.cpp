#include <stdio.h>

#include <algorithm>
#include <string.h>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int n, r, o /* r+y */, y, g /* y+b */, b, v /* r+b */;

void ins(string &str, char ch, int cnt, string rep) {
  for (int i = 0; i < str.size(); ++i) {
    if (str[i] == ch) {
      string ans = str.substr(0, i + 1);
      for (int j = 0; j < cnt; ++j) {
        ans += rep;
      }
      ans += str.substr(i + 1);
      str = ans;
      return;
    }
  }
}

string solve() {
  if (b - o < 0 || r - g < 0 || y - v < 0) {
    return "IMPOSSIBLE";
  }
  if (o && b - o == 0) {
    if (b + o < n) {
      return "IMPOSSIBLE";
    } else {
      string ans = "";
      for (int i = 0; i < b; ++i) {
        ans += "BO";
      }
      return ans;
    }
  }
  if (g && r - g == 0) {
    if (r + g < n) {
      return "IMPOSSIBLE";
    } else {
      string ans = "";
      for (int i = 0; i < r; ++i) {
        ans += "RG";
      }
      return ans;
    }
  }
  if (v && y - v == 0) {
    if (y + v < n) {
      return "IMPOSSIBLE";
    } else {
      string ans = "";
      for (int i = 0; i < y; ++i) {
        ans += "YV";
      }
      return ans;
    }
  }
  vector<pair<int, char>> vec;
  vec.push_back(make_pair(b - o, 'B'));
  vec.push_back(make_pair(r - g, 'R'));
  vec.push_back(make_pair(y - v, 'Y'));
  sort(vec.begin(), vec.end());
  if (vec[2].first > vec[0].first + vec[1].first) {
    return "IMPOSSIBLE";
  }
  string ans = "";
  int sum = vec[0].first + vec[1].first + vec[2].first;
  int cnt = sum - 2 * vec[2].first;
  for (int i = 0; i < vec[2].first; ++i) {
    ans += vec[2].second;
    if (i < vec[1].first) {
      ans += vec[1].second;
    } else {
      ans += vec[0].second;
    }
    if (i < cnt) {
      ans += vec[0].second;
    }
  }
  ins(ans, 'B', o, "OB");
  ins(ans, 'R', g, "GR");
  ins(ans, 'Y', v, "VY");
  return ans;
}

int main() {
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("B-small-attempt0.out", "w", stdout);

  int T;
  scanf("%d", &T);
  for (int test = 1; test <= T; ++test) {
    scanf("%d%d%d%d%d%d%d", &n, &r, &o, &y, &g, &b, &v);
    printf("Case #%d: %s\n", test, solve().c_str());
  }

  return 0;
}

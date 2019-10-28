
#include <algorithm>
#include <assert.h>
#include <bitset>
#include <climits>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <math.h>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef std::pair<int, int> pii;
template <typename T>
using min_heap = std::priority_queue<T, std::vector<T>, std::greater<T>>;
template <typename T>
using max_heap = std::priority_queue<T, std::vector<T>, std::less<T>>;
using namespace std;

int prev(int i, int n) {
  i--;
  if (i < 0)
    i += n;
  return i;
}

int next(int i, int n) { return (i + 1) % n; }

int add(int i, int v, int n) { return (i + v) % n; }

string no = "IMPOSSIBLE";

string solve(int n /*, int r, int o, int y, int g, int b, int v*/,
             vector<pair<int, char>> chrs) {
  sort(chrs.begin(), chrs.end(),
       [](pair<int, char> a, pair<int, char> b) -> bool {
         return a.first > b.first;
       });
  if (n == 1) {
    return chrs[0].second + "";
  }
  if (chrs[0].first > n / 2)
    return no;
  string s = "";
  for (int i = (0); i < (n); i++)
    s += " ";
  int idx = 0;
  int cnt = 0;
  for (int i = (0); i < (chrs.size()); i++) {
    for (int j = (0); j < (chrs[i].first); j++) {
      s[idx] = chrs[i].second;
      cnt++;
      if (j == chrs[i].first - 1)
        idx = add(idx, 1, n);
      else
        idx = add(idx, 2, n);
      if (cnt == n)
        break;
      while (s[idx] != ' ')
        idx = next(idx, n);
    }
  }
  return s;
  /*if (r > n / 2 || o > n / 2 || y > n / 2 || g > n / 2 || b > n / 2 || v > n /
  2) return no; string s = ""; FOR(i, 0, n) s += " "; int idx = 0, cnt = 0;
  FOR(i, 0, o)
  {
          s[idx] = 'O';
          if (s[prev(idx, n)] == 'B')
          {
                  r++;
                  cnt--;
          }
          if (s[next(idx, n)] == 'B')
          {
                  r++;
                  cnt--;
          }
          s[prev(idx, n)] = 'B';
          s[next(idx, n)] = 'B';
          cnt += 3;
          b -= 2;
          if (b < 0)
                  return no;
          if (cnt == n)
                  break;
          idx = add(idx, 2, n);
          while (!(s[idx] == ' ' && (s[prev(idx, n)] == ' ' || s[prev(idx, n)]
  == 'B') && (s[next(idx, n)] == ' ' || s[prev(idx, n)] == 'B'))) idx =
  next(idx, n);
  }
  FOR(i, 0, g)
  {
          s[idx] = 'G';
          if (s[prev(idx, n)] == 'R')
          {
                  r++;
                  cnt--;
          }
          if (s[next(idx, n)] == 'R')
          {
                  r++;
                  cnt--;
          }
          s[prev(idx, n)] = 'R';
          s[next(idx, n)] = 'R';
          cnt += 3;
          r -= 2;
          if (r < 0)
                  return no;
          if (cnt == n)
                  break;
          idx = add(idx, 2, n);
          while (!(s[idx] == ' ' && (s[prev(idx, n)] == ' ' || s[prev(idx, n)]
  == 'R') && (s[next(idx, n)] == ' ' || s[prev(idx, n)] == 'R'))) idx =
  next(idx, n);
  }
  FOR(i, 0, v)
  {
          s[idx] = 'V';
          if (s[prev(idx, n)] == 'Y')
          {
                  y++;
                  cnt--;
          }
          if (s[next(idx, n)] == 'Y')
          {
                  y++;
                  cnt--;
          }
          s[prev(idx, n)] = 'Y';
          s[next(idx, n)] = 'Y';
          cnt += 3;
          y -= 2;
          if (y < 0)
                  return no;
          if (cnt == n)
                  break;
          idx = add(idx, 2, n);
          while (!(s[idx] == ' ' && (s[prev(idx, n)] == ' ' || s[prev(idx,n)] ==
  'Y') && (s[next(idx, n)] == ' ' || s[next(idx, n)] == 'Y'))) idx = next(idx,
  n);
  }
  FOR(i, 0, r)
  {
          s[idx] = 'R';
          cnt++;
          if (cnt == n)
                  break;
          if (i == r - 1)
                  idx = next(idx, n);
          else
                  idx = add(idx, 2, n);
          while (s[idx] != ' ')
                  idx = next(idx, n);
  }
  FOR(i, 0, y)
  {
          s[idx] = 'Y';
          cnt++;
          if (cnt == n)
                  break;
          if (i == y - 1)
                  idx = next(idx, n);
          else
                  idx = add(idx, 2, n);
          while (s[idx] != ' ')
                  idx = next(idx, n);
  }
  FOR(i, 0, b)
  {
          s[idx] = 'B';
          cnt++;
          if (cnt == n)
                  break;
          if (i == b - 1)
                  idx = next(idx, n);
          else
                  idx = add(idx, 2, n);
          while (s[idx] != ' ')
                  idx = next(idx, n);
  }
  return s;*/
}

bool check(string s) {
  for (int i = (0); i < (s.length()); i++) {
    if (s[i] == s[(i + 1) % s.length()])
      return false;
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int NUMBER_OF_TESTS;
  cin >> NUMBER_OF_TESTS;
  for (int t = 1; t <= NUMBER_OF_TESTS; t++) {
    int n, r, o, y, g, b, v;
    cin >> n >> r >> o >> y >> g >> b >> v;
    vector<pair<int, char>> vv;
    vv.push_back({r, 'R'});
    vv.push_back({o, 'O'});
    vv.push_back({y, 'Y'});
    vv.push_back({g, 'G'});
    vv.push_back({b, 'B'});
    vv.push_back({v, 'V'});
    string ans = solve(n, vv);
    // string ans = solve(n, r, o, y, g, b, v);
    /*if (!check(ans))
    {
            cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
    }*/
    cout << "Case #" << t << ": " << ans << "\n";
  }
  return 0;
}

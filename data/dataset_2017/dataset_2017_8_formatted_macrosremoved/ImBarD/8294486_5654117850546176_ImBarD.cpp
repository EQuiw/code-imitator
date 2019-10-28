#include <algorithm>
#include <cstring>
#include <ctype.h>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef std::vector<int> vi;
typedef std::vector<bool> vb;
typedef std::vector<string> vs;
typedef std::vector<double> vd;
typedef std::vector<long long> vll;
typedef std::vector<std::vector<int>> vvi;
typedef vector<vvi> vvvi;
typedef vector<vll> vvll;
typedef std::vector<std::pair<int, int>> vpi;
typedef vector<vpi> vvpi;
typedef std::pair<int, int> pi;
typedef std::pair<ll, ll> pll;
typedef std::vector<pll> vpll;

const long long mod = 1000000007;
int main() {

  freopen("input.txt", "rt", stdin);
  freopen("output.txt", "wt", stdout);

  int t;
  scanf("%d", &t);
  for (int iad = 0; iad < t; iad++) {
    printf("Case #%d: ", iad + 1);
    int n;
    int r, o, y, g, b, v;
    string ans;
    cin >> n >> r >> o >> y >> g >> b >> v;
    if (r + y == 0) {
      if (g > 0 || v > 0 || b != o) {
        cout << "IMPOSSIBLE\n";
        continue;
      } else {
        for (int i = 0; i < b; i++)
          ans += "BO";
        cout << ans << endl;
        continue;
      }
    }
    if (r + b == 0) {
      if (g > 0 || o > 0 || y != v) {
        cout << "IMPOSSIBLE\n";
        continue;
      } else {
        for (int i = 0; i < y; i++)
          ans += "YV";
        cout << ans << endl;
        continue;
      }
    }
    if (b + y == 0) {
      if (o > 0 || v > 0 || r != g) {
        cout << "IMPOSSIBLE\n";
        continue;
      } else {
        for (int i = 0; i < g; i++)
          ans += "RG";
        cout << ans << endl;
        continue;
      }
    }
    r -= g;
    y -= v;
    b -= o;
    if (r < 0 || y < 0 || b < 0) {
      cout << "IMPOSSIBLE\n";
      continue;
    }
    if (r == 0 && g > 0) {
      cout << "IMPOSSIBLE\n";
      continue;
    }
    if (y == 0 && v > 0) {
      cout << "IMPOSSIBLE\n";
      continue;
    }
    if (b == 0 && o > 0) {
      cout << "IMPOSSIBLE\n";
      continue;
    }
    if (r + y < b || r + b < y || b + y < r) {
      cout << "IMPOSSIBLE\n";
      continue;
    }
    int cnt = r + y + b;
    ans = string(cnt, '.');
    int cur = 0;
    if (2 * r == cnt) {
      for (int i = 0; i < r; i++) {
        ans[2 * i] = 'R';
      }
      for (int i = 0; i < r; i++) {
        if (y > 0) {
          ans[2 * i + 1] = 'Y';
          y--;
        } else
          ans[2 * i + 1] = 'B';
      }
    } else if (2 * b == cnt) {
      for (int i = 0; i < b; i++) {
        ans[2 * i] = 'B';
      }
      for (int i = 0; i < b; i++) {
        if (y > 0) {
          ans[2 * i + 1] = 'Y';
          y--;
        } else
          ans[2 * i + 1] = 'R';
      }
    } else if (2 * y == cnt) {
      for (int i = 0; i < y; i++) {
        ans[2 * i] = 'Y';
      }
      for (int i = 0; i < y; i++) {
        if (r > 0) {
          ans[2 * i + 1] = 'R';
          r--;
        } else
          ans[2 * i + 1] = 'B';
      }
    } else {
      for (int i = 0; i < cnt; i++) {
        if (r > 0) {
          ans[cur] = 'R';
          r--;
        } else if (y > 0) {
          ans[cur] = 'Y';
          y--;
        } else if (b > 0) {
          ans[cur] = 'B';
          b--;
        }
        cur += 2;
        if (cur >= cnt)
          cur = 1;
      }
    }
    if (g > 0) {
      int k = 0;
      while (ans[k] != 'R')
        k++;
      string bef = ans.substr(0, k);
      string aft = ans.substr(k);
      for (int i = 0; i < g; i++)
        bef += "RG";
      ans = bef + aft;
    }
    if (v > 0) {
      int k = 0;
      while (ans[k] != 'Y')
        k++;
      string bef = ans.substr(0, k);
      string aft = ans.substr(k);
      for (int i = 0; i < v; i++)
        bef += "YV";
      ans = bef + aft;
    }
    if (o > 0) {
      int k = 0;
      while (ans[k] != 'B')
        k++;
      string bef = ans.substr(0, k);
      string aft = ans.substr(k);
      for (int i = 0; i < o; i++)
        bef += "BO";
      ans = bef + aft;
    }
    cout << ans << endl;
  }
}

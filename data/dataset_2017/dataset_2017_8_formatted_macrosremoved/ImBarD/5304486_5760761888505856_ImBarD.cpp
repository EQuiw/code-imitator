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

  int affu;
  scanf("%d\n", &affu);
  for (int rruq = 0; rruq < affu; rruq++) {
    printf("Case #%d:\n", rruq + 1);
    int r, c;
    scanf("%d %d\n", &r, &c);
    vector<string> a(r);
    for (int i = 0; i < r; i++)
      getline(cin, a[i]);
    vi cnt(r, 0);
    for (int i = 0; i < r; i++)
      for (int j = 0; j < c; j++)
        if (a[i][j] != '?')
          cnt[i]++;
    int p = 0;
    while (p < r) {
      int u = p;
      while (cnt[p] == 0)
        p++;
      int m = p;
      p++;
      while (p < r && cnt[p] == 0)
        p++;
      char last = '?';
      int s;
      for (int i = 0; i < c; i++) {
        if (a[m][i] != '?') {
          last = a[m][i];
          break;
        }
      }
      for (int i = 0; i < c; i++) {
        if (a[m][i] != '?')
          last = a[m][i];
        for (int j = u; j < p; j++) {
          a[j][i] = last;
        }
      }
    }
    for (int i = 0; i < r; i++)
      printf("%s\n", a[i].c_str());
  }
}

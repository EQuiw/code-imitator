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

#define all(c) (c).begin(), (c).end()
#define sz(c) (int)(c).size()
#define forn(i, a, b) for (int i = a; i < b; i++)

#define pb push_back
#define mp make_pair

int main() {
#ifndef ONLINE_JUDGE
  freopen("input.txt", "rt", stdin);
  freopen("output.txt", "wt", stdout);
#endif
  int affu;
  scanf("%d\n", &affu);
  forn(rruq, 0, affu) {
    printf("Case #%d:\n", rruq + 1);
    int r, c;
    scanf("%d %d\n", &r, &c);
    vector<string> a(r);
    forn(i, 0, r) getline(cin, a[i]);
    vi cnt(r, 0);
    forn(i, 0, r) forn(j, 0, c) if (a[i][j] != '?') cnt[i]++;
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
      forn(i, 0, c) {
        if (a[m][i] != '?') {
          last = a[m][i];
          break;
        }
      }
      forn(i, 0, c) {
        if (a[m][i] != '?')
          last = a[m][i];
        forn(j, u, p) { a[j][i] = last; }
      }
    }
    forn(i, 0, r) printf("%s\n", a[i].c_str());
  }
}

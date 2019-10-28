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
  int t;
  cin >> t;
  forn(aff, 0, t) {
    cout << "Case #" << aff + 1 << ": ";
    string s;
    int k;
    cin >> s >> k;
    int n = s.size();
    vi a(n, 1);
    forn(i, 0, n) if (s[i] == '-') a[i] = -1;

    vi flip(n + 1, 0);
    int cur = 1;
    bool can = true;
    int ans = 0;
    forn(i, 0, n) {
      if (flip[i])
        cur = -cur;
      if (cur * a[i] == -1) {
        if (i + k > n) {
          can = false;
        } else {
          flip[i + k] = 1;
          ans++;
          cur = -cur;
        }
      }
    }
    if (!can)
      cout << "IMPOSSIBLE\n";
    else
      cout << ans << endl;
  }
}

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
    ld d;
    int n;
    cin >> d >> n;
    ld maxt = 0;
    for (int i = 0; i < n; i++) {
      ld k, s;
      cin >> k >> s;
      maxt = max(maxt, (d - k) / s);
    }
    printf("%.10lf\n", (double)(d / maxt));
  }
}

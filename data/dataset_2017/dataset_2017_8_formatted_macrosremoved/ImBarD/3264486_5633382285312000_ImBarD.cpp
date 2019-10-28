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

  int t;
  cin >> t;
  for (int aff = 0; aff < t; aff++) {
    cout << "Case #" << aff + 1 << ": ";
    ll n;
    cin >> n;
    ll was = n;
    vi a;
    while (n > 0) {
      a.push_back(n % 10);
      n /= 10;
    }
    reverse((a).begin(), (a).end());
    int l = a.size();
    int d = -1;
    for (int i = 0; i < l - 1; i++) {
      if (a[i] > a[i + 1]) {
        d = i;
        break;
      }
    }
    if (d == -1) {
      cout << was << endl;
      continue;
    } else {
      for (int i = d + 1; i < l; i++)
        a[i] = 9;
      a[d]--;
      while (d > 0 && a[d] < a[d - 1]) {
        a[d] = 9;
        d--;
        a[d]--;
      }
    }
    int s = 0;
    while (a[s] == 0)
      s++;
    for (int i = s; i < l; i++)
      cout << a[i];
    cout << endl;
  }
}

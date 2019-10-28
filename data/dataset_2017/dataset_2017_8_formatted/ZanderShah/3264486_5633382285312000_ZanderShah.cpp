#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#define pb push_back
#define mp make_pair
#define l(x) x << 1
#define r(x) x << 1 | 1
#define scan(x)                                                                \
  do {                                                                         \
    while ((x = getchar()) < '0')                                              \
      ;                                                                        \
    for (x -= '0'; '0' <= (_ = getchar()); x = (x << 3) + (x << 1) + _ - '0')  \
      ;                                                                        \
  } while (0)
char _;
#define x first
#define y second

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<float, float> pff;
typedef pair<double, double> pdd;
typedef pair<ll, ll> pll;
typedef map<int, int> mii;
typedef unordered_map<int, int> umii;

int T, x[20];
string s;
bool b;

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);

  cin >> T;
  for (int r = 1; r <= T; r++) {
    cin >> s;
    for (int i = 0; i < s.length(); i++) {
      x[i] = s[i] - '0';
    }

    do {
      b = 0;
      for (int i = 0; i < s.length() - 1; i++) {
        if (x[i] > x[i + 1]) {
          x[i]--;
          for (i++; i < s.length(); i++) {
            x[i] = 9;
          }
          b = 1;
        }
      }
    } while (b);

    cout << "Case #" << r << ": ";
    for (int i = 0; i < s.length(); i++) {
      if (x[i] != 0) {
        cout << x[i];
      }
    }
    cout << endl;
  }
}

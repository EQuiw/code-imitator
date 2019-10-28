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
char _;

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<float, float> pff;
typedef pair<double, double> pdd;
typedef pair<ll, ll> pll;
typedef map<int, int> mii;
typedef unordered_map<int, int> umii;

int T, w, m;
string s;

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);

  cin >> T;
  for (int r = 1; r <= T; r++) {
    cin >> s >> w;
    m = 0;

    for (int i = 0; i < s.length() - w + 1; i++) {
      if (s[i] == '-') {
        for (int j = 0; j < w; j++) {
          s[i + j] = s[i + j] == '+' ? '-' : '+';
        }
        m++;
      }
    }

    for (int i = 0; i < s.length(); i++) {
      if (s[i] == '-') {
        m = -1;
      }
    }

    cout << "Case #" << r << ": ";
    if (m == -1) {
      cout << "IMPOSSIBLE" << endl;
    } else {
      cout << m << endl;
    }
  }
}

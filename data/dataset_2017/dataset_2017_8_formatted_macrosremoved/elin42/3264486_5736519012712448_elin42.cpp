#include <algorithm>
#include <climits>
#include <cmath>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<double> vd;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<char> vc;
typedef vector<vc> vvc;
typedef vector<string> vs;
typedef vector<vector<string>> vvs;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef vector<pii> vpii;
typedef vector<vpii> vvpii;
typedef set<int> si;
typedef vector<si> vsi;
using namespace std;
typedef unsigned int u32;

int main() {
  u32 T;
  cin >> T;
  for (u32 t = 1; t <= T; t++) {
    string s;
    cin >> s;
    int k;
    cin >> k;
    int total_flips = 0;
    bool valid = true;
    queue<int> recent_flips;
    for (int i = 0; i < s.size(); i++) {
      if (!recent_flips.empty() && i - recent_flips.front() >= k) {
        // cout << i << ", pop: " << recent_flips.front() << '\n';
        recent_flips.pop();
      }
      if ((s[i] == '+' && recent_flips.size() % 2 == 1) ||
          (s[i] == '-' && recent_flips.size() % 2 == 0)) {
        if (s.size() - i < k) {
          valid = false;
          break;
        }
        total_flips++;
        // cout << i << ", push: " << i << '\n';
        recent_flips.push(i);
      }
    }
    cout << "Case #" << t << ": ";
    if (valid) {
      cout << total_flips << '\n';
    } else {
      cout << "IMPOSSIBLE\n";
    }
  }
  return 0;
}

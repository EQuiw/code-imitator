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
#define mp make_pair
#define forf(i, n) for (int i = 0; i < n; i++)
#define forb(i, n) for (int i = n - 1; i >= 0; i--)
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

int main() {
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++) {
    string n;
    cin >> n;
    int const_streak_start = 0, prev = -1;
    bool done = false;
    for (int i = 0; i < n.size() && !done; i++) {
      if (n[i] < prev) {
        n[const_streak_start]--;
        for (int j = const_streak_start + 1; j < n.size(); j++) {
          n[j] = '9';
          done = true;
        }
      }
      if (n[i] != prev) {
        const_streak_start = i;
      }
      prev = n[i];
    }
    cout << "Case #" << t << ": ";
    n.erase(0, min(n.find_first_not_of('0'), n.size() - 1));
    cout << n << '\n';
  }
  return 0;
}

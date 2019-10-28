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
    int n, r, o, y, g, b, v;
    cin >> n >> r >> o >> y >> g >> b >> v;
    int n1, n2, n3;
    char c1, c2, c3;
    if (r >= y && r >= b) {
      n1 = r;
      c1 = 'R';
      if (y >= b) {
        n2 = y;
        c2 = 'Y';
        n3 = b;
        c3 = 'B';
      } else {
        n2 = b;
        c2 = 'B';
        n3 = y;
        c3 = 'Y';
      }
    } else if (y >= r && y >= b) {
      n1 = y;
      c1 = 'Y';
      if (r >= b) {
        n2 = r;
        c2 = 'R';
        n3 = b;
        c3 = 'B';
      } else {
        n2 = b;
        c2 = 'B';
        n3 = r;
        c3 = 'R';
      }
    } else {
      n1 = b;
      c1 = 'B';
      if (r >= y) {
        n2 = r;
        c2 = 'R';
        n3 = y;
        c3 = 'Y';
      } else {
        n2 = y;
        c2 = 'Y';
        n3 = r;
        c3 = 'R';
      }
    }
    cout << "Case #" << t << ": ";
    if (n1 > n2 + n3) {
      cout << "IMPOSSIBLE\n";
    } else {
      int ext = n2 + n3 - n1;
      forf(i, n1) {
        cout << c1;
        if (i < n2) {
          cout << c2;
        } else {
          cout << c3;
        }
        if (ext > 0) {
          cout << c3;
          ext--;
        }
      }
      cout << '\n';
    }
  }
  return 0;
}

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef vector<char> vc;
typedef vector<vc> vvc;
typedef vector<int> vi;
typedef vector<vi> vvi;

int main() {

  int t;
  cin >> t;
  int cas = 1;
  while (t--) {
    cout << "Case #" << cas << ": ";
    cas++;

    int n, r, o, y, g, b, v;
    cin >> n >> r >> o >> y >> g >> b >> v;

    string stable = "";
    bool impossible = false;
    char state;
    if (r > 0) {
      state = 'r';
      r--;
      stable = "R";
    } else if (y > 0) {
      state = 'y';
      y--;
      stable = "Y";
    } else if (b > 0) {
      state = 'b';
      b--;
      stable = "B";
    }

    while ((r > 0 || y > 0 || b > 0) && !impossible) {
      if (state == 'r') {
        if (y == 0 && b == 0) {
          impossible = true;
        } else if (y > b) {
          y--;
          state = 'y';
          stable += "Y";
        } else {
          b--;
          state = 'b';
          stable += "B";
        }
      } else if (state == 'y') {
        if (r == 0 && b == 0) {
          impossible = true;
        } else if (b > r) {
          b--;
          state = 'b';
          stable += "B";
        } else {
          r--;
          state = 'r';
          stable += "R";
        }
      } else if (state == 'b') {
        if (y == 0 && r == 0) {
          impossible = true;
        } else if (r > y) {
          r--;
          state = 'r';
          stable += "R";
        } else {
          y--;
          state = 'y';
          stable += "Y";
        }
      }
    }

    if (impossible) {
      cout << "IMPOSSIBLE" << endl;
    } else {
      if (stable[0] != stable[stable.size() - 1]) {
        cout << stable << endl;
      } else {
        // if ring condition not satisfied, attempt swapping last two
        if (stable[stable.size() - 1] != stable[stable.size() - 3]) {
          // three last unicorns are different colors, so swap
          char temp = stable[stable.size() - 2];
          stable[stable.size() - 2] = stable[stable.size() - 1];
          stable[stable.size() - 1] = temp;
          cout << stable << endl;
        } else {
          // swap would violate rules, so impossible
          cout << "IMPOSSIBLE" << endl;
        }
      }
    }
  }

  return 0;
}

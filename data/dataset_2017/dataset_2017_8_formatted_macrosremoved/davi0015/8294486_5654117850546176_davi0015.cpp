#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
typedef long long int ll;

int main() {
  int T;
  cin >> T;

  for (int i = 0; i < T; i++) {
    int n, r, o, y, g, b, v;
    cin >> n >> r >> o >> y >> g >> b >> v;

    bool possible = true;
    cout << "Case #" << i + 1 << ": ";
    // cout << (o < b) << (g < r) << (v < y) << (2 * max(max(b - o, r - g), y -
    // v) <= b - o + r - g + y - v) << endl;
    if (o + b == n && o == b) {
      for (int j = 0; j < o; j++) {
        cout << "OB";
      }
    } else if (g + r == n && g == r) {
      for (int j = 0; j < g; j++) {
        cout << "GR";
      }
    } else if (v + y == n && v == y) {
      for (int j = 0; j < v; j++) {
        cout << "VY";
      }
    } else if ((o == 0 || o < b) && (g == 0 || g < r) && (v == 0 || v < y) &&
               2 * max(max(b - o, r - g), y - v) <= b - o + r - g + y - v) {
      string temp;
      vector<string> sb, sr, sy;
      temp = "B";
      for (int j = 0; j < o; j++) {
        temp += "OB";
      }
      sb.push_back(temp);
      b -= o;
      for (int j = 0; j < b - 1; j++) {
        sb.push_back("B");
      }

      temp = "R";
      for (int j = 0; j < g; j++) {
        temp += "GR";
      }
      sr.push_back(temp);
      r -= g;
      for (int j = 0; j < r - 1; j++) {
        sr.push_back("R");
      }

      temp = "Y";
      for (int j = 0; j < v; j++) {
        temp += "VY";
      }
      sy.push_back(temp);
      y -= v;
      for (int j = 0; j < y; j++) {
        sy.push_back("Y");
      }

      string s;
      if (b >= r && b >= y) {
        for (int j = 0; j < b; j++) {
          s += sb[j];
          if (j < r)
            s += sr[j];
          if (j >= b - y)
            s += sy[j - b + y];
        }
      } else if (r >= b && r >= y) {
        for (int j = 0; j < r; j++) {
          s += sr[j];
          if (j < b)
            s += sb[j];
          if (j >= r - y)
            s += sy[j - r + y];
        }
      } else {
        for (int j = 0; j < y; j++) {
          s += sy[j];
          if (j < b)
            s += sb[j];
          if (j >= y - r)
            s += sr[j - y + r];
        }
      }

      cout << s;
    } else {
      cout << "IMPOSSIBLE";
    }
    cout << endl;
  }

  return 0;
}

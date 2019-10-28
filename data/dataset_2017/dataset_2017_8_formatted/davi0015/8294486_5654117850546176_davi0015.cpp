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

#define forn(I, N) for (int I = 0; I < N; I++)
#define fornd(I, N) for (int I = N - 1; I >= 0; I--)
#define forab(I, A, B) for (int I = A; I <= B; I++)
#define forabd(I, A, B) for (int I = B; I >= A; I--)
#define FOREACH(I, A)                                                          \
  for (__typeof__(A)::iterator I = A.begin(); I < A.end(); I++)
#define pb push_back
#define mp make_pair

typedef long long int ll;

int main() {
  int T;
  cin >> T;

  forn(i, T) {
    int n, r, o, y, g, b, v;
    cin >> n >> r >> o >> y >> g >> b >> v;

    bool possible = true;
    cout << "Case #" << i + 1 << ": ";
    // cout << (o < b) << (g < r) << (v < y) << (2 * max(max(b - o, r - g), y -
    // v) <= b - o + r - g + y - v) << endl;
    if (o + b == n && o == b) {
      forn(j, o) { cout << "OB"; }
    } else if (g + r == n && g == r) {
      forn(j, g) { cout << "GR"; }
    } else if (v + y == n && v == y) {
      forn(j, v) { cout << "VY"; }
    } else if ((o == 0 || o < b) && (g == 0 || g < r) && (v == 0 || v < y) &&
               2 * max(max(b - o, r - g), y - v) <= b - o + r - g + y - v) {
      string temp;
      vector<string> sb, sr, sy;
      temp = "B";
      forn(j, o) { temp += "OB"; }
      sb.pb(temp);
      b -= o;
      forn(j, b - 1) { sb.pb("B"); }

      temp = "R";
      forn(j, g) { temp += "GR"; }
      sr.pb(temp);
      r -= g;
      forn(j, r - 1) { sr.pb("R"); }

      temp = "Y";
      forn(j, v) { temp += "VY"; }
      sy.pb(temp);
      y -= v;
      forn(j, y) { sy.pb("Y"); }

      string s;
      if (b >= r && b >= y) {
        forn(j, b) {
          s += sb[j];
          if (j < r)
            s += sr[j];
          if (j >= b - y)
            s += sy[j - b + y];
        }
      } else if (r >= b && r >= y) {
        forn(j, r) {
          s += sr[j];
          if (j < b)
            s += sb[j];
          if (j >= r - y)
            s += sy[j - r + y];
        }
      } else {
        forn(j, y) {
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

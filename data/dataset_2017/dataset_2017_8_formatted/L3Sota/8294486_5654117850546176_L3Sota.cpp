// UNNECESSARY
// #include
// <chrono>//std::chrono::/system_clock/steady_clock/high_resolution_clock/duration
// #include
// <cstdio>//printf/scanf/fopen/fclose/fprintf/fscanf/snprintf/putc/puts/getc/gets
// #include <fstream>//ifstream/ofstream

// DATA STRUCTURES
#include <array>
#include <bitset>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <tuple>
#include <valarray>
#include <vector>

// MISCELLANEOUS
#include <algorithm> //min/max/sort(rand-access it)/merge
#include <cassert>
#include <climits> //INT_MAX/INT_MIN/ULLONG_MAX
#include <cmath> //fmin/fmax/fabs/sin(h)/cos(h)/tan(h)/exp/log/pow/sqrt/cbrt/ceil/floor/round/trunc
#include <cstdlib> //abs/atof/atoi/atol/atoll/strtod/strtof/..., srand/rand, calloc/malloc, exit, qsort
#include <iomanip> //setfill/setw/setprecision/fixed/scientific
#include <iostream> //cin/cout/wcin/wcout/left/right/internal/dec/hex/oct/fixed/scientific
#include <iterator>
#include <limits> //numeric_limits<type>::max/min/lowest/epsilon/infinity/quiet_NaN/signaling_NaN
#include <new>
#include <string> //stoi/stol/stoul/stoll/stoull/stof/stod/stold/to_string/getline
#include <utility> //pair

#ifndef REP
#define REP(i, n) for (int i = 0; i < n; ++i)
#endif

#ifndef REPST
#define REPST(i, n) for (size_t i = 0; i < n; ++i)
#endif

#ifndef READ
#define READ(x) std::cin >> x
#endif

typedef unsigned int ui;
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> pii;
typedef std::pair<ll, int> plli;
typedef std::pair<ull, int> puli;
typedef std::pair<double, int> pdi;
typedef std::pair<ll, ll> pllll;
typedef std::pair<ull, ull> pulul;
typedef std::pair<double, double> pdd;
typedef std::tuple<int, int, int> ti3;
typedef std::tuple<int, int, int, int> ti4;

const bool debug = true;

// --------------------------------------------------------------------------------------

using namespace std;

int main(void) {
  int t;
  cin >> t;
  REP(test, t) {
    int n;
    // red, ora, yel, gre, blu, vio
    int colors[6];
    char colorchars[6] = {'R', 'O', 'Y', 'G', 'B', 'V'};
    cin >> n;
    REP(i, 6) { cin >> colors[i]; }
    int red, ora, yel, gre, blu, vio;
    red = colors[0];
    ora = colors[1];
    yel = colors[2];
    gre = colors[3];
    blu = colors[4];
    vio = colors[5];

    string s(n, '?');
    // int* indices = new int[n];

    if (ora == 0 && gre == 0 && vio == 0) {
      int countmax = max({red, yel, blu});
      size_t argmax = 0;
      REP(i, 3) {
        if (countmax == colors[2 * i]) {
          argmax = 2 * i;
          break;
        }
      }
      REPST(pos, n) {
        s[pos] = colorchars[argmax];
        // indices[pos] = argmax;
        --colors[argmax];
        countmax = 0;
        if (pos < n - 1) {
          size_t next_argmax = 7;
          REP(i, 3) {
            if (2 * i == argmax) {
              continue;
            } else {
              if (countmax < colors[2 * i]) {
                countmax = colors[2 * i];
                next_argmax = 2 * i;
              }
            }
          }
          argmax = next_argmax;
          if (argmax == 7) {
            break;
          }
        }
      }
      if (argmax == 7) {
        s = "IMPOSSIBLE";
      } else if (s[0] == s[n - 1]) {
        if (n <= 3 || s[0] == s[n - 2] || s[n - 1] == s[n - 3]) {
          s = "IMPOSSIBLE";
        } else {
          char last = s[n - 1];
          char seco = s[n - 2];
          s[n - 1] = seco;
          s[n - 2] = last;
        }
      }
      cout << "Case #" << (test + 1) << ": " << s << '\n';
      // delete[] indices;
    } else {
      cout << "Case #" << (test + 1) << ": UNDEFINED" << '\n';
    }
  }

  return 0;
}

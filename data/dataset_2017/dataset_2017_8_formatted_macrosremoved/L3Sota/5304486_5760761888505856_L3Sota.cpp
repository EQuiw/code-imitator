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
  for (int test = 0; test < t; ++test) {
    int r, c;
    cin >> r >> c;
    vector<string> v;
    for (int i = 0; i < r; ++i) {
      string s;
      std::cin >> s;
      v.push_back(s);
    }
    vector<bool> vv;
    for (int i = 0; i < r; ++i) {
      string qq = string(c, '?');
      if (v[i] == qq) {
        vv.push_back(true);
      } else {
        vv.push_back(false);
        for (int j = 0; j < c; ++j) {
          bool found = false;
          if (v[i][j] == '?') {
            for (int jj = j + 1; jj < c; ++jj) {
              if (v[i][jj] != '?') {
                for (int jjj = j; jjj < jj; ++jjj) {
                  v[i][jjj] = v[i][jj];
                }
                found = true;
                break;
              }
            }
            if (!found) {
              for (int jj = j - 1; jj >= 0; --jj) {
                if (v[i][jj] != '?') {
                  for (int jjj = jj + 1; jjj <= j; ++jjj) {
                    v[i][jjj] = v[i][jj];
                  }
                  found = true;
                  break;
                }
              }
            }
          }
        }
      }
    }
    for (int i = 0; i < r; ++i) {
      if (vv[i]) {
        for (int ii = i + 1; ii < r; ++ii) {
          if (!vv[ii]) {
            for (int iii = i; iii < ii; ++iii) {
              v[iii] = v[ii];
            }
            vv[i] = true;
            break;
          }
        }
        if (vv[i]) {
          for (int ii = i - 1; ii >= 0; --ii) {
            if (!vv[ii]) {
              for (int iii = ii + 1; iii <= i; ++iii) {
                v[iii] = v[ii];
              }
              vv[i] = true;
              break;
            }
          }
        }
      }
    }

    cout << "Case #" << (test + 1) << ":\n";
    for (int i = 0; i < r; ++i)
      cout << v[i] << '\n';
  }
  return 0;
}

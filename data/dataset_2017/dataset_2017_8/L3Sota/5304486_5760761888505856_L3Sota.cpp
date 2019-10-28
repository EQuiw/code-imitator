// UNNECESSARY
// #include <chrono>//std::chrono::/system_clock/steady_clock/high_resolution_clock/duration
// #include <cstdio>//printf/scanf/fopen/fclose/fprintf/fscanf/snprintf/putc/puts/getc/gets
// #include <fstream>//ifstream/ofstream

// DATA STRUCTURES
#include <array>
#include <bitset>
#include <list>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <tuple>
#include <valarray>
#include <vector>

// MISCELLANEOUS
#include <algorithm>//min/max/sort(rand-access it)/merge
#include <cassert>
#include <climits>//INT_MAX/INT_MIN/ULLONG_MAX
#include <cmath>//fmin/fmax/fabs/sin(h)/cos(h)/tan(h)/exp/log/pow/sqrt/cbrt/ceil/floor/round/trunc
#include <cstdlib>//abs/atof/atoi/atol/atoll/strtod/strtof/..., srand/rand, calloc/malloc, exit, qsort
#include <iomanip>//setfill/setw/setprecision/fixed/scientific
#include <iostream>//cin/cout/wcin/wcout/left/right/internal/dec/hex/oct/fixed/scientific
#include <iterator>
#include <limits>//numeric_limits<type>::max/min/lowest/epsilon/infinity/quiet_NaN/signaling_NaN
#include <new>
#include <string>//stoi/stol/stoul/stoll/stoull/stof/stod/stold/to_string/getline
#include <utility>//pair

#ifndef REP
#define REP(i,n) for (int i = 0; i < n; ++i)
#endif

#ifndef REPST
#define REPST(i,n) for (size_t i = 0; i < n; ++i)
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

int main(void)
{
    int t;
    cin >> t;
    REP(test,t)
    {
        int r, c;
        cin >> r >> c;
        vector<string> v;
        REP(i,r) {string s; READ(s); v.push_back(s);}
        vector<bool> vv;
        REP(i,r)
        {
            string qq = string(c, '?');
            if (v[i] == qq) {
                vv.push_back(true);
            } else {
                vv.push_back(false);
                REP(j,c) {
                    bool found = false;
                    if (v[i][j] == '?') {
                        for (int jj = j+1; jj < c; ++jj) {
                            if (v[i][jj] != '?') {
                                for (int jjj = j; jjj < jj; ++jjj) {
                                    v[i][jjj] = v[i][jj];
                                }
                                found = true;
                                break;
                            }
                        }
                        if (!found) {
                            for (int jj = j-1; jj >= 0; --jj) {
                                if (v[i][jj] != '?') {
                                    for (int jjj = jj+1; jjj <= j; ++jjj) {
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
        REP(i,r)
        {
            if (vv[i]) {
                for (int ii = i+1; ii < r; ++ii) {
                    if (!vv[ii]) {
                        for (int iii = i; iii < ii; ++iii) {
                            v[iii] = v[ii];
                        }
                        vv[i] = true;
                        break;
                    }
                }
                if (vv[i]) {
                    for (int ii = i-1; ii >= 0; --ii) {
                        if (!vv[ii]) {
                            for (int iii = ii+1; iii <= i; ++iii) {
                                v[iii] = v[ii];
                            }
                            vv[i] = true;
                            break;
                        }
                    }
                }
            }
        }

        cout << "Case #" << (test+1) << ":\n";
        REP(i,r) cout << v[i] << '\n';
    }
    return 0;
}

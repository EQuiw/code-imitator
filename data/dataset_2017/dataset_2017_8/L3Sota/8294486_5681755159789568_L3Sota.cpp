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
        size_t n;
        int q;
        cin >> n >> q;
        vector<double> distv, speedv;
        REP(i,n) {
            double e, s;
            cin >> e >> s;
            distv.push_back(e);
            speedv.push_back(s);
        }
        double** distm = new double*[n];
        REP(i,n) {
            distm[i] = new double[n];
            REP(j,n) {
                cin >> distm[i][j];
            }
        }
        vector<int> starts, ends;
        REP(i,q) {
            int s, e;
            cin >> s >> e;
            --s; --e;
            starts.push_back(s);
            ends.push_back(e);
        }

        vector<double> dp(n, numeric_limits<double>::max());
        dp[0] = 0.0;
        REPST(i,n) { // start from i
            double disttotal = 0.0;
            for(size_t j = i+1; j < n; ++j) { // attempt to reach j
                disttotal += distm[j-1][j];
                if (disttotal > distv[i]) {
                    break;
                } else {
                    if (dp[j] > dp[i] + disttotal / speedv[i]) {
                        dp[j] = dp[i] + disttotal / speedv[i];
                    }
                }
            }
        }

        cout << setprecision(numeric_limits<double>::digits10 + 1);
        cout << "Case #" << (test+1) << ": " << dp.back() << '\n';
    }
    return 0;
}

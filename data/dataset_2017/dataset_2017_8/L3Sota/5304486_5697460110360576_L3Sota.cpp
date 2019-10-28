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
        int n, p;
        cin >> n >> p;
        vector<int> r;
        REP(i,n) {int temp; READ(temp); r.push_back(temp);}

        vector< vector<int> > count(n, vector<int>(1145141, 0));

        int smallest_num_servings = 1e6;
        int largest_num_servings = 1;

        int largest_q = 0;
        REP(ing,n) {
            int min_q = 1e6;
            int max_q = 0;
            REP(pack,p) {
                int q;
                READ(q);
                if (max_q < q) {
                    max_q = q;
                }
                if (min_q > q) {
                    min_q = q;
                }
                ++count[ing][q];
            }
            int smns = static_cast<int>(ceil(min_q / (r[ing] * 1.11)));
            int lans = static_cast<int>(floor(max_q / (r[ing] * 0.89)));
            if (smallest_num_servings > smns) {
                smallest_num_servings = smns;
            }
            if (largest_num_servings < lans) {
                largest_num_servings = lans;
            }
        }

        int kits = 0;
        for (int num_servings = smallest_num_servings; num_servings <= largest_num_servings; ++num_servings)
        {
            bool fulfilled = true;
            vector<int> erase;
            REP(ing,n)
            {
                int lower = static_cast<int>(ceil(r[ing]*num_servings*0.9));
                int higher = static_cast<int>(min(floor(r[ing]*num_servings*1.1), 1e6));
                int argmax = -1;
                int maxval = 0;
                for (int ind = lower; ind <= higher; ++ind) {
                    if (count[ing][ind] > maxval) {
                        maxval = count[ing][ind];
                        argmax = ind;
                    }
                }
                if (argmax == -1) {
                    fulfilled = false;
                    break;
                } else {
                    erase.push_back(argmax);
                }
            }
            if (fulfilled) {
                REP(j,n) {--count[j][erase[j]];}
                ++kits;
                --num_servings;
                if (kits == p) {
                    break;
                }
            }
        }

        cout << "Case #" << (test+1) << ": " << kits << '\n';
    }
    return 0;
}

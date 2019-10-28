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

const bool debug = false;

// --------------------------------------------------------------------------------------

// DECLARATIONS
template <typename T> void read(size_t n, T* a);
template <typename T> void read2(size_t n, size_t m, T** a);


// IMPLEMENTATIONS
template <typename T> void read(size_t n, T* a) {
    for (size_t i = 0; i < n; ++i) { std::cin >> a[i]; }
}

template <typename T> void read2(size_t n, size_t m, T** a) {
    for (size_t i = 0; i < n; ++i) {
        a[i] = new int[m];
        for (size_t j = 0; j < m; ++j) { std::cin >> a[i][j]; }
    }
}


using namespace std;

int main(void)
{
    ui t;
    cin >> t;
    for (ui test = 1; test <= t; ++test) {
        ull n; ull k;
        cin >> n >> k;
        queue<ull> q;
        q.push(n);
        q.push(n);
        ull count = 0;
        ull vsize = 2;
        vector<ull> v;
        while (count < k)
        {
            q.pop();
            ull qq = q.front();
            if (qq) {
                ++count;
                v.push_back(qq/2);
                v.push_back((qq-1)/2);
            }
            if (v.size() == vsize) {
                sort(v.begin(), v.end(), greater<ull>());
                for (size_t i = 0; i < v.size(); ++i) {
                    q.push(v[i]);
                }
                vsize *= 2;
                v = vector<ull>();
            }
        }
        ull qq = q.front();
        cout << "Case #" << test << ": " << (qq/2) << ' ' << ((qq-1)/2) << '\n';

    }

    return 0;
}

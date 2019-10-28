#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cmath>
#include <complex>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
typedef vector<int> vi; typedef vector<vector<int>> vvi; typedef vector<string> vs; typedef vector<double> vd;
typedef vector<vd> vvd; typedef long long ll; typedef vector<ll> vll; typedef vector<vll> vvll; typedef pair<int, int> pii;
#define all(v) begin(v), end(v)

#ifdef LOCAL
ifstream in("b.in");
#else
istream & in = cin;
#endif
//ostream & out = cout;
ofstream out("b.out");
template <class T> void read(T & t) { for (auto & x : t) in >> x; } template <class T> int sz(T const & t) { return (int)t.size(); }

int main() {
    ios_base::sync_with_stdio(false);
    int ntests; in >> ntests;
    for (int test = 1; test <= ntests; ++test) {        
        int n, p; in >> n >> p;
        vi r(n);
        for (int & x : r) in >> x;
        vvi q(n, vi(p));
        for (vi & v : q)
            for (int & x : v)
                in >> x;
        int res = 0;
        if (n == 1) {            
            for (int i = 0; i < p; ++i) {
                int x = q[0][i] / r[0];
                if (x > 0 && 10 * q[0][i] >= 9 * x * r[0] && 10 * q[0][i] <= 11 * x * r[0]) {
                    ++res;
                    continue;
                }
                ++x;
                if (10 * q[0][i] >= 9 * x * r[0] && 10 * q[0][i] <= 11 * x * r[0])
                    ++res;
            }
        } else {
            vi perm(p);
            for (int i = 0; i < p; ++i) perm[i] = i;
            do {
                int cur = 0;
                for (int i = 0; i < p; ++i) {
                    int h1 = 10 * q[0][i] / (9 * r[0]);
                    int l1 = (10 * q[0][i] - 1) / (11 * r[0]) + 1;
                    int h2 = 10 * q[1][perm[i]] / (9 * r[1]);
                    int l2 = (10 * q[1][perm[i]] - 1) / (11 * r[1]) + 1;
                    if (l1 <= h2 && l2 <= h1)
                        ++cur;
                    /*int x = q[0][i] / r[0];
                    if (x >= 0 && 
                        10 * q[0][i] >= 9 * x * r[0] && 10 * q[0][i] <= 11 * x * r[0] &&
                        10 * q[1][perm[i]] >= 9 * x * r[1] && 10 * q[1][perm[i]] <= 11 * x * r[1]) {
                        ++cur;
                        continue;
                    }
                    ++x;
                    if (10 * q[0][i] >= 9 * x * r[0] && 10 * q[0][i] <= 11 * x * r[0] &&
                        10 * q[1][perm[i]] >= 9 * x * r[1] && 10 * q[1][perm[i]] <= 11 * x * r[1])
                        ++cur;*/
                }
                res = max(res, cur);
            } while (next_permutation(all(perm)));
        }
        out << "Case #" << test << ": " << res << '\n';
    }
    return 0;
}

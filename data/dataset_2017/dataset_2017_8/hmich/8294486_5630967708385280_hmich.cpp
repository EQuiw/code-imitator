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
#pragma warning(disable : 4244 4267 4018 4996 4800)
//#pragma comment( linker, "/stack:10000000" )
using namespace std; 
typedef vector<int> vi; typedef vector<vi> vvi; typedef vector<string> vs; typedef vector<double> vd;
typedef vector<vd> vvd; typedef long long ll; typedef vector<ll> vll; typedef vector<vll> vvll; typedef pair<int, int> pii;
#define all(v) begin(v), end(v)

#ifdef LOCAL
ifstream in( "a.in" );
#else
istream & in = cin;
#endif
//ostream & out = cout;
ofstream out("a.out");
template <class T> void read(T & t) { for (auto & x : t) in >> x; } template <class T> int sz(T const & t) { return (int)t.size(); }

int main() {
    ios_base::sync_with_stdio(false);
    int ntests; in >> ntests;
    for (int test = 1; test <= ntests; ++test) {
        int d, n;
        in >> d >> n;
        //vi k(n), s(n);
        double t = 0;
        for (int i = 0; i < n; ++i) {
            int k, s;
            in >> k >> s;
            t = max(t, ((double)d - k) / s);
        }
        out.setf(ios::fixed);
        out.precision(10);
        out << "Case #" << test << ": " << d / t << '\n';
    }
    return 0;
}

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
        int r, c; in >> r >> c;
        vs v(r); vvi done(r, vi(c));
        for (int i = 0; i < r; ++i) {
            in >> v[i];
        }
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) if (!done[i][j]) {
                char ch = '?';
                int ii, jj, t;
                for (jj = j; jj < c; ++jj) if (v[i][jj] != '?')  {
                    if (ch == '?') ch = v[i][jj], t = i;
                    else break;
                }
                for (ii = i + 1; ii < r; ++ii) {
                    for (int k = j; k < jj; ++k) if (v[ii][k] != '?')  {
                        if (ch == '?') ch = v[ii][k], t = ii;
                        else {
                            if (t == ii)
                                jj = k;
                            goto done;
                        }
                    }
                }
                done: for (int x = i; x < ii; ++x)
                    for (int y = j; y < jj; ++y)
                        v[x][y] = ch, done[x][y] = 1;
            }
        }
        out << "Case #" << test << ": " << '\n';
        for (int i = 0; i < r; ++i)
            out << v[i] << '\n';
    }
    return 0;
}

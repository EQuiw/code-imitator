#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#include <unordered_set>
#include <unordered_map>

using namespace std;

#define all(c) ((c).begin()), ((c).end())
#define dump(c) cerr << "> " << #c << " = " << (c) << endl;
#define iter(c) __typeof((c).begin())
#define tr(i, c) for (iter(c) i = (c).begin(); i != (c).end(); i++)
#define REP(i, a, b) for (int i = a; i < (int)(b); i++)
#define rep(i, n) REP(i, 0, n)
#define mp make_pair
#define fst first
#define snd second
#define pb push_back
#define debug(fmt, ...) \
        fprintf( stderr, \
                  fmt "\n", \
                  ##__VA_ARGS__ \
        )

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<vi> vvi;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef vector<string> vs;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int INF = 1 << 30;
const double EPS = 1e-10;

double zero(double d) {
    return abs(d) < EPS ? 0.0 : d;
}

template<class T>
bool chmax(T &a, const T &b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

template<class T>
bool chmin(T &a, const T &b) {
    if (b < a) {
        a = b;
        return true;
    }
    return false;
}

#define UNIQUE(v) v.erase( unique(v.begin(), v.end()), v.end() );

template<typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &p) {
    return os << '(' << p.first << ',' << p.second << ')';
}

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &a) {
    os << '[';
    rep(i, a.size()) os << (i ? " " : "") << a[i];
    return os << ']';
}

string toString(int i) {
    stringstream ss;
    ss << i;
    return ss.str();
}

const int MOD = 1000000007;

// a^k
ll fpow(ll a, ll k, int M) {
    ll res = 1ll;
    ll x = a;
    while (k != 0) {
        if ((k & 1) == 1)
            res = (res * x) % M;
        x = (x * x) % M;
        k >>= 1;
    }
    return res;
}

struct prepare {
    prepare() {
        cout.setf(ios::fixed, ios::floatfield);
        cout.precision(8);
        ios_base::sync_with_stdio(false);
    }
} _prepare;


string solve() {
    int N;
    cin >> N;
    vi col(6);
    rep(i, 6) {
        cin >> col[i];
    }

//    rep(i, 6) {
//        if (i % 2 == 1) {
//            if (col[i] > 0 && col[i] >= col[(i + 3) % 6]) {
//                if (col[i] + col[(i + 3) % 6] != N)
//                    return "";
//            }
//        }
//    }
//
//    vi ryb(3, 0);
//    rep(i, 6) {
//        if(i % 2 == 0) {
//            ryb[i/2] += col[i];
//        }
//        else if(i % 2 == 1) {
//            ryb[(i+3) % 6] -= col[i];
//        }
//    }


    string s = "";
    vector<string> large(6, "");

    rep(_i, 3) {
        int i = _i * 2 + 1;
        int comp = (i + 3) % 6;
        if (i % 2 == 1 && col[i] > 0) {
            bool check = false;
            int sm = col[i] + col[comp];

            string su = "";

            while (col[i] > 0) {
                check = true;
                if (col[comp] <= 0) {
                    return "";
                }
                su += comp + '0';
                su += i + '0';
                col[i]--;
                col[comp]--;
            }

            if (check) {
                if (col[comp] <= 0 && sm != N) {
                    return "";
                }
                if(col[comp] > 0) {
                    su += comp + '0';
                    col[comp]--;
                }
            }

            large[comp] = su;
            col[comp]++;
        }
    }


    priority_queue< pair<int, pii> > que;
    rep(i, 3) {
        que.push(mp(col[i * 2], mp(col[i*2], i * 2)));
    }

    while (!que.empty()) {
        auto f = que.top();
        que.pop();

//        cout << " f: " << f << endl;

        if (f.first <= 0)
            break;

        s += f.second.second + '0';
        f.first--;

        auto sec = que.top();
        que.pop();

//        cout << " s: " << sec << endl;

        if (sec.first > 0) {
            s += sec.second.second + '0';
            sec.first--;
        }

        que.push(f);
        que.push(sec);
    }

//    cout << s << endl;
//    rep(i, 3) {
//        cout << i << " " << large[i] << endl;
//    }

    vector<string> strcol = {"R", "O", "Y", "G", "B", "V"};
    string ans = "";
    rep(i, s.size()) {
        int ci = (s[i] - '0');
        if (large[ci] != "") {
            tr(it, large[ci]) {
                ans += strcol[(*it - '0')];
            }
            large[ci] = "";
        } else {
            ans += strcol[ci];
        }
    }
//
//    cout << "  ans: " << ans << endl;

    if(ans.size() == 1)
        return "";

    rep(i, N) {
        char s = ans[i];
        char e = ans[(i+1) % N];

        rep(i, 2) {
            if(s == 'R') {
                if(e == 'R' || e == 'O' || e == 'V')
                    return "";
            }
            if(s == 'B') {
                if(e == 'B' || e == 'G' || e == 'V')
                    return "";
            }
            if(s == 'Y') {
                if(e == 'Y' || e == 'O' || e == 'G')
                    return "";
            }

            swap(s, e);
        }
    }

    return ans;
}

int main() {
    int T;
    cin >> T;
    rep(_t, T) {
        cout << "Case #" << (_t + 1) << ": ";
        string ans = solve();
        if (ans == "") {
            cout << "IMPOSSIBLE";
        } else {
            cout << ans;
        }
        cout << endl;
    }
    return 0;
}


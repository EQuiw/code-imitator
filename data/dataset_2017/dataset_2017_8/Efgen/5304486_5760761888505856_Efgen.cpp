// @formatter:off
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef vector<vector<int> > vvi;
typedef vector<ll> vl;
typedef vector<vector<ll> > vvl;
#define forn(i,n) for(int i=0;i<(n);++i)
#define forv(i,v) forn(i,sz(v))
#define all(v) v.begin(), v.end()
#define mp make_pair
#define pb push_back
#define X first
#define Y second
template<class T> inline T sqr(T x) { return x * x; }
template<class T> inline T parse(const string&s){T x;stringstream ss(s);ss>>x;return x;}
int gcd(int a,int b){return a?gcd(b%a,a):b;}
ll gcd(ll a,ll b){return a?gcd(b%a,a):b;}
ll powmod(ll a,ll p,ll m){ll r=1;while(p){if(p&1)r=r*a%m;p>>=1;a=a*a%m;}return r;}
// @formatter:on


void solveTest() {
    int n, m;
    cin >> n >> m;
    vector<string> a(n);
    vector<bool> f(n);
    forn(i, n) {
        cin >> a[i];
    }
    string sv = "";
    forn(i, m) sv += "?";
    forn(i, n) {
        if (a[i] == sv) {
            f[i] = true;
            continue;
        }
        int p = 0;
        forn(j, m) {
            if (a[i][j] == '?') {
                if (p == 0) {
                    while (p < m && a[i][p] == '?') p++;
                }
            } else {
                p = j;
            }
            a[i][j] = a[i][p];
        }
    }
    int p = 0;
    forn(i, n) {
        if (f[i]) {
            if (p == 0) {
                while (p < n && f[p]) p++;
            }
        } else {
            p = i;
        }
        a[i] = a[p];
    }
    //cout << endl;
    forn(i, n) {
        cout << endl << a[i];
    }
}

int main() {
#ifdef EFGEN_DBG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int tests;
    cin >> tests;
    for (int test = 1; test <= tests; test++) {
        cout << "Case #" << test << ": ";
        solveTest();
        cout << endl;
    }
}

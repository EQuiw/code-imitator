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

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define forv(i, v) forn(i, v.size())
#define all(v) v.begin(), v.end()
#define mp make_pair
#define pb push_back


int main() {
    int tests;
    cin >> tests;
    for (int test = 1; test <= tests; test++) {
        cout << "Case #" << test << ": ";
        string s;
        int k;
        cin >> s >> k;
        int n = s.size();
        vector<bool> a(n);
        forn(i, n) a[i] = s[i] == '+';
        int res = 0;
        forn(i, n - k + 1) {
            if (!a[i]) {
                res++;
                forn(j, k) {
                    a[i + j] = !a[i + j];
                }
            }
        }
        bool ok = true;
        forn(i, k) ok &= a[n - i - 1];
        if (ok) cout << res; else cout << "IMPOSSIBLE";
        cout << endl;
    }

}

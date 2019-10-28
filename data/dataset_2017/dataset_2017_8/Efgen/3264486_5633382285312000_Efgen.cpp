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
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int tests;
    cin >> tests;
    for (int test = 1; test <= tests; test++) {
        cout << "Case #" << test << ": ";
        string s;
        cin >> s;
        int n = s.size();
        int pos = n;
        for (int i = 1; i < n; i++) {
            if (s[i] < s[i - 1]) {
                pos = i - 1;
                while (pos > 0 && s[pos - 1] == s[pos]) pos--;
                if (s[pos] == '1') {
                    s = "";
                    forn(j, n - 1) s += "9";
                } else {
                    s[pos]--;
                    for (int j = pos + 1; j < n; j++) s[j] = '9';
                }
                break;
            }
        }
        cout << s << endl;
    }

}

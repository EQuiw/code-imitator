#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;
using vvl = vector<vl>;
using pll = pair<ll,ll>;
using vb = vector<bool>;
const ll oo = 0x3f3f3f3f3f3f3f3fLL;
const double eps = 1e-9;
#define	sz(c) ll((c).size())
#define	all(c) begin(c),end(c)
#define	mp make_pair
#define mt make_tuple
#define	pb push_back
#define eb emplace_back
#define xx first
#define yy second
#define	has(c,i) ((c).find(i) != end(c))
#define FOR(i,a,b) for (ll i = (a); i < (b); i++)
#define	FORD(i,a,b) for (ll i = (b)-1; i >= (a); i--)

int main(){
	ios::sync_with_stdio(false);
    ll TC;
    cin >> TC;
    FOR(tc,1,TC+1){
        double d, n;
        cin >> d >> n;
        vl k(n), s(n);
        double a = 0;
        FOR(i,0,n){
          cin >> k[i] >> s[i];
          a = max(a, (d-k[i])/s[i]);
        }
        cout << "Case #" << tc << ": " << setprecision(8) << fixed << d/a << endl;
    }
}

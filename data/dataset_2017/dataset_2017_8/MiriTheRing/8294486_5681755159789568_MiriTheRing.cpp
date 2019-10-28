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
        cout << "Case #" << tc << ": ";
        ll n, q;
        cin >> n >> q;
        vector<double> e(n), s(n);
        FOR(i,0,n){
          cin >> e[i] >> s[i];
        }
        vector<vl> d(n, vl(n));
        vector<vector<double>> t(n, vector<double>(n, oo));
        FOR(i,0,n){
          FOR(j,0,n){
            cin >> d[i][j];
            if(d[i][j] == -1){
              d[i][j] = oo;
            }
          }
        }

        FOR(k,0,n){
          FOR(i,0,n){
            FOR(j,0,n){
              if(d[i][j] > d[i][k] + d[k][j]){
                d[i][j] = d[i][k] + d[k][j];
              }
            }
          }
        }
        
        FOR(i,0,n){
          FOR(j,0,n){
            if(d[i][j] <= e[i]){
              t[i][j] = d[i][j]/s[i];
            }
          }
        }

        FOR(k,0,n){
          FOR(i,0,n){
            FOR(j,0,n){
              if(t[i][j] > t[i][k] + t[k][j]){
                t[i][j] = t[i][k] + t[k][j];
              }
            }
          }
        }
        

        FOR(i,0,q){
          ll u, v;
          cin >> u >> v;
          cout << setprecision(8) << fixed <<  t[u-1][v-1] << " ";
        }
        cout << endl;
    }
}

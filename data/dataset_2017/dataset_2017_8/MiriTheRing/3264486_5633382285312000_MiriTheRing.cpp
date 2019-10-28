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

bool tidy(string a){
  FOR(i,1,sz(a)){
    if(a[i-1] > a[i]) return false; 
  }
  return true;
}

int main(){
	ios::sync_with_stdio(false);
  vl nums = {1,2,3,4,5,6,7,8,9};
  vl swap;
  FOR(l,2,19){
    swap = vl();
    FOR(i,1,10){
      FORD(j,0,sz(nums)){
        if(sz(to_string(nums[j])) < l-1)
          break;
        char c = ('0' + i);
        string num = to_string(nums[j]);
        num += c;
        if(tidy(num)){
          swap.pb(stoll(num));
        }
      }
    }
    FOR(i,0,sz(swap)) nums.pb(swap[i]);
  }
  sort(all(nums));
  ll TC;
  cin >> TC;
  FOR(tc,0,TC){
    ll n;
    cin >> n;
    auto ptr = upper_bound(all(nums), n);
    ptr--;
    cout << "Case #" << tc+1 << ": " << *ptr << endl;
  }
}

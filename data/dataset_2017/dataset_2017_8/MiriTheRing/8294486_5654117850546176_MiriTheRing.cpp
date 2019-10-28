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

map<ll, char> m = {{0,'R'}, {1,'O'}, {2,'Y'}, {3, 'G'}, {4, 'B'}, {5, 'V'}};

int main(){
  ios::sync_with_stdio(false);
  ll TC;
  cin >> TC;
  FOR(tc,1,TC+1){
    cout << "Case #" << tc << ": ";
    vector<pll> nums;
    ll n, last = 0;
    ll first;
    cin >> n;
    bool poss = true;
    FOR(i,0,6){
      ll k;
      cin >> k;
      nums.pb(mp(k, i));
    }
    sort(nums.rbegin(), nums.rend());
    if(nums[0].xx > (n)/2){
      poss = false;
    }
    string res = "";
    FOR(i,0,n){
      res += "R";
    }
    ll idx = 0;
    FOR(i,0,sz(nums)){
      while(nums[i].xx){
        res[idx] = m[nums[i].yy];
        nums[i].xx--;
        idx += 2;
        if(idx >= n) idx = 1;
      }
    }
    
    /*
    string res = "";
    res += m[last];
    first = last;
    num[last]--;
    FOR(i,1,n){
      ll next_idx = -1;
      ll next_num = 0;
      FOR(j,last+2, last+5){
        if(num[j%6] > next_num){
          next_num = num[j%6];
          next_idx = j%6;
        }
      }
      if(next_idx == -1){
        poss = false;
        break;
      }
      last = next_idx;
      res += m[last];
      num[last]--;
    }
    
    if(poss){
      poss = false;
    FOR(j, last+2, last+5){
      if(j == first) poss = true;
    }
    }
    cerr << res << endl;
    */
    if(poss)
      cout << res << endl;
    else
      cout << "IMPOSSIBLE" << endl;
    
  }
}

#include <map>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <list>
#include <cmath>
#include <stack>
#include <queue>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <algorithm>
#include <assert.h>
#include <functional>
#define _USE_MATH_DEFINES
#include <math.h>
#include <complex>
using namespace std;
#if 1
#define ll long long
#else
#define ll int
#endif
#define ld double
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pb push_back
#define ft first
#define sd second
#define rep(i,n) for(int i=0;i<(int)(n);++i)
#define FOR(i,b,e) for(int i=b;i<=(int)(e);++i)
#define FORR(i,b,e) for(int i=b;i>=(int)(e);--i)
#define Fill(a,b) memset(a,b,sizeof(a))
#define all(a) a.begin(),a.end()
template<typename T1, typename T2> void Max(T1& a, T2 b) {a=max(a, (T1)b);}
template<typename T1, typename T2> void Min(T1& a, T2 b) {a=min(a, (T1)b);}

const int inf = 1e9;
const int N = 1000;

pll f[2][2];

void solve() {
  ll n, k;
  cin >> n >> k;
  int c = 0;
  f[0][0].ft = n;
  f[0][0].sd = 1;
  f[0][1].ft = f[0][1].sd = 0;
  while (1) {
    if (f[c][0].sd + f[c][1].sd >= k) {
      ll t = f[c][0].sd >= k ? f[c][0].ft:f[c][1].ft;
      t--;
      ll ans1 = (t + 1) / 2;
      ll ans2 = t / 2;
      cout << ans1 << ' ' << ans2 << endl;
      break;
    }
    k -= f[c][0].sd + f[c][1].sd;
    Fill(f[!c], 0);
    ll t1 = f[c][0].ft - 1;
    ll t2 = (t1 + 1) / 2;
    ll t3 = t1 / 2;
    f[!c][0] = pll(t2, f[c][0].sd);
    if (t3 == t2) {
      f[!c][0].sd *= 2;
    }
    else
      f[!c][1] = pll(t3, f[c][0].sd);
    if (f[c][1].sd) {
      t1 = f[c][1].ft - 1;
      t2 = (t1 + 1) / 2;
      t3 = t1 / 2;
      if (t2 == t3) {
        f[!c][1].sd += 2 * f[c][1].sd;
      }
      else {
        f[!c][0].sd += f[c][1].sd;
        f[!c][1] = pll(t3,f[c][1].sd);
      }
    }
    c = !c;
  }
  
  
}

void init() {
  
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(0);
  //freopen("C:\\Users\\LENOVO\\Documents\\Visual Studio 2015\\Projects\\Test\\Input\\in.in", "r", stdin);

  init();
  int T; cin >> T;
  FOR(TI,1,T) {
    cout << "Case #" << TI << ": ";
    //cout << "Case " << TI << ": ";
    solve();
  }
 
  
  return 0;
}

#include <map>
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
using namespace std;
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pb push_back
#define ft first
#define sd second
#define rep(i,n) for(ll i=0;i<(n);++i)
#define FOR(i,b,e) for(ll i=b;i<=(e);++i)
#define FORR(i,b,e) for(ll i=b;i>=(e);--i)
#define Fill(a,b) memset(a,b,sizeof(a))
#define all(a) a.begin(),a.end()
template<typename T1, typename T2> void Max(T1& a, T2 b) { a = max(a, (T1)b); }
template<typename T1, typename T2> void Min(T1& a, T2 b) { a = min(a, (T1)b); }


const double inf = 1e11;
const int N = 100;

double d[N][N];
double e[N], s[N];
double memo[N][N];
double dsum[N];
ll n;

double go(int i, int horse) {
  double& ret = memo[i][horse];
  if (ret > 0)return ret;
  if (i == n - 1) return 0;
  ret = inf;
  double horse_dis = dsum[i + 1] - dsum[horse];
  if (e[horse] >= horse_dis) {
    Min(ret, d[i][i + 1]/s[horse] + go(i + 1, horse));
  }
  if (e[i] >= d[i][i + 1]) {
    Min(ret, d[i][i+1]/s[i] + go(i + 1, i));
  }
  if (ret < inf) {
    //cout << "ok " << i << " " << horse <<" "<<ret<< endl;
  }
  return ret;
}


void solve() {
  ll q;
  cin >> n >> q;
  rep(i, n)cin >> e[i] >> s[i];
  rep(i, n)rep(j, n)cin >> d[i][j];
  dsum[0] = 0;
  FOR(i, 1, n - 1)dsum[i] = dsum[i - 1] + d[i - 1][i];
  while (q--) {
    ll u, v;
    cin >> u >> v;
    Fill(memo, 0);
    double ans = go(0, 0);
    cout << setprecision(8) << ans << endl;

    rep(i, n-1) {
      bool fd = 0;
      rep(j, n)if (memo[i][j] > 0 && memo[i][j] < inf) {
        fd = 1;
        break;
      }
      if (!fd) {
        cout << "bad " << i << endl;
      }
    }
  }
}

void init() {
  
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(0);
  //freopen("C:\\Users\\LENOVO\\Documents\\Visual Studio 2015\\Projects\\Test\\Input\\in.in", "r", stdin);

  init();
  int T; cin >> T;
  FOR(TI, 1, T) {
    cout << "Case #" << TI << ": ";
    //cout << "Case " << TI << ": ";
    solve();
  }
  

  return 0;
}

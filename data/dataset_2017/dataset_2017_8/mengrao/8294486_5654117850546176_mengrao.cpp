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


const int inf = 1e9;
const int N = 1000;

ll a[6]; // R, O, Y, G, B, V
        // R, B, Y


void solve() {
  ll n;
  cin >> n;
  rep(i, 6)cin >> a[i];
  rep(i, 6)if (a[i] * 2 > n) {
    cout << "IMPOSSIBLE" << endl;
    return;
  }
  int nvar = 0;
  rep(i, 6) nvar += a[i] > 0;
  if (a[1] && a[1] + (nvar > 2)> a[4]) {
    cout << "IMPOSSIBLE" << endl;
    return;
  }
  if (a[3] && a[3] + (nvar > 2)> a[0]) {
    cout << "IMPOSSIBLE" << endl;
    return;
  }
  if (a[5] && a[5] + (nvar > 2)> a[2]) {
    cout << "IMPOSSIBLE" << endl;
    return;
  }
  string ans;
  if (a[1]) {
    rep(it, a[1]) {
      ans += "BO";
      a[4]--;
    }
    if (nvar > 2) {
      ans += "B";
      a[4]--;
    }
  }
  if (a[3]) {
    rep(it, a[3]) {
      ans += "RG";
      a[0]--;
    }
    if (nvar > 2) {
      ans += "R";
      a[0]--;
    }
  }
  if (a[5]) {
    rep(it, a[5]) {
      ans += "YV";
      a[2]--;
    }
    if (nvar > 2) {
      ans += "Y";
      a[2]--;
    }
  }
  a[1] = a[4];
  n = a[0] + a[1] + a[2];
  while (n > 0) {
    char back = ans.empty() ? 'N' : ans.back();
    char front = ans.empty() ? 'N' : ans.front();
    if (back == 'R') {
      if (a[1] > a[2]) ans += 'B', a[1]--;
      else if (a[2] > a[1]) ans += 'Y', a[2]--;
      else {
        if (a[1] == 0) {
          cout << "IMPOSSIBLE" << endl;
          return;
        }
        if (front == 'B')ans += 'B', a[1]--;
        else ans += 'Y', a[2]--;
      }
    }
    if (back == 'B') {
      if (a[0] > a[2]) ans += 'R', a[0]--;
      else if (a[2] > a[0]) ans += 'Y', a[2]--;
      else {
        if (a[0] == 0) {
          cout << "IMPOSSIBLE" << endl;
          return;
        }
        if (front == 'R')ans += 'R', a[0]--;
        else ans += 'Y', a[2]--;
      }
    }
    if (back == 'Y') {
      if (a[0] > a[1]) ans += 'R', a[0]--;
      else if (a[1] > a[0]) ans += 'B', a[1]--;
      else {
        if (a[0] == 0) {
          cout << "IMPOSSIBLE" << endl;
          return;
        }
        if (front == 'R')ans += 'R', a[0]--;
        else ans += 'B', a[1]--;
      }
    }
    if (back == 'N') {
      int best = 0;
      if (a[1] > a[best]) best = 1;
      if (a[2] > a[best]) best = 2;
      if (best == 0) ans += 'R', a[0]--;
      else if (best == 1) ans += 'B', a[1]--;
      else ans += 'Y', a[2]--;
    }
    n--;
  }
  if (ans.back() == ans.front()) {
    cout << "IMPOSSIBLE" << endl;
    return;
  }
  cout << ans << endl;

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

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

void solve() {
  string str;
  int k;
  cin >> str >> k;
  int n = str.size();
  int ans = 0;
  rep(i, n - k + 1) if(str[i]=='-') {
    ans++;
    FOR(j, i + 1, i + k - 1) {
      if (str[j] == '-')str[j] = '+';
      else str[j] = '-';
    }
  }
  FOR(i, n - k + 1, n - 1)if (str[i] == '-') {
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
  FOR(TI,1,T) {
    cout << "Case #" << TI << ": ";
    //cout << "Case " << TI << ": ";
    solve();
  }
 
  
  return 0;
}

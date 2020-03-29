// Hi
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
using namespace std;
typedef long long ll;
void solve() {
  int n, p;
  int mods[4];
  for (int i = 0; i < 4; i++)
    mods[i] = 0;
  cin >> n >> p;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    mods[x % p]++;
  }
  /*
  int ans=mods[0];
  if(p==2) ans+=mods[1]/2;
  if(p==3) {
      int x = min(mods[1],mods[2]);
      ans += x;
      mods[1]-=x;
      mods[2]-=x;


  }
  if(p==4) ans+= mods[2]/2 + min(mods[1],mods[3]);
  cout<<min(n,ans+1)<<endl;
   */
  int ans = mods[0];
  int numLeft = n - mods[0];
  while (numLeft) {
    ans++;
    if (p == 2) {
      if (mods[1] >= 2) {
        mods[1] -= 2;
        numLeft -= 2;
      } else {
        break;
      }
    }
    if (p == 3) {
      if (mods[1] && mods[2]) {
        mods[1]--;
        mods[2]--;
        numLeft -= 2;
      } else if (mods[1] >= 3) {
        mods[1] -= 3;
        numLeft -= 3;
      } else if (mods[2] >= 3) {
        mods[2] -= 3;
        numLeft -= 3;
      } else {
        break;
      }
    }
  }
  cout << ans << endl;
}
int main() {
  ios::sync_with_stdio(false);
  freopen("test.txt", "r", stdin);
  freopen("test1.txt", "w", stdout);
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++) {
    cout << "Case #" << i << ": ";
    solve();
  }
}

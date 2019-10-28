#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
typedef pair<ll, ll> PLL;
int r[110];
int q[110][110];
int qL[110][110];
int qR[110][110];
int num[110][110];
int dp[110];
priority_queue<PII, vector<PII>, greater<PII>> pq[110];
int main() {
  ios::sync_with_stdio(0);
  freopen("1.in", "r", stdin);
  freopen("out.txt", "w", stdout);
  int cas = 1;
  int t;
  cin >> t;
  while (t--) {
    cout << "Case #" << cas++ << ": ";
    int n, p;
    cin >> n >> p;
    for (int i = 0; i < n; i++) {
      cin >> r[i];
    }
    // cout << endl << "############" << endl;
    for (int i = 0; i < 110; i++) {
      while (!pq[i].empty()) {
        pq[i].pop();
      }
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < p; j++) {
        cin >> q[i][j];
        int L = 0, R = 1000010;
        qL[i][j] = R, qR[i][j] = 0;
        while (L <= R) {
          int mid = (L + R) / 2;
          ll tot = 1LL * mid * r[i];
          if (tot * 0.9 - 1e-5 < q[i][j]) {
            qR[i][j] = max(qR[i][j], mid);
            L = mid + 1;
          } else {
            R = mid - 1;
          }
        }
        L = 0, R = 1000010;
        while (L <= R) {
          int mid = (L + R) / 2;
          ll tot = 1LL * mid * r[i];
          if (tot * 1.1 + 1e-5 > q[i][j]) {
            qL[i][j] = min(qL[i][j], mid);
            R = mid - 1;
          } else {
            L = mid + 1;
          }
        }
        // cout << "(" << qL[i][j]<< "  " << qR[i][j] << ")";
        if (qR[i][j] < qL[i][j]) {
          qR[i][j] = qL[i][j] = 0;
        } else {
          pq[i].push(make_pair(qL[i][j], qR[i][j]));
        }
      }
      // cout << endl;
    }
    // cout << "#########" << endl;
    int ans = 0;
    PII tmp[51];
    bool can = 1;
    while (can) {
      int minr = 1000010, maxl = -1;
      for (int i = 0; i < n; i++) {
        if (pq[i].empty()) {
          can = 0;
        } else {
          tmp[i] = pq[i].top();
          minr = min(minr, tmp[i].second);
          maxl = max(maxl, tmp[i].first);
        }
      }
      if (!can)
        break;
      // cout << maxl << " " << minr << endl;
      if (maxl <= minr) {
        ans++;
        for (int i = 0; i < n; i++) {
          pq[i].pop();
        }
      } else {
        for (int i = 0; i < n; i++) {
          if (tmp[i].second == minr)
            pq[i].pop();
        }
      }
    }
    /*if(n == 1){
      for(int i = 0 ; i < p ; i ++){
        ans += qR[0][i];
      }
    }else if(n == 2 && p <= 8){
      int a[8] = {0,1,2,3,4,5,6,7};
      do{
        int cur = 0;
        for(int i  = 0; i < p;  i++){
          if(qR[0][i] < qL[1][a[i]] || qL[0][i] > qR[1][a[i]])continue;
          cur ++;
        }
        ans = max(cur,ans);
      }while(next_permutation(a,a+8));
    }*/
    /*for(int j = 0; j < p ; j ++){
      int cur = num[0][j];
      bool can = true;
      for(int i = 0 ; i < n ; i++){
        bool ok = false;
        for(int k = 0 ; k < p ; k ++){
          if(cur == num[i][k]){
            dp[i] = k;
            ok = true;
          }
        }
        if(!ok){
          can = false;
        }
      }
      if(can){
        ans += cur;
        for(int i = 0 ; i < n ; i++){
          num[i][dp[i]] = -1;
        }
      }
    }*/
    cout << ans << endl;
  }
  return 0;
}

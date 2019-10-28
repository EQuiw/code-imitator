#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stdlib.h>
#include <string.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

typedef long long ll;

#define FOR(i, n) for (int i = 0; i < n; i++)
#define out(a)                                                                 \
  for (auto i : a)                                                             \
    cout << i << " ";
#define outl(a)                                                                \
  for (auto i : a)                                                             \
    cout << i << endl;

vector<vector<ll>> tree;

int main() {
  freopen("/Users/shitian/Downloads/B-small-attempt5.in", "r", stdin);
  freopen("/Users/shitian/Downloads/B-small-attempt5.txt", "w", stdout);
  int tcase;
  cin >> tcase;
  for (int tc = 1; tc <= tcase; tc++) {
    cout << "Case #" << tc << ": ";

    int n, p; // ingredients, packages
    cin >> n >> p;
    int r[101];
    FOR(i, n) cin >> r[i];
    int q[100][100];
    FOR(i, n) FOR(j, p) cin >> q[i][j];
    vector<pair<int, int>>
        amount[100]; // amount[i][j]: ingredient[i] has amount[i][j]
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < p; j++) {
        double amount_d = q[i][j];
        double mi = amount_d, ma = amount_d;
        mi = mi / (r[i] * 1.1);
        ma = ma / (r[i] * 0.9);
        int mi_a = ceil(mi), ma_a = floor(ma);
        //                cout<<mi_a<<" "<<ma_a<<" "<<r[i]<<" "<<amount_d<<endl;
        //                while(mi_a*r[i]*1.1<amount_d)mi_a++;
        //                while(ma_a*r[i]*0.9>amount_d)ma_a--;
        //                cout<<mi_a<<" "<<ma_a<<" "<<r[i]<<" "<<amount_d<<endl;
        if (mi_a > ma_a)
          continue;
        amount[i].push_back(make_pair(ma_a, mi_a)); //[end, start]
      }
      sort(amount[i].begin(), amount[i].end(), greater<pair<int, int>>());
    }
    int ans = 0;
    while (amount[0].size()) {
      pair<int, int> fr = amount[0][0];
      //     cout<<fr.first<<" "<<fr.second<<endl;
      amount[0].erase(amount[0].begin());
      bool ok = true;
      vector<int> to_erase(n, -1);
      for (int j = 1; j < n; j++) {
        for (int k = 0; k < amount[j].size(); k++) {
          // cout<<amount[j][k].first<<" "<<amount[j][k].second<<endl;
          if (amount[j][k].first >= fr.second &&
              amount[j][k].second <= fr.first) {
            if (to_erase[j] == -1)
              to_erase[j] = k;
            else {
              if (amount[j][to_erase[j]].second < amount[j][k].second) {
                to_erase[j] = k;
              }
            }
          }
        }
        if (to_erase[j] == -1) {
          ok = false;
          break;
        }
      }
      if (ok == false) {
        break;
      }
      ans++;
      FOR(i, n) {
        if (i == 0)
          continue;
        amount[i].erase(amount[i].begin() + to_erase[i]);
      }
    }
    //        FOR(i,100)amount[i].clear();
    //        for(int i=0;i<n;i++){
    //            for(int j=0;j<p;j++){
    //                double amount_d=q[i][j];
    //                double mi=amount_d,ma=amount_d;
    //                mi=mi/(r[i]*1.1);ma=ma/(r[i]*0.9);
    //                int mi_a=floor(mi),ma_a=ceil(ma);
    //                //                cout<<mi_a<<" "<<ma_a<<" "<<r[i]<<"
    //                "<<amount_d<<endl; while(mi_a*r[i]*1.1<amount_d)mi_a++;
    //                while(ma_a*r[i]*0.9>amount_d)ma_a--;
    //                //                cout<<mi_a<<" "<<ma_a<<" "<<r[i]<<"
    //                "<<amount_d<<endl; if(mi_a>ma_a)continue;
    //                amount[i].push_back(make_pair(mi_a, ma_a));//[end, start]
    //            }
    //            sort(amount[i].begin(),amount[i].end());
    //        }
    //        int ans2=0;
    //        while(amount[0].size()){
    //            pair<int,int>fr=amount[0][0];
    //            //     cout<<fr.first<<" "<<fr.second<<endl;
    //            amount[0].erase(amount[0].begin());
    //            bool ok=true;
    //            vector<int>to_erase(n,-1);
    //            for(int j=1;j<n;j++){
    //                for(int k=0;k<amount[j].size();k++){
    //                    //cout<<amount[j][k].first<<"
    //                    "<<amount[j][k].second<<endl;
    //                    if(amount[j][k].first>=fr.second&&amount[j][k].second<=fr.first){
    //                        to_erase[j]=k;
    //                        break;
    //                    }
    //                }
    //                if(to_erase[j]==-1){
    //                    ok=false;
    //                    break;
    //                }
    //            }
    //            if(ok==false){
    //                break;
    //            }
    //            ans2++;
    //            FOR(i,n){
    //                if(i==0)continue;
    //                amount[i].erase(amount[i].begin()+to_erase[i]);
    //            }
    //        }
    cout << ans << endl;
  }
  return 0;
}

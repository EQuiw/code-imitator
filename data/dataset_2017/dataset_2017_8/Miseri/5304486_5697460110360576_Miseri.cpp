#include<bits/stdc++.h>
#define pb   push_back
using namespace std;
typedef long long ll;
typedef long double ld;

int n, T, P;

int r[55], g, mm[55][55];

set<pair<int,int>> pq[55];

pair<int,int> mmt(int g,int i){ 
  int hi = 5000001, lo = 0;
  for(int it=0;it<35;it++){
    int mid = (hi+lo)/2;
    if ((int)(1.1*(r[i]*mid)+0.5)>=g) hi = mid;
    else lo = mid;
  }
  int hi1 = 5000001, lo1 = 0;
  for(int it=0;it<35;it++){
    int mid = (hi1+lo1)/2;
    if ((int)(0.9*(r[i]*mid)+0.5)<=g) lo1 = mid;
    else hi1 = mid;
  }
  return {hi,lo1};
}

int main(){
  ios_base::sync_with_stdio(false);cin.tie(0);
  cin >> T;
  for(int it=1;it<=T;it++){
    cin >> n >> P;
    for(int i=0;i<n;i++){
      cin >> r[i];
    }
    vector<vector<int>> events;
    for(int i=0;i<n;i++){
      for(int j=0;j<P;j++){
        cin >> g;
        auto p = mmt(g,i);
        //cout << p.first <<  " " << p.second <<endl;
        if (p.first>p.second) continue;
        mm[i][j] = p.second;
        events.pb({p.first,i,j});
        events.pb({p.second,i+n,j});
      }
    }
    sort(events.begin(),events.end());
    ll bm = 0, targ = (1LL<<n)-1;
    ll ans = 0;
    for(auto &v: events){
      //cout << bm <<endl;
      if (v[1]>=n){
        v[1]-=n;
        if (bm==targ && pq[v[1]].begin()->second==v[2]){
          //cout << "ADDING " << v[1] <<endl;
          ans++;
          for(int i=0;i<n;i++){
            pq[i].erase(pq[i].begin());
            if (pq[i].empty()) bm^=1LL<<i;
          }
        }
        else {
          int i = v[1];
          if (pq[i].empty()||pq[i].begin()->second!=v[2]) continue;
          pq[i].erase(pq[i].begin());
          if (pq[i].empty()) bm^=1LL<<i;
        }
      }
      else {
        int i = v[1];
        if (pq[i].empty())bm^=1LL<<i;
        pq[i].insert(make_pair(mm[i][v[2]],v[2]));
      }
    }
    for(int i=0;i<n;i++) assert(pq[i].empty());
    cout << "Case #" << it << ": " << ans <<endl;
  }
}

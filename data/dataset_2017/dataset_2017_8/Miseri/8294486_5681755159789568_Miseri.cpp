#include<bits/stdc++.h>
#define pb   push_back
using namespace std;
typedef long long ll;
typedef long double ld;

ld s[3333];
ll d[3333];
ld D[111][111];
int N, Q;
ld mint[111][111];

ld dijk(int a, int b){
  for(int i=0;i<101;i++) 
    for(int j=0;j<101;j++) 
      mint[i][j] = 1e55;
  mint[a][a] = 0;
  // time, place, horse, horse dis left
  priority_queue<vector<ld>,vector<vector<ld>>,greater<vector<ld>>> pq;
  pq.push({(ld)0,(ld)a,(ld)a,(ld)d[a]});
  while(!pq.empty()){
    auto v = pq.top(); pq.pop();
    int cn = v[1], ch = v[2], hl = v[3];
    ld ct=v[0];
    if (cn == b) return ct;
    if (ct > mint[cn][ch]) continue;
    // keep on current horse
    for(int i=0;i<N;i++){
      if (D[cn][i]==-1 || hl<D[cn][i]) continue;
      int nhl = hl-D[cn][i];
      ld nt = ct + D[cn][i]/s[ch];
      if (nt<mint[i][ch]){
        mint[i][ch] = nt;
        pq.push({(ld)nt,(ld)i,(ld)ch,(ld)nhl});
      }
    }
    // take new horse
    ch = cn; hl = d[ch];
    for(int i=0;i<N;i++){
      if (D[cn][i]==-1 || hl<D[cn][i]) continue;
      int nhl = hl-D[cn][i];
      ld nt = ct + D[cn][i]/s[ch];
      if (nt<mint[i][ch]){
        mint[i][ch] = nt;
        pq.push({(ld)nt,(ld)i,(ld)ch,(ld)nhl});
      }
    }
  }
  return -1;
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);
    int T;
    cin >> T;
    cout << setprecision(10) << fixed;
    for(int it=0;it<T;it++){
      int a, b;
      cin >> N >> Q;
      for(int i=0;i<N;i++){
        cin >> d[i] >> s[i];
      }
      for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
          cin >> D[i][j];
        }
      }
      cout << "Case #" << it+1 << ": ";
      for(int i=0;i<Q;i++){
        cin >> a >> b;
        a--; b--;
        cout << dijk(a,b) <<" ";
      }
      cout <<endl;
    }
}

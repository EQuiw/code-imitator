#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm> // sort
#include <utility>
#include <cmath>

typedef long long ll;
using namespace std;

bool has_overlap(pair<int,int> p1, pair<int,int> p2){
  if(p1.second < p2.first) return false;
  if(p2.second < p1.first) return false;
  return true;
}

int main(){
  ll T;
  cin >> T;

  for(int i=0; i<T; i++){
    ll N,P;
    cin >> N >> P;
    vector<int> rcp(N);
    for(int i=0; i<N; i++){
      cin >> rcp[i];
    }
    vector<vector<int> > pack(N);
    for(int i=0; i<N; i++){ pack[i].resize(P); }
    for(int i=0; i<N; i++){
      for(int j=0; j<P; j++){
        cin >> pack[i][j];
      }
      sort(pack[i].begin(), pack[i].end());
    }

    // check possible num of servings
    vector<vector<pair<int,int> > > segs(N);
    for(int i=0; i<N; i++){
      for(int j=0; j<P; j++){
        int lmul = 1;
        while(pack[i][j] > 1.1*lmul*rcp[i]){ lmul++; }
        int rmul = lmul;
        while(pack[i][j] >= 0.9*rmul*rcp[i]){ rmul++; } rmul--;

        if(lmul <= rmul){ segs[i].push_back(make_pair(lmul,rmul)); }
      }
    }

    int ans=0;
    vector<int> idx(N, 0);
    for(int j=0; j<segs[0].size(); j++){
      pair<int,int> crr = segs[0][j];
      // cerr << pack[0][j] << " " << rcp[0] << " " << crr.first << " " << crr.second << endl;

      bool possible = true;
      for(int i=1; i<N; i++){
        int tmp_idx = idx[i];
        for(; tmp_idx < segs[i].size(); tmp_idx++){
          if(has_overlap(crr, segs[i][tmp_idx])){ break; }
        }
        if(tmp_idx == segs[i].size()){
          possible = false;
          break;
        }
        idx[i] = tmp_idx+1;
      }
      if(possible){ ans++; }
    }

    cout << "Case #" << i+1 << ": " << ans << endl;
  }

  return 0;
}

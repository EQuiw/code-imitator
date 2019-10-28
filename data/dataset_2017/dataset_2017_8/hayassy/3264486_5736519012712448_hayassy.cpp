#include <iostream>
#include <vector>
#include <algorithm> // sort
#include <utility>

typedef long long ll;
using namespace std;

char flip(char c){ if(c == '+'){ return '-'; } return '+'; }

int main(){
  ll N;
  cin >> N; cin.ignore();

  for(int i=0; i<N; i++){
    string ps;
    int K;
    cin >> ps >> K; cin.ignore();

    ll lim = ps.length() - (K-1);

    ll ans = 0;
    for(int j=0; j < lim; j++){ // make every pancake happy
      if(ps[j] == '-'){
        ans++;
        for(int k=0; k<K; k++){
          ps[j+k] = flip(ps[j+k]);
        }
      }
    }
    for(size_t j=lim; j<ps.length(); j++){
      if(ps[j] == '-'){
        ans = -1;
        break;
      }
    }

    if(ans < 0){
      cout << "Case #" << i+1 << ": IMPOSSIBLE" << endl;
    } else {
      cout << "Case #" << i+1 << ": " << ans << endl;
    }
  }

  return 0;
}

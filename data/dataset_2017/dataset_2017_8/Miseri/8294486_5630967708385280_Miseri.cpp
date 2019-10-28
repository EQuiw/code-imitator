#include<bits/stdc++.h>
#define pb   push_back
using namespace std;
typedef long long ll;
typedef long double ld;

ld d[3333], s[3333];

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);
    int T;
    cin >> T;
    cout <<fixed <<setprecision(10);
    for(int it=0;it<T;it++){
      int N, D;
      cin >> D >> N;
      ld t = 0;
      for(int i=0;i<N;i++){
        cin >> d[i] >> s[i];
        ld tod = (D-d[i])/s[i];
        t = max(t,tod);
      }
      ld ans = ((ld)D)/t;
      cout << "Case #" << it+1 << ": " << ans <<endl;
    }
}

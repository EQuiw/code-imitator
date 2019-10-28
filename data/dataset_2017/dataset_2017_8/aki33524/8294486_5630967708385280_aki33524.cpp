#include <bits/stdc++.h>
using namespace std;

int D, N;
vector<double> K, S;

void solve(){
    double mtime = 0;
    for(int i=0; i<N; i++){
        mtime = max(mtime, (D - K[i]) / S[i]);
    }
    cout << D / mtime << endl;
}

int main(){
    cout.precision(16);
    cout.setf(ios::fixed);
    
    int T; cin >> T;
    for(int i=1; i<=T; i++){
        cout << "Case #" << i << ": ";
        cin >> D >> N;
        K.resize(N);
        S.resize(N);
        
        for(int i=0; i<N; i++)
            cin >> K[i] >> S[i];
        
        solve();
    }
    
    return 0;
}
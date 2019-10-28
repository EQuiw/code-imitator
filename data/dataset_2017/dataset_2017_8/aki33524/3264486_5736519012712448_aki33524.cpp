#include <bits/stdc++.h>
using namespace std;

string S;
int K;

void flip(int si){
    for(int i=0; i<K; i++){
        if(S[si+i] == '-')
            S[si+i] = '+';
        else
            S[si+i] = '-';
    }
}

void solve(){
    cin >> S >> K;
    int L = S.size();
    
    int count = 0;
    for(int i=0; i<L-K+1; i++){
        if(S[i] == '-'){
            flip(i);
            count++;
        }
    }
    for(int i=0; i<L; i++){
        if(S[i] == '-'){
            cout << "IMPOSSIBLE" << endl;
            return;
        }
    }
    cout << count << endl;
}

int main(){
    int T; cin >> T;
    for(int t=0; t<T; t++){
        cout << "Case #" << t+1 << ": ";
        solve();
    }
    return 0;
}
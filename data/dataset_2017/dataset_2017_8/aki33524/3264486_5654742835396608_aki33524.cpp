#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll N, K;

void solve(){
    priority_queue<ll> que;
    
    que.push(N);
    for(int i=0; i<K-1; i++){
        auto x = que.top(); que.pop();
        x--;
        que.push(x/2);
        que.push((x+1)/2);
    }
    ll x = que.top();
    x--;
    cout << (x+1)/2 << " " << x/2 << endl;
}

int main(){
    int T; cin >> T;
    for(int i=0; i<T; i++){
        cout << "Case #" << i+1 << ": ";
        cin >> N >> K;
        solve();
    }
    
    return 0;
}
#include <bits/stdc++.h>

using namespace std;
bool check(int n){
    vector<int> V;
    while(n){
        V.push_back(n%10);
        n=n/10;
    }
    reverse(V.begin(),V.end());
    for(int i=1;i<V.size();++i)
        if(V[i]<V[i-1])
            return false;
    return true;
}
int main(){
    freopen("A.txt","r",stdin);
    freopen("W.txt","w",stdout);
    int t;cin >> t;
    int index=1;
    while(t--){
       int n;cin >> n;
       while(true){
            if(check(n))
                break;
            --n;
       }

            cout << "Case #" << index++ << ": " << n << endl;

    }
    return 0;
}

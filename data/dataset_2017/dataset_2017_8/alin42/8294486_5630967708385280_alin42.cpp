#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

int main(){
    ios::sync_with_stdio(0);
    freopen("readable.txt","w",stdout);
    int t; cin>>t;
    for (int ca=1;ca<=t;ca++){
        int n; ld d; 
        cin>>d>>n;
        ld ans=0;
        while (n--){
            ld k,s; cin>>k>>s; 
            ans=max(ans,(d-k)/s);
        }
        cout<<"Case #"<<ca<<": "<<fixed<<setprecision(10)<<(d/ans)<<endl;
    }
    return 0;
}

//g++ -std=c++11 -O2 -Wfatal-errors -Im -Wall -Wextra -o "output.txt" "code.cpp"
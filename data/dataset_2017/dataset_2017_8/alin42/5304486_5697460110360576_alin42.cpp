#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;

ll need[1005]; 
vector<pii> segs[1005];
int main(){
    ios::sync_with_stdio(0);
    freopen("readable.txt","w",stdout);
    int t; cin>>t;
    for (int ca=1;ca<=t;ca++){
        cout<<"Case #"<<ca<<": ";
        int n,p; cin>>n>>p;
        for (int i=1;i<=n;i++) {
            cin>>need[i];
            segs[i].clear();
        }
        for (int i=1;i<=n;i++) {
            for (int j=1;j<=p;j++){
                ll x; cin>>x; 
                ll l=(10*x+11*need[i]-1)/(11*need[i]); 
                ll r=(10*x)/(9*need[i]); 
                if (l<=r) segs[i].push_back({l,r});
            }
            if (segs[i].size()) sort(segs[i].begin(),segs[i].end());
        }
        /*for (int i=1;i<=n;i++){
            for (pii p:segs[i]) cout<<p.first<<' '<<p.second<<','; cout<<endl;
        }*/
        int ans=0;
        for (int i=0;i<segs[1].size();i++){
            ll l=segs[1][i].first,r=segs[1][i].second;
            int ch=-1;
            for (int j=0;j<segs[2].size();j++){
                if ((segs[2][j].second<l)||(segs[2][j].first>r)) 1;
                else{
                    ch=j; break;
                }
            }
            if (ch!=-1){
                ans++;
                segs[2].erase(segs[2].begin()+ch);
            }
        }
        if (n==1) ans=segs[1].size();
        cout<<ans<<endl;
    }
    return 0;
}

//g++ -std=c++11 -O2 -Wfatal-errors -Im -Wall -Wextra -o "output.txt" "code.cpp"
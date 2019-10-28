#include <bits/stdc++.h>


using namespace std;
string ok(int n){
    if(n==1) return "R";
    if(n==2) return "B";
    return "Y";
}
long long dis[1005][1005];
long long E[1005];
long long s[1005];
int main(){
  freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int t;cin >> t;int index=1;
    while(t--){
        int n,q;cin >> n >> q;
        for(int i=1;i<=n;++i){
            cin >> E[i] >> s[i];
        }
        for(int i=1;i<=n;++i){
            for(int j=1;j<=n;++j){
                cin >> dis[i][j];
                if(dis[i][j]==-1)
                    dis[i][j]=1000000000000000000;
            }
        }
        for(int k=1;k<=n;++k){
            for(int i=1;i<=n;++i){
                for(int j=1;j<=n;++j){
                    dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
                }
            }
        }


        cout << "Case #" << index++ << ":";
        while(q--){
            int uk,vk;cin >> uk >> vk;
            set<pair<double,int> > S;
            S.insert(make_pair(0,uk));
            bool vis[1005];
            for(int i=1;i<=n;++i) vis[i]=0;
            while(!S.empty()){
                auto it=S.begin();
                if(vis[(*it).second]){
                    S.erase(it);
                    continue;}
                if((*it).second==vk){
                    cout << " ";
                    printf("%.10f",(*it).first);break;
                }
                vis[(*it).second]=1;
                for(int i=1;i<=n;++i){
                    if(dis[(*it).second][i]<=E[(*it).second] && dis[(*it).second][i]!=1000000000000000000){
                        S.insert(make_pair((*it).first+((1.0*dis[(*it).second][i])/(1.0*s[(*it).second])),i));
                    }
                }
            }
            }
        cout << endl;
    }

    return 0;
}

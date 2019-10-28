//Hi
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <set>
#include <map>
using namespace std;
typedef long long ll;

void solve(){
    int n, q;
    pair<int, int> cities[100];
    vector<int> dists[101];
    cin>>n>>q;
    for(int i=0; i< n; i++){
        cin>>cities[i].first>>cities[i].second;
    }
    for(int i=0; i< n; i++){
        for(int j=0; j< n; j++){
            int x;
            cin>>x;
            if(x==-1)continue;
            dists[i].push_back(x);
        }
    }
    int s;
    int d;
    cin>>s>>d;
    long double bestTimes[100];
    for(int i=0; i< n; i++) bestTimes[i]=1e13;
    bestTimes[0]= 0;
    for(int i=0; i< n-1; i++){
        int cur=0;
        int counter=i;
        long double curTime=bestTimes[i];
        while(cur+dists[counter][0]<=cities[i].first){
            
            curTime +=(long double)dists[counter][0]/cities[i].second;
            cur =cur+dists[counter][0];
            bestTimes[counter+1] = min(curTime,bestTimes[counter+1] );
            
            counter++;
            if(counter>=n-1) break;
        }
       // for(int j=0; j< n; j++) cout<<bestTimes[j]<<" ";
       // cout<<endl;
    }
    cout<<fixed<<setprecision(8)<<bestTimes[n-1]<<endl;
}
int main()
{
    ios::sync_with_stdio(false);
    freopen("test.txt","r",stdin);
    freopen("test1.txt","w",stdout);
    int t;
    cin>>t;
    for(int i=1; i<=t; i++){
        cout<<"Case #"<<i<<": ";
        solve();
        
    }
    
}

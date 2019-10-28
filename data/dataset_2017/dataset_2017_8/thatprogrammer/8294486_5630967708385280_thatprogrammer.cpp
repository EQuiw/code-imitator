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
pair<int, int> horses[1001];
void solve(int d, int n){
    long double ans=1e15;
    for(int i=0; i< n; i++){
        long double en = (long double)(d-horses[i].first)/horses[i].second;
        long double cur = d/en;
        ans = min(cur, ans);
    }
    cout<<fixed<<setprecision(8)<<ans<<endl;
}
int main()
{
    ios::sync_with_stdio(false);
    freopen("test.txt","r",stdin);
    freopen("test1.txt","w",stdout);
    int t;
    cin>>t;
    for(int i=1; i<=t; i++){
        int d, n;
        cin>>d>>n;
        for(int j=0; j< n; j++) cin>>horses[j].first>>horses[j].second;
        cout<<"Case #"<<i<<": ";
        solve(d,n);
    }
    
}

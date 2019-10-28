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
int solve(string s, int k){
    int ans=0;
    for(int i=0; i<= s.length()-k; i++){
        if(s[i]=='-'){
            ans++;
            for(int j=i; j<i+k; j++){
                if(s[j]=='-')s[j]='+';
                else s[j] = '-';
            }
        }
    }
    
    for(int i=0; i< s.length(); i++){
        if(s[i]=='-')ans=-1;
    }
    return ans;
}
int main()
{
    ios::sync_with_stdio(false);
    freopen("test.txt","r",stdin);
    freopen("test1.txt","w",stdout);
    //freopen(".out","w",stdout);
    int t;
    cin>>t;
    for(int i=1; i<=t; i++){
        string s;
        int k;
        cin>>s>>k;
        int ans = solve(s,k);
        if (ans == -1) cout<<"Case #"<<i<<": "<<"IMPOSSIBLE"<<endl;
        else cout<<"Case #"<<i<<": "<<ans<<endl;
    }
}



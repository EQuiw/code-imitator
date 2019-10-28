#include <vector>
#include <string.h>
#include<iostream>
#include<set>
#include<map>
#include<unordered_map>
#include<string.h>
#include<algorithm>
using namespace std;

const int mod=1e9+7;
typedef long long ll;

#define out_vector(v) for(auto a:v)cout<<a<<" "; cout<<endl;

struct less_than_key{
    inline bool operator() (const pair<int,int>& p1, const pair<int,int>& p2){
        return (p1.first==p2.first?p1.second<p2.second:p1.first > p2.first);
    }
};

bool check(ll d){
    string s=to_string(d);
    for(int i=0;i<s.length()-1;i++){
        if(s[i]>s[i+1]){
            return false;
        }
    }
    return true;
}

int main()
{
    freopen("/Users/shitian/Downloads/B-small-attempt0.in", "r", stdin);
    freopen("/Users/shitian/Downloads/B-small-attempt0.txt", "w", stdout);
    int tcase;
    cin>>tcase;
    for(int tc=1;tc<=tcase;tc++){
        cout<<"Case #"<<tc<<": ";
        
        ll n,last;
        cin>>n;
        for(ll i=1;i<=n;i++){
            if(check(i)){
                last=i;
            }
        }
        cout<<last<<endl;
    }
    return 0;
}

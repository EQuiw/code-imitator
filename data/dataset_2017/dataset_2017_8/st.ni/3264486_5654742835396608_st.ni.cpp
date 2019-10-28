#include <vector>
#include <string.h>
#include<iostream>
#include<set>
#include<map>
#include<unordered_map>
#include<string.h>
#include<algorithm>
#include <stdlib.h>
using namespace std;

const int mod=1e9+7;
typedef long long ll;

#define out_vector(v) for(auto a:v)cout<<a<<" "; cout<<endl;

struct less_than_key{
    inline bool operator() (const pair<int,int>& p1, const pair<int,int>& p2){
        return (p1.first==p2.first?p1.second<p2.second:p1.first > p2.first);
    }
};

ll po(ll b,ll d){
    if(d==0){
        return 1;
    }
    return b*po(b,d-1);
}

int main()
{
    freopen("/Users/shitian/Downloads/C-small-1-attempt0.in", "r", stdin);
    freopen("/Users/shitian/Downloads/C-small-1-attempt0.txt", "w", stdout);
    int tcase;
    cin>>tcase;
    for(int tc=1;tc<=tcase;tc++){
        cout<<"Case #"<<tc<<": ";
        
        ll n,k;
        cin>>n>>k;
        set<ll>stalls;
        stalls.insert(0);
        stalls.insert(n+1);
        for(int kk=0;kk<k;kk++){
            //min(LS, RS) is maximal.  A
            //max(LS, RS) is maximal   B
            //left
            vector<pair<int,pair<int,int> > >vec;//l,r
            //if use i
            for(int i=1;i<=n;i++){
                if(stalls.find(i)!=stalls.end())continue;
                //find l, r occupied
                ll l,r;
                auto it=stalls.lower_bound(i);
                r=*it;
                it--;
                l=*it;
                
                vec.push_back(make_pair(i,make_pair(i-l-1, r-i-1)));
            }
            vector<pair<int,pair<int,int> > >A,B;
            //min_lr A
            ll min_lr=0;
            for(int i=0;i<vec.size();i++){
                int l=vec[i].second.first,r=vec[i].second.second;
                if(min(l,r)>=min_lr){
                    if(min(l,r)>min_lr)A.clear();
                    A.push_back(vec[i]);
                    min_lr=min(l,r);
                }
            }
            //max_lr B
            ll max_lr=0;
            for(int i=0;i<A.size();i++){
                int l=A[i].second.first,r=A[i].second.second;
                if(max(l,r)>=max_lr){
                    if(max(l,r)>max_lr)B.clear();
                    B.push_back(A[i]);
                    max_lr=max(l,r);
                }
            }
            sort(B.begin(),B.end());
          
            stalls.insert(B[0].first);
            if(kk==k-1){
                cout<<B[0].second.second<<" "<<B[0].second.first<<endl;
            }
        }
        //out_vector(stalls);
    }
    return 0;
}

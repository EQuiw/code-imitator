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
int servings[51];
int packs[51][51];
pair<int, int> valid(int ser, int x){
    pair<int, int> res;
    res.second = 0;
    if( (float)x/(0.9*ser)<(float)x/(1.1*ser)) return res;
    res.first = ceil(x/(1.1*ser))+0.00001;
    res.second = x/(0.9*ser);
    return res;
}
struct entr{
    int x;
    int ingre;
    int id;
    int en;
    bool start;
};
bool comp(entr a, entr b){
    if(a.x< b.x) return true;
    if(a.x == b.x && a.start) return true;
    return false;
}
bool comp2(entr a, entr b){
    return a.en< b.en;
}
int solve(int n,int p){
    int ans=0;
    vector<entr> ranges;
    int idCount = 0;
    for(int i=0; i< n; i++){
        for(int j=0; j<p; j++){
            pair<int, int> cur = valid(servings[i], packs[i][j]);
            if(cur.second==0)continue;
            if(cur.second<cur.first)continue;
            entr temp;
            temp.x = cur.first;
            temp.ingre = i;
            temp.id = idCount;
            temp.start = true;
            temp.en = cur.second;
            ranges.push_back(temp);
            temp.x = cur.second;
            temp.start = false;
            ranges.push_back(temp);
            idCount++;
            
        }
    }
    sort(ranges.begin(), ranges.end(),comp);
    vector<entr> cInRange[51];
    for(int i=0; i<ranges.size(); i++){
       // cout<<ranges[i].x<<" "<<ranges[i].id<<" "<<ranges[i].ingre<<endl;
        if(ranges[i].start) cInRange[ranges[i].ingre].push_back(ranges[i]);
        else{
            for(int j=0; j<cInRange[ranges[i].ingre].size(); j++){
                if(cInRange[ranges[i].ingre][j].id == ranges[i].id){
                    cInRange[ranges[i].ingre].erase(cInRange[ranges[i].ingre].begin() + j);
                    break;
                }
            }
            continue;
        }
        int curMin = cInRange[0].size();
        for(int j =0; j< n; j++){
            curMin = min(curMin, (int)cInRange[j].size());
        }
        ans+=curMin;
        if(curMin ==0)continue;
        
        for(int j =0; j< n; j++){
            sort(cInRange[j].begin(), cInRange[j].end(), comp2);
            cInRange[j].erase(cInRange[j].begin());
        }
        
    }
    /*
    for(map<int, int>::iterator it = nums[0].begin(); it!=nums[0].end(); ++it){
        int cur = it->second;
        int check= it->first;
        for(int i=0; i< n; i++){
            cur = min(cur, nums[i][check]);
        }
        ans+=cur;
    }
     */
    return ans;
}
int main()
{
    ios::sync_with_stdio(false);
    freopen("test.txt","r",stdin);
    freopen("test2.txt","w",stdout);
    int t;
    cin>>t;
    for(int i=1; i<=t; i++){
        int n, p;
        cin>>n>>p;
        for(int j=0; j<n; j++) cin>>servings[j];
        for(int j=0; j< n; j++){
            for(int b =0; b< p; b++){
                cin>>packs[j][b];
            }
        }
        
        int ans = solve(n, p);
        cout<<"Case #"<<i<<": "<<ans<<endl;
    }
    
}

/* ***************************************
Author        :Scau.ion
Created Time  :2017/04/08 18:38:40 UTC+8
File Name     :ion.cpp
*************************************** */

#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define ULL unsigned long long
#define PB push_back
#define MP make_pair
#define PII pair<int,int>
#define VI vector<int>
#define VPII vector<PII>
#define X first
#define Y second
#define IOS ios::sync_with_stdio(0);cin.tie(0);
#define IN freopen("C-small-1-attempt0.in", "r", stdin);
#define OUT freopen("C-small-1-attempt0.out", "w", stdout);

int main()
{
    IN;
    OUT;
    int t;
    cin>>t;
    for (int i=1;i<=t;++i)
    {
        LL n,k;
        cin>>n>>k;
        map<LL,LL> mp;
        mp[n]=1;
        queue<LL> que;
        que.push(n);
        while (1)
        {
            LL tis=que.front();
            que.pop();
            LL num=mp[tis];
            if (num>=k)
            {
                cout<<"Case #"<<i<<": "<<(tis/2)<<" "<<((tis-1)/2)<<endl;
                break;
            }
            k-=num;
            if (mp.find(tis/2)==mp.end()) que.push(tis/2);
            if (tis%2==0&&mp.find((tis-1)/2)==mp.end()) que.push((tis-1)/2);
            mp[tis/2]+=num;
            mp[(tis-1)/2]+=num;
        }
    }
}

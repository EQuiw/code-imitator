/* ***************************************
Author        :Scau.ion
Created Time  :2017/04/23 00:23:02 UTC+8
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
#define IN freopen("B-small-attempt0.in", "r", stdin);
#define OUT freopen("B-small-attempt0.out", "w", stdout);

int main()
{
    IN;
    OUT;
    IOS;
    int t;
    cin>>t;
    for (int i=1;i<=t;++i)
    {
        int n;
        cin>>n;
        pair<int,char> a[3];
        for (int j=0;j<3;++j)
        {
            cin>>a[j].X;
            int xx;
            cin>>xx;
        }
        a[0].Y='R';
        a[1].Y='Y';
        a[2].Y='B';
        sort(a,a+3);
        cout<<"Case #"<<i<<": ";
        if (a[2].X>a[0].X+a[1].X) cout<<"IMPOSSIBLE"<<endl;
        else
        {
            vector<char> ans;
            for (int j=1;j<=a[2].X;++j)
                ans.PB(a[2].Y);
            int st=0;
            for (int j=1;j<=a[1].X;++j)
            {
                ans.insert(ans.begin()+st,a[1].Y);
                st+=2;
            }
            int j;
            for (j=1;j<=a[0].X;++j)
            {
                if (st==ans.size()) break;
                ans.insert(ans.begin()+st,a[0].Y);
                st+=2;
            }
            st=0;
            for (;j<=a[0].X;++j)
            {
                ans.insert(ans.begin()+st,a[0].Y);
                st+=2;
            }
            for (int j=0;j<ans.size();++j)
                cout<<ans[j];
            cout<<endl;
        }
    }
    return 0;
}

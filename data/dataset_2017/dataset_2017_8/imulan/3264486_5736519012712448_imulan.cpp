#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define rep(i,n) for(int (i)=0;(i)<(int)(n);++(i))
#define each(itr,c) for(__typeof(c.begin()) itr=c.begin(); itr!=c.end(); ++itr)
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define fi first
#define se second

void solve()
{
    string s;
    int k;
    cin >>s >>k;

    int n=s.size();
    int ans=0;
    rep(i,n-k+1)
    {
        if(s[i]=='-')
        {
            rep(j,k) s[i+j] = (s[i+j]=='+')?'-':'+';
            // cout<<"flip: "<<i<<" "<<s<<endl;
            ++ans;
        }
    }

    bool valid=true;
    rep(i,n) valid&=(s[i]=='+');
    if(valid) printf("%d\n", ans);
    else printf("IMPOSSIBLE\n");
}

int main()
{
    int T;
    cin >>T;
    rep(t,T)
    {
        printf("Case #%d: ", t+1);
        solve();
    }
    return 0;
}

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
    int r,c;
    cin >>r >>c;
    vector<string> s(r);
    rep(i,r) cin >>s[i];

    // // 各行に何かしら文字があるか？
    // bool row=true;
    // rep(i,r)
    // {
    //     bool ok=false;
    //     rep(j,c)if(s[i][j]!='?') ok=true;
    //     row&=ok;
    // }
    //
    // // 各列に何かしら文字があるか？
    // bool column=true;
    // rep(i,c)
    // {
    //     bool ok=false;
    //     rep(j,r)if(s[j][i]!='?') ok=true;
    //     column&=ok;
    // }


    // 横に伸ばす
    rep(i,r)rep(j,c)
    {
        if(s[i][j]!='?')
        {
            int L=j,R=j;
            while(L>0 && s[i][L-1]=='?') --L;
            while(R<c-1 && s[i][R+1]=='?') ++R;

            for(int k=L; k<=R; ++k) s[i][k]=s[i][j];
        }
    }

    rep(i,r)
    {
        if(s[i][0]!='?')
        {
            int L=i,R=i;
            while(L>0 && s[L-1][0]=='?') --L;
            while(R<r-1 && s[R+1][0]=='?') ++R;

            for(int j=L; j<=R; ++j)
            {
                rep(k,c) s[j][k]=s[i][k];
            }
        }
    }
    rep(i,r)rep(j,c) assert(s[i][j]!='?');

    rep(i,r) cout << s[i] << endl;
}

int main()
{
    int T;
    cin >>T;
    rep(t,T)
    {
        printf("Case #%d:\n", t+1);
        solve();
    }
    return 0;
}

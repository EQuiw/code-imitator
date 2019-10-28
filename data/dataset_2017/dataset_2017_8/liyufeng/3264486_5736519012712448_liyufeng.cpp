#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <string>
#include <cmath>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <bitset>
#include <cstdlib>
#include <vector>
using namespace std;

#define   lowbit(x)     x&(-x)
#define   lson          l,m,rt<<1
#define   rson          m+1,r,rt<<1|1
#define   ll            long long
#define   ull           unsigned long long
#define   mem(n,v)      memset(n,v,sizeof(n))
#define   MAX           100005
#define   PI            3.1415926
#define   E             2.718281828459
#define   opnin         freopen("text.in.txt","r",stdin)
#define   opnout        freopen("text.out.txt","w",stdout)
#define   clsin         fclose(stdin)
#define   clsout        fclose(stdout)

const int    INF    =   0x7fffffff;
const ll     INFF   =   0x7fffffffffffffff;
const double pi     =   3.141592653589793;
const double inf    =   1e18;
const double eps    =   1e-8;
const ll     mod    =   1e9+7;
/*************************************************************/
int ans = 0;
string str;
int k;
void solve()
{
    int len = str.length();
    for(int i=0;i<len;i++){
        if(str[i] == '-'){
            if(i + k > len){
                ans = -1;
                break;
            }
            ans++;
            for(int j=0;j<k;j++){
                if(str[i+j] == '-')
                    str[i+j] = '+';
                else
                    str[i+j] = '-';
            }
        }
    }
}
int main()
{
    freopen("A-small-attempt5.in","r",stdin);
    freopen("A-small-attempt5.out","w",stdout);
    int t;
    cin >> t;
    for(int i=1;i<=t;i++){
        ans = 0;
        cin >> str >> k;
        solve();
        if(ans == -1)
            printf("Case #%d: IMPOSSIBLE\n",i,ans);
        else
            printf("Case #%d: %d\n",i,ans);
    }
    fclose(stdin);
    fclose(stdout);

    return 0;
}

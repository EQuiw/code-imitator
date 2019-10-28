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
int a[20];
int b[20];
int main()
{
    ll n;
    ll ans;
    freopen("B-small-attempt1.in","r",stdin);
    freopen("B-small-attempt1.out","w",stdout);
    int t;
    cin >> t;
    for(int i=1;i<=t;i++){
        mem(a,0);
        ans = 0;
        cin >> n;
        ll m = n;
        int cnt = 0;
        while(m > 0){
            a[cnt++] = m % 10;
            m /= 10;
        }
        for(int j=cnt-1;j>=1;j--){
            if(a[j-1] < a[j]){
                a[j] -= 1;
                while(j < cnt-1){
                    if(a[j+1] > a[j]){
                        a[j+1] -= 1;
                        j++;
                    }
                    else
                        break;
                }
                while(j >= 1){
                    a[j-1] = 9;
                    j--;
                }
            }
        }
        ll l = 1;
        for(int j=0;j<cnt;j++){
            ans += a[j] * l;
            l *= 10;
        }
        printf("Case #%d: %lld\n",i,ans);
    }
    fclose(stdin);
    fclose(stdout);

    return 0;
}

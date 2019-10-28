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
int main()
{
    freopen("C-small-1-attempt1.in","r",stdin);
    freopen("C-small-1-attempt1.out","w",stdout);
    int t;
    cin >> t;
    for(int i=1;i<=t;i++){
        int n,k;
        cin >> n >> k;
        priority_queue<int>q;
        q.push(n);
        for(int j=0;j<k-1;j++){
            int temp = q.top();
            q.pop();
            if(temp % 2 == 0){
                q.push((temp-1) - (temp-1) / 2);
                q.push((temp-1) / 2);
            }
            else{
                q.push((temp-1) / 2);
                q.push((temp-1) / 2);
            }
        }
        int a,b;
        int temp = q.top();
        if(temp % 2 == 0){
            a = (temp-1) - (temp-1) / 2;
            b = (temp-1) / 2;
        }
        else{
            b = a = (temp-1) / 2;
        }

        printf("Case #%d: %d %d\n",i,a,b);
    }
    fclose(stdin);
    fclose(stdout);

    return 0;
}

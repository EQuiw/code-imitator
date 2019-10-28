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
#define   MAX           105
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
    freopen("B-small-attempt0.in","r",stdin);
    freopen("B-small-attempt0.out","w",stdout);

    int N,P;
    int Q[MAX][MAX];
    int temp[MAX];
    int R[MAX];
    int kase;
    cin >> kase;
    for(int t=1;t<=kase;t++){
        cin >> N >> P;
        for(int i = 1;i <= N;i++)
            cin >> R[i];
        for(int i = 1;i <= N;i++){
            for(int j = 1;j <= P;j++){
                cin >> Q[i][j];
            }
            sort(Q[i]+1,Q[i]+1+P);
        }
        mem(temp,0);
        int ans = 0;
        for(int j = 1;j <= 1000005;j++){
            bool flag = false;
            for(int i = 1;i <= N;i++){
                long long d = ceil(0.9 * j * R[i]);
                while(temp[i] <= P && Q[i][temp[i]] < d)
                    temp[i]++;
                d = floor(1.1 * j * R[i]);
                if(Q[i][temp[i]] > d || temp[i] > P){
                    flag = true;
                    break;
                }
            }
            if(!flag){
                ans++;
                j = j - 1;
                for(int i = 1;i <= N;i++)
                    temp[i]++;
            }
            flag = true;
            for(int i = 1;i <= N;i++)
                if(temp[i] > P){
                    flag = false;
                    break;
                }
            if(!flag)
                break;
        }
        printf("Case #%d: %d\n",t,ans);
    }
    fclose(stdin);
    fclose(stdout);

    return 0;
}

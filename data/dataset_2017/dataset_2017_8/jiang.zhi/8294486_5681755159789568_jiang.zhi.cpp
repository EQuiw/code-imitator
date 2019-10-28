#include <algorithm>
#include <assert.h>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <memory.h>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <sstream>
#include <utility>
#include <vector>
using namespace std;

typedef pair<int,int> PII;
typedef long long LL;

#define ALL(x) x.begin(),x.end()

#define DEB(args...) fprintf(stderr,args)

#define PB push_back
#define MP make_pair
#define ST first
#define ND second 

const int INF = 0x3f3f3f3f;

const int N = 110;

int e[N], s[N];
long long dist[N][N];
long long reald[N];
double dtime[N];

int main(){
    int t;
    scanf("%d", &t);
    for(int cas = 1; cas <= t; cas++){
        long long ans = 0;
        int n, q;
        scanf("%d %d", &n, &q);
        for(int i = 0; i < n; i++){
            scanf("%d %d", e+i, s+i);
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                scanf("%lld",&dist[i][j]);
            }
        }
        reald[0]=0;
        for(int i = 0; i < n-1; i++){
            reald[i+1]=reald[i]+dist[i][i+1];
        }
        for(int i = 0; i < n; i++){
            // printf("%lld\n",reald[i]);
        }
        dtime[0]=0;
        for(int i = 1; i < n; i++){
            dtime[i]=1e18;
        }
        for(int i = 0; i < n; i++){
            for(int j = i+1; j < n; j++){
                if(reald[j]-reald[i]<=e[i]){
                    long long d = reald[j]-reald[i];
                    dtime[j]=min(dtime[j],dtime[i]+d*1.0/s[i]);
                }
            }
        }
        int a, b;
        scanf("%d %d",&a,&b);

        printf("Case #%d: %lf\n", cas, dtime[n-1]);
    }
    
}

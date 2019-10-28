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


int main(){
    int t;
    scanf("%d", &t);
    for(int cas = 1; cas <= t; cas++){
        
        int d, n;
        scanf("%d %d",&d,&n);

        double time = 0;
        double ans = 0;
        for(int i = 0 ; i < n; i++){
            int s, v;
            scanf("%d %d",&s,&v);
            time =  max(time,1.0*(d-s)/(v));
        }
        ans =  1.0*d/time;
        
        
        
        printf("Case #%d: %lf\n", cas, ans);
    }
    
}

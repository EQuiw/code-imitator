#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;


const double eps = 1e-8;
const double pi = acos(-1.0);


bool judge(long long k){
    int x=k%10;
    k/=10;
    while (k) {
        int nx=k%10;
        if (nx > x) {
            return false;
        }
        x=nx;
        k/=10;
    }
    return true;
}

long long pow10(int k){
    long long ret=1;
    for (int i = 0; i < k; i++) {
        ret*=10;
    }
    return ret;
}
long long calc(long long k, int p){
    long long ret=0;
    for (int i = 0; i < p; i++) {
        ret += 9LL * pow10( i);
        k/=10;
    }

    long long u=k%10;
    if (u == 0) {
        return -1;
    }
    u-=(p!=0);
    ret += u * pow10( p);
    k/=10;

    for (int i = p + 1; i <= 22; i++) {
        long long x=k%10;
        long long v = min(x, u);
        ret += v * pow10( i);
        u=v;
        k/=10;
    }
    return ret;
}

long long solve(long long  k) {
//    if (judge(k)) {
//        return k;
//    }
    long long ret=0;
    for (int i = 0; i <= 20; i++) {
        long long now = calc(k, i);
//        cout<<i<<" "<<now<<endl;
        ret = max(ret, now);
    }

    return ret;
}

int main() {
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);

    int T;
    cin>>T;

    for (int cas = 1; cas <= T; cas++) {
        long long k;
        cin>>k;
        long long ret = solve(k);

        cout<<"Case #"<<cas<<": "<<ret<<endl;
    }
    return 0;
}


#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define INF 1000000000000000000LL


int main() {
    vector<ll> v;
    queue<ll> q;


    q.push(0);

    while(!q.empty()) {
        ll val = q.front();
        q.pop();

        v.push_back(val);

        int now = val % 10;
        if(now == 0) now = 1;
        for(int i = now; i <= 9; i++) {
            if(val * 10 + i > INF) continue;
            q.push(val * 10 + i);
        }
    }


    int kase = 0, test;
    scanf("%d", &test);
    while(test--) {
        ll n;
        scanf("%lld", &n);
        int idx = lower_bound(v.begin(), v.end(), n) - v.begin();
        if(v[idx] != n) idx--;
        printf("Case #%d: %lld\n", ++kase, v[idx]);
    }
    return 0;
}
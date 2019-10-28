#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#define ll long long
#define sort(A) sort(A.begin(),A.end())
#define rsort(A) sort(A.rbegin(),A.rend())
using namespace std;
static const ll D = 1000000007;

ll foo(ll n, ll k){
    if(k==0)
        return n;
    else{
        return max(foo(n/2,k/2),foo((n-1)/2,(k-1)/2));
    }
}

int main() {
    ll T, n, k;
    cin >> T;
    for(ll t = 0; t<T; ++t){
        cin >> n >> k;
        ll r = foo(n,k-1);
        cout << "Case #" << t+1 << ": " << r/2 << " " << (r-1)/2 << endl;
    }
    return 0;
}

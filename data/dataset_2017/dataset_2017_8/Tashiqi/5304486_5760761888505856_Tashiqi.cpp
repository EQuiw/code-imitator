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


int main() {
    ll T, R, C, i, j;
    cin >> T;
    for(ll t = 0; t<T; ++t){
        cin >> R >> C;
        string foo;
        for(i = 0; i<C; ++i)
            foo += '?';
        vector<string> V(R), res(R, foo);
        vector<ll> X(R);
        vector<vector<ll>> Y(R, vector<ll> (C));
        for(i = 0; i<R; ++i)
            cin >> V[i];
        for(i = 0; V[i]==foo; ++i){}
        for(j = 0; j<R; ++j){
            if(V[j]!=foo)
                i = j;
            X[j] = i;
        }
        for(ll k = 0; k<R; ++k){
            for(i = 0; V[X[k]][i]=='?'; ++i){}
            for(j = 0; j<C; ++j){
                if(V[X[k]][j]!='?')
                    i = j;
                res[k][j] = V[X[k]][i];
            }
        }
        cout << "Case #" << t+1 << ":" << endl;
        for(auto& l:res)
            cout << l << endl;
    }

    return 0;
}

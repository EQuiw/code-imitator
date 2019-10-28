#include <iostream>
#include <string>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
using namespace std;
#define mp(X,Y) make_pair(X,Y)
#define F first
#define S second
typedef long long ll;
typedef pair<int,int> PII;
typedef pair<ll,ll> PLL;



int main(){
    ios::sync_with_stdio(0);
    freopen("1.in","r",stdin);
    freopen("out.txt","w",stdout);
    int t;
    int cas = 1;
    cin >> t;
    while(t--){
        cout << "Case #" << cas++<<": ";
        ll n,k;
        cin >> n >> k;
        priority_queue<ll > q;
        q.push(n);
        map<ll,int>ms;
        ms[n] = 1;
        while(k > 0){
          ll p = q.top();
          ll len = p - 1;
          ll m = ms[p];
          q.pop();
          ll z = len / 2;
          ll y = len - z;
          if(m >= k){
            cout << y << " " << z << endl;
            break;
          }else{
            k -= m;
            if(!ms.count(y)){
              q.push(y);
            }
            ms[y] += m;
            if(!ms.count(z)){
              q.push(z);
            }
            ms[z] += m;
          }
        }
    }
    return 0;
}

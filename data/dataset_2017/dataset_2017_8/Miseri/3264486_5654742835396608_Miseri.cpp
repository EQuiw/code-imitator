#include<bits/stdc++.h>
#define pb   push_back
using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<ll> pii;

ll T, n, k;

map<ll,ll> cc;

int main(){
  ios_base::sync_with_stdio(false);cin.tie(0);
  cin >> T;
  for(int it=0;it<T;it++){
    cc.clear();
    cin >> n >> k;
    ll sf = 0, last=0;
    priority_queue<ll> pq;
    pq.push(n); cc[n] = 1;
    while(sf<k){
      assert(!pq.empty());
      ll c = pq.top(), n1 = c/2, n2 = c-n1-1;
      //cout << c << " " << cc[c] <<endl;
      pq.pop();
      if (cc.count(n1)) cc[n1]+=cc[c];
      else cc[n1] = cc[c], pq.push(n1);
      if (cc.count(n2)) cc[n2]+=cc[c];
      else cc[n2] = cc[c], pq.push(n2);
      sf+=cc[c];
      last = c;
    }
    cout<< "Case #" << it+1 << ": " << last/2<< " "<< last - last/2-1 <<endl;
  }
}

// satyaki3794
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> ii;

ll pwr(ll base, ll p, ll mod = (1000000007LL)) {
  ll ans = 1;
  while (p) {
    if (p & 1)
      ans = (ans * base) % mod;
    base = (base * base) % mod;
    p /= 2;
  }
  return ans;
}

ll gcd(ll a, ll b) {
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

struct compare {
  bool operator()(const ii &a, const ii &b) const {
    if ((a.first - 1) / 2 != (b.first - 1) / 2)
      return a.first > b.first;
    return (a.first - 1 - (a.first - 1) / 2) >
           (b.first - 1 - (b.first - 1) / 2);
  }
};

set<ii> arr;

int main() {

  ios_base::sync_with_stdio(0);
  cin.tie(0);

  freopen("C-small-1-attempt1.in", "r", stdin);
  freopen("output.txt", "w", stdout);

  // for(int i=1;i<=10;i++)
  //     arr.insert(ii(i, 0));
  // for(auto it : arr)
  //     cout<<it.ff<<" ";cout<<endl;

  int t, x = 1;
  cin >> t;
  // t=1;
  while (t--) {

    ll n, k;
    cin >> n >> k;
    // k--;

    arr.clear();
    arr.insert(ii(-n, 1));
    set<ii>::iterator it;
    ll ans_l, ans_r;

    // int ctr = 0;
    while (k > 0) {

      // ctr++;
      // if(ctr == 10)   break;

      assert(!arr.empty());
      it = arr.begin();
      ii temp = (*it);
      temp.first *= -1;
      arr.erase(it);
      if (temp.second == 0)
        continue;

      // cout<<endl;
      // cout<<"now at "<<temp.ff<<" "<<temp.ss<<endl;

      ll z = min(k, temp.second);
      if (temp.second > z) {
        arr.insert(ii(-temp.first, temp.second - z));
        temp.second = z;
      }
      k -= z;

      ll l = (temp.first - 1) / 2, r = temp.first - 1 - l;
      ans_l = max(l, r);
      ans_r = min(l, r);

      // cout<<"got "<<l<<" "<<r<<" and k = "<<k<<endl;

      if (l > 0) {
        it = arr.lower_bound(ii(-l, -1));
        if (it != arr.end() && (*it).first == -l) {
          ll cnt = (*it).second + temp.second;
          arr.erase(it);
          arr.insert(ii(-l, cnt));
          // cout<<"pushed "<<l<<" "<<cnt<<" at left"<<endl;
        } else {
          ll cnt = temp.second;
          arr.insert(ii(-l, cnt));
          // cout<<"pushed "<<l<<" "<<cnt<<" at left"<<endl;
        }
      }

      if (r > 0) {
        it = arr.lower_bound(ii(-r, -1));
        if (it != arr.end() && (*it).first == -r) {
          ll cnt = (*it).second + temp.second;
          arr.erase(it);
          arr.insert(ii(-r, cnt));
          // cout<<"pushed "<<r<<" "<<cnt<<" at right"<<endl;
        } else {
          ll cnt = temp.second;
          arr.insert(ii(-r, cnt));
          // cout<<"pushed "<<r<<" "<<cnt<<" at right"<<endl;
        }
      }
    }

    cout << "Case #" << x++ << ": " << ans_l << " " << ans_r << endl;
  }

  return 0;
}

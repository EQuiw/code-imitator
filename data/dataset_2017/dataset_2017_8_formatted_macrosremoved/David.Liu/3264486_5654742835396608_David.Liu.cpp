#include <iostream>
using namespace std;
typedef long long ll;

ll min(ll a, ll b) {
  if (a == -1)
    return b;
  if (b == -1)
    return a;

  return a < b ? a : b;
}

ll f(ll n, ll k) {
  // cout<<n<<" "<<k<<endl;
  if (k == 1)
    return n - 1;
  if (k == 0)
    return -1;
  ll p = (k - 1) / 2 + (k - 1) % 2;
  ll m = (n - 1) / 2;
  if (n % 2 == 0 && k % 2 == 0)
    return min(f(m + 1, p), f(m, p - 1));
  return f(m, p);
}

int main() {
  int T;
  cin >> T;
  for (int TT = 1; TT <= T; ++TT) {
    ll n, k;
    cin >> n >> k;
    ll ans = f(n, k);
    ll a = ans / 2 + ans % 2, b = ans / 2;
    cout << "Case #" << TT << ": " << a << " " << b << endl;
  }
}

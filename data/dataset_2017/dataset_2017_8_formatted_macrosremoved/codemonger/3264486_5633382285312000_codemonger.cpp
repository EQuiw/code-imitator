#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int check(ll x) {
  int i = 0;
  ll a[20];
  while (x > 0) {
    a[i] = x % 10;
    i++;
    x /= 10;
  }
  for (int j = 0; j < i - 1; j++) {
    if (a[j] < a[j + 1]) {
      return false;
    }
  }
  return true;
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int t;
  cin >> t;

  for (int z = 1; z <= t; z++) {
    ll n;
    cin >> n;
    int count = 0;
    int flag = 0;
    while (flag == 0) {
      if (check(n) == true) {
        flag = 1;
      } else if (n % 10 == 9) {
        count++;
        n /= 10;
      } else {
        ll nn = n % 10;
        n -= (nn + 1);
      }
      // cout<<n<<endl;
    }
    cout << "Case #" << z << ": " << n;
    for (int i = 0; i < count; i++) {
      cout << '9';
    }
    cout << endl;
  }
}

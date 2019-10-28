#include <iostream>

using namespace std;

int solve(int cc) {
  long long n, k, t = 0, onell = 1LL;
  cin >> n >> k;
  while (k > 0) {
    n -= (onell << t);
    if (k > (onell << t)) {
      k -= (onell << t);
      t++;
    } else {
      break;
    }
    //        cout<<n<<" "<<k<<" "<<t<<endl;
  }
  long long solmax = 0, solmin = 0;
  if (n > 0) {
    long long tt = (onell << (t + 1));
    long long ttt = n / tt;
    long long tttt = n % tt;
    if (tttt >= k) {
      solmax = ttt + 1;
    } else {
      solmax = ttt;
    }
    tttt -= (tt / 2);
    if (tttt >= k) {
      solmin = ttt + 1;
    } else {
      solmin = ttt;
    }
  }
  cout << "Case #" << cc << ": " << solmax << " " << solmin << endl;
  return 1;
}

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; i++) {
    solve(i + 1);
  }
  return 0;
}

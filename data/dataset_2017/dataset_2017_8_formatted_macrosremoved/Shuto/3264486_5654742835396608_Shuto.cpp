#include <bits/stdc++.h>
using namespace std;
typedef pair<long long int, long long int> PI;
typedef pair<long long int, long long int> PI;

inline void solve() {
  long long int n, k;
  cin >> n >> k;
  priority_queue<long long int> pq;
  pq.push(n);
  for (long long int i = 0; i < ((long long int)(k - 1)); i++) {
    long long int now = pq.top();
    pq.pop();
    --now;
    pq.push(now / 2);
    pq.push(now - now / 2);
  }
  long long int res = pq.top();
  --res;
  cout << res - res / 2 << " " << res / 2;
}

int main() {
  long long int t;
  cin >> t;
  for (long long int case_num = 0; case_num < ((long long int)(t));
       case_num++) {
    cout << "Case #" << case_num + 1 << ": ";
    solve();
    cout << endl;
  }

  return 0;
}

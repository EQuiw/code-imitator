#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
int main() {
  freopen("C-small-1-attempt0.in", "r", stdin);
  freopen("CSOut.txt", "w", stdout);

  int T, N, K;
  cin >> T;
  for (int ca = 1; ca <= T; ca++) {
    cin >> N >> K;
    priority_queue<int> pq;
    pq.push(N);
    int now;
    for (int i = 0; i < K - 1; i++) {
      now = (pq.top());
      pq.pop();
      if (now % 2 == 0) {
        pq.push(now / 2);
        pq.push((now - 1) / 2);
      } else {
        pq.push(now / 2);
        pq.push(now / 2);
      }
      // cout << now << "\n";
    }
    now = (pq.top());
    int A, B;
    if (now % 2 == 0) {
      A = now / 2;
      B = (now - 1) / 2;
    } else {
      A = now / 2;
      B = now / 2;
    }
    cout << "Case #" << ca << ": ";
    cout << A << " " << B << "\n";
  }
  return 0;
}

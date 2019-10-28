#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
int main() {

  int n, m, t;
  cin >> t;
  for (int j = 0; j < t; j++) {
    cin >> n >> m;
    priority_queue<int> pq;
    pq.push(n);
    m--;
    while (m--) {
      int l = (pq.top() - 1) / 2, r = (pq.top()) / 2;
      pq.pop();
      if (l)
        pq.push(l);
      if (r)
        pq.push(r);
    }
    int l = (pq.top()) / 2, r = (pq.top() - 1) / 2;
    cout << "Case #" << j + 1 << ": " << l << " " << r << endl;
  }
}

#include <bits/stdc++.h>

using namespace std;

priority_queue<int> q;

long long n, k;
int t;
void work(int ca) {
  while (!q.empty())
    q.pop();
  cin >> n >> k;
  q.push(n);
  long long now, l, r;
  while (k--) {
    now = q.top();
    q.pop();
    if (now & 1) {
      l = now / 2;
      r = now / 2;
      q.push(l);
      q.push(r);
    } else {
      l = now / 2;
      r = now / 2 - 1;
      q.push(l);
      q.push(r);
    }
  }
  cout << "Case #" << ca << ": " << l << ' ' << r << endl;
}
int main() {
  cin >> t;
  for (int i = 1; i <= t; i++)
    work(i);
  return 0;
}

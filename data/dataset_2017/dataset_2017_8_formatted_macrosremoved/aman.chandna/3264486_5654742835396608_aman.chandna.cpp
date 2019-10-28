

#include <bits/stdc++.h>
#include <unordered_map>
#include <unordered_set>
using namespace std;

int main() {

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  ;
  freopen("inp.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
  long long t;
  cin >> t;
  for (long long ccr = 1; ccr <= t; ++ccr) {

    long long n, k, val1, val2;
    cin >> n >> k;
    priority_queue<long long, vector<long long>, less<long long>> pq;
    pq.push(n);
    while (k--) {
      long long val = pq.top();
      pq.pop();
      val1 = val2 = val / 2;
      if (val % 2 == 0) {
        --val2;
      }
      pq.push(val1);
      pq.push(val2);
    }

    cout << "Case #" << ccr << ": " << val1 << " " << val2 << "\n";
  }
  return 0;
}

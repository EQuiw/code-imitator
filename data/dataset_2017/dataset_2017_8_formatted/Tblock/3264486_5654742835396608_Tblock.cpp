#include <iostream>
#include <queue>
#include <string>

using namespace std;

typedef long long ll;

int main() {

  int t;
  cin >> t;
  int cas = 1;
  while (t--) {
    cout << "Case #" << cas << ": ";
    cas++;

    ll n, k;
    cin >> n >> k;

    priority_queue<ll> intervals = priority_queue<ll>();
    intervals.push(n);

    // insert (k - 1) people
    for (int i = 0; i < k - 1; i++) {
      ll next = intervals.top();
      intervals.pop();
      intervals.push((next - 1) / 2);
      intervals.push(next / 2);
    }

    cout << intervals.top() / 2 << " " << (intervals.top() - 1) / 2 << endl;
  }

  return 0;
}
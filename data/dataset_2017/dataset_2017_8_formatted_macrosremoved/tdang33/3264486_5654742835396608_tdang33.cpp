#include <iostream>
// #include <cmath>
// #include <string>
#include <queue>

using namespace std;

vector<long long> solve(long long n, long long k) {
  vector<long long> result;
  priority_queue<long long> q;
  q.push(n);
  long long ma, mi;
  while (k > 0) {
    long long t = q.top();
    q.pop();
    ma = t / 2, mi = (t % 2 ? t / 2 : t / 2 - 1);
    q.push(ma);
    q.push(mi);
    k--;
  }
  result.push_back(ma);
  result.push_back(mi);
  return result;
}

int main() {
  int T;
  cin >> T;
  for (int i = 0; i < T; i++) {
    long long n;
    cin >> n;
    long long k;
    cin >> k;
    vector<long long> result = solve(n, k);
    // long long l = t/2;
    cout << "Case #" << i + 1 << ": " << result[0] << " " << result[1] << endl;
  }
  return 0;
}

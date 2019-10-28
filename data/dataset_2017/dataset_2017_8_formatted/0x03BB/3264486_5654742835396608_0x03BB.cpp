#include <iostream>
#include <queue>
using namespace std;

int main() {
  int nCase;
  cin >> nCase;
  for (int iCase = 1; iCase <= nCase; ++iCase) {
    long long n, k;
    cin >> n >> k;
    priority_queue<long long> bath_len;
    bath_len.push(n);
    for (int i = 1; i < k; ++i) {
      long long max_bath = bath_len.top();
      if (max_bath == 0) {
        break;
      }
      bath_len.pop();
      --max_bath;
      bath_len.push(max_bath >> 1);
      bath_len.push((max_bath >> 1) + (max_bath & 1));
    }
    long long last_bath = bath_len.top();
    if (last_bath > 0) {
      --last_bath;
    }
    long long max_ans = (last_bath >> 1) + (last_bath & 1);
    long long min_ans = (last_bath >> 1);
    cout << "Case #" << iCase << ": " << max_ans << " " << min_ans << endl;
    while (!bath_len.empty()) {
      bath_len.pop();
    }
  }
}
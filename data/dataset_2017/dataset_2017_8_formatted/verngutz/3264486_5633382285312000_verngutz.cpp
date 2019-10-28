#include <iostream>
#define NEG_INF -4999999999999999999LL
using namespace std;

int T;
long long N;
int n;
long long digits[19];
long long ten[19];

long long opt(int i, int last, bool strict) {
  if (i == 0) {
    return 0;
  } else if (strict) {
    long long ans = NEG_INF;
    for (int x = last; x < digits[i]; x++) {
      ans = max(ans, x * ten[i - 1] + opt(i - 1, x, false));
    }
    if (digits[i] >= last) {
      ans = max(ans, digits[i] * ten[i - 1] + opt(i - 1, digits[i], true));
    }
    return ans;
  } else {
    return 9 * ten[i - 1] + opt(i - 1, 9, false);
  }
}
int main() {
  ten[0] = 1;
  for (int i = 1; i < 19; i++) {
    ten[i] = ten[i - 1] * 10;
  }
  cin >> T;
  for (int t = 1; t <= T; t++) {
    cin >> N;
    for (n = 1; N > 0; n++) {
      digits[n] = N % 10;
      N /= 10;
    }
    n--;
    cout << "Case #" << t << ": " << opt(n, 0, true) << endl;
  }
  return 0;
}
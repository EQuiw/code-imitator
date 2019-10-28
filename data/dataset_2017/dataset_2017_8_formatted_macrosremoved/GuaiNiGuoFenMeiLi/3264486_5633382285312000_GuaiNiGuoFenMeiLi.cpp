#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

long long solve(long long n) {
  vector<int> b;
  for (long long i = n; i; i /= 10) {
    b.push_back(i % 10);
  }
  reverse(b.begin(), b.end());
  size_t j = b.size() - 1;
  for (size_t i = 1; i < b.size(); ++i) {
    if (b[i] < b[i - 1]) {
      j = i - 1;
      break;
    }
  }
  if (j == b.size() - 1) {
    return n;
  }
  size_t k = 0;
  for (size_t i = j; i > 0; --i) {
    if (i - 1 >= 0 && b[i] > b[i - 1]) {
      k = i;
      break;
    }
  }
  b[k]--;
  for (size_t i = k + 1; i < b.size(); ++i) {
    b[i] = 9;
  }
  long long r = 0;
  for (size_t i = 0; i < b.size(); ++i) {
    r = r * 10 + b[i];
  }
  return r;
}

int main() {
  freopen("B-small-attempt1.in", "r", stdin);
  freopen("B-small-attempt1.out", "w", stdout);

  int T;
  cin >> T;
  for (int test = 1; test <= T; ++test) {
    long long N;
    cin >> N;
    // cout << N << " " << solve(N) << endl;
    cout << "Case #" << test << ": " << solve(N) << endl;
  }

  return 0;
}

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const long long TEN_TO_18 = 1000000000000000000;

void print(int testNo, long long ans) {
  cout << "Case #" << testNo << ": " << ans << endl;
}

long long getLastTidy(long long n) {
  for (long long i = 10; i <= TEN_TO_18; i *= 10) {
    long long l = n / i;
    if (l == 0L)
      break;

    l %= 10;
    long long r = (n / (i / 10)) % 10;

    if (l > r) {
      n /= i;
      n *= i;
      --n;
    }
  }

  return n;
}

int main() {
  int totalTestNo;
  cin >> totalTestNo;
  for (int testNo = 1; testNo <= totalTestNo; ++testNo) {
    long long n;
    cin >> n;
    long long tidy = getLastTidy(n);
    print(testNo, tidy);
  }
}

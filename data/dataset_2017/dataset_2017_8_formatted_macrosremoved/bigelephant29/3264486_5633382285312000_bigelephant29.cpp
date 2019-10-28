#include <cstdio>
using namespace std;
const int MAX = 20;
long long arr[MAX];

bool check(long long tmp) {
  long long last = 9;
  while (tmp) {
    long long now = tmp % 10;
    if (now > last)
      return false;
    last = now;
    tmp /= 10;
  }
  return true;
}

long long next(long long now) {
  arr[0] = 9;
  int cnt = 1;
  while (now) {
    arr[cnt++] = now % 10;
    now /= 10;
  }
  int high;
  for (high = cnt - 1; high > 0; high--) {
    if (arr[high] > arr[high - 1])
      break;
  }
  long long ans = 0;
  for (int i = cnt - 1; i > 0; i--) {
    ans = ans * 10;
    if (i >= high)
      ans += arr[i];
  }
  if (high > 0)
    ans--;
  return ans;
}

int main() {
  int TN;
  scanf("%d", &TN);
  for (int casen = 1; casen <= TN; casen++) {
    printf("Case #%d: ", casen);
    long long n;
    scanf("%lld", &n);
    long long ans = next(n);
    while (!check(ans)) {
      ans = next(ans);
    }
    printf("%lld\n", ans);
  }
  return 0;
}

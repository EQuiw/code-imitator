#include <cstdio>
#include <map>
using namespace std;

int main() {
  int TN;
  scanf("%d", &TN);
  for (int casen = 1; casen <= TN; casen++) {
    printf("Case #%d: ", casen);
    int n, k, ansx = -1, ansy = -1;
    scanf("%d %d", &n, &k);
    map<int, int> mp;
    mp[n] = 1;
    while (k > 0) {
      int len = mp.rbegin()->first;
      int cnt = mp.rbegin()->second;
      mp.erase(len);
      k -= cnt;
      ansx = len / 2, ansy = (len - 1) / 2;
      mp[ansx] += cnt;
      mp[ansy] += cnt;
    }
    printf("%d %d\n", ansx, ansy);
  }
  return 0;
}

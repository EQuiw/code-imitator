#include <iostream>
#include <map>
#include <stdio.h>
using namespace std;

int T;
long long int N;
long long int K;
map<long long int, long long int> d;

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int t;

  cin >> T;
  for (t = 1; t <= T; t++) {
    scanf("%lld %lld\n", &N, &K);

    d.clear();
    d[N] = 1;

    long long int pos = 0;
    long long int res;
    while (true) {
      auto current = d.rbegin();
      if (pos + current->second >= K) {
        res = current->first;
        break;
      }
      d[(current->first - 1) / 2] += current->second;
      d[(current->first - 1) / 2 + (current->first - 1) % 2] += current->second;
      pos += current->second;
      d.erase(current->first);
    }
    printf("Case #%d: ", t);
    printf("%lld %lld\n", (res - 1) / 2 + (res - 1) % 2, (res - 1) / 2);
  }
  return 0;
}

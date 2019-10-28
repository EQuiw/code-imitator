#include <bits/stdc++.h>
using namespace std;

int main() {
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++) {
    long long N, K;
    cin >> N;
    cin >> K;

    int L = 0;
    long long Z = K;
    while (Z > (1LL << L)) {
      Z -= 1LL << L;
      L++;
    }
    long long B = (N + 1) % (1 << L);
    long long T = (N + 1 - (1 << L)) / (1 << L);
    cout << "Case #" << t << ": ";
    if (Z <= B)
      cout << (T + 1) / 2 << " " << T / 2;
    else
      cout << T / 2 << " " << (T - 1) / 2;
    cout << endl;
  }
  return 0;
}

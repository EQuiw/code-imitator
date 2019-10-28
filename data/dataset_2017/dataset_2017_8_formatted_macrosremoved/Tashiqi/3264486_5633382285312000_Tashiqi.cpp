#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;
static const long long D = 1000000007;

int main() {
  long long T, N;
  cin >> T;
  for (long long t = 0; t < T; ++t) {
    cin >> N;
    vector<int> V;
    while (N != 0) {
      V.push_back(N % 10);
      N /= 10;
    }
    for (unsigned int i = 0; i < V.size() - 1; ++i) {
      if (V[i] < V[i + 1]) {
        --V[i + 1];
        for (unsigned int j = 0; j <= i; ++j)
          V[j] = 9;
      }
    }
    for (int i = V.size() - 1; i >= 0; --i)
      N = 10 * N + V[i];
    cout << "Case #" << t + 1 << ": " << N << endl;
  }
  return 0;
}

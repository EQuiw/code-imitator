#include <bits/stdc++.h>
using namespace std;

int main() {
  int T;
  cin >> T;
  cout.precision(15);
  for (int testCase = 1; testCase <= T; testCase++) {
    cout << "Case #" << testCase << ": ";
    int D, N;
    cin >> D;
    cin >> N;
    double endTime = 0;
    for (int i = 0; i < N; i++) {
      int K, S;
      cin >> K;
      cin >> S;
      endTime = max(endTime, double(D - K) / S);
    }
    cout << D / endTime;
    cout << endl;
  }
  return 0;
}

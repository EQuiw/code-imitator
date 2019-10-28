#include <bits/stdc++.h>
using namespace std;

int main() {
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++) {
    cout << "Case #" << t << ": ";

    string S;
    cin >> S;
    for (int i = 0; i < S.size() - 1; i++)
      if (S[i] > S[i + 1]) {
        S[i]--;
        for (int j = i + 1; j < S.size(); j++)
          S[j] = '9';
        for (int j = i - 1; j >= 0; j--)
          if (S[j] > S[j + 1]) {
            S[j]--;
            S[j + 1] = '9';
          }
        break;
      }
    cout << stoll(S) << endl;
  }
}

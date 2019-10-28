#include <bits/stdc++.h>

using namespace std;

vector<string> split(const string &text) { // split string by space
  vector<string> vys;
  stringstream ss(text);
  string word;
  while (getline(ss, word, ' ')) {
    vys.push_back(word);
  }
  return vys;
}

int main() {
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++) {
    int K;
    string S;
    cin >> S;
    cin >> K;
    int flips = 0;
    for (int i = 0; i < S.length() + 1 - K; i++) {
      if (S[i] == '-') {
        flips++;
        for (int j = i; j < i + K; j++) {
          S[j] = (S[j] == '-') ? '+' : '-';
        }
      }
    }
    for (int i = S.length() + 1 - K; i < S.length(); i++) {
      if (S[i] == '-') {
        flips = -1;
        break;
      }
    }
    cout << "Case #" << t << ": ";
    cout << (flips < 0 ? "IMPOSSIBLE" : to_string(flips)) << endl;
  }
  return 0;
}

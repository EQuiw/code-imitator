#include <iostream>
#include <string>

using namespace std;

int main() {
  int T;
  cin >> T;
  for (int i = 0; i < T; ++i) {
    string s;
    int k;
    int count = 0;
    cin >> s >> k;
    for (int j = 0; j < s.size() - k + 1; ++j) {
      if (s[j] == '-') {
        ++count;
        s[j] = '+';
        for (int l = j + 1; l < j + k; ++l) {
          if (s[l] == '-')
            s[l] = '+';
          else
            s[l] = '-';
        }
      }
    }
    bool valid = true;
    for (int j = s.size() - k + 1; j < s.size(); ++j) {
      if (s[j] == '-') {
        valid = false;
        break;
      }
    }
    if (valid)
      cout << "Case #" << i + 1 << ": " << count << "\n";
    else
      cout << "Case #" << i + 1 << ": IMPOSSIBLE\n";
  }
}

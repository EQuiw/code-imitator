#include <iostream>

using namespace std;

int solve(int cc) {
  string str;
  int k;
  bool sol = true;
  int count = 0;
  cin >> str >> k;
  for (int i = 0; i < str.length(); i++) {
    if (str[i] == '-') {
      if (i + k - 1 < str.length()) {
        for (int j = i; j < i + k; j++) {
          if (str[j] == '-') {
            str[j] = '+';
          } else {
            str[j] = '-';
          }
        }
        count++;
      } else {
        sol = false;
      }
    }
    //        cout<<str<<endl;
  }
  if (sol) {
    cout << "Case #" << cc << ": " << count << endl;
  } else {
    cout << "Case #" << cc << ": IMPOSSIBLE" << endl;
  }
  return 1;
}

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; i++) {
    solve(i + 1);
  }
  return 0;
}

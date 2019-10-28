#include <iostream>

using namespace std;

bool legal(string s, int k) {
  if (k == s.size() - 1) {
    return true;
  }
  for (int i = k; i < s.size(); ++i) {
    if (s[i] > s[k]) {
      return true;
    }
    if (s[i] < s[k]) {
      return false;
    }
  }
  return true;
}

bool judge(int k) {
  if (k == 1000) {
    return false;
  }
  int a = k / 100;
  int b = k / 10 % 10;
  int c = k % 10;
  if (a <= b && b <= c) {
    return true;
  } else {
    return false;
  }
}

int main() {
  int T;
  cin >> T;
  for (int c = 1; c <= T; ++c) {
    cout << "Case #" << c << ": ";
    /*
    int N;
    cin >> N;
    for (int j = N; j >= 1; --j) {
            if (judge(j)) {
                    cout << j << endl;
                    break;
            }
    }*/
    string s;
    cin >> s;
    for (int i = 0; i < s.size(); ++i) {
      if (!legal(s, i)) {
        --s[i];
        if (i != 0 || s[i] != '0') {
          cout << s[i];
        }
        for (int j = i + 1; j < s.size(); ++j) {
          cout << '9';
        }
        break;
      } else {
        cout << s[i];
      }
    }
    cout << endl;
  }
  return 0;
}

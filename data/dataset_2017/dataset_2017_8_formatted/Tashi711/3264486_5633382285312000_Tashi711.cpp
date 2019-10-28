#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

void work() {
  string s;
  cin >> s;
  int pos;
  for (int c = 1; c <= 18; ++c) {
    pos = -1;
    for (int i = 0; i < (int)s.size() - 1; ++i) {
      if (s[i] > s[i + 1]) {
        s[i]--;
        pos = i + 1;
        break;
      }
    }
    if (pos != -1) {
      for (int i = pos; i < (int)s.size(); ++i) {
        s[i] = '9';
      }
    }
  }
  for (int i = 0; i < (int)s.size(); ++i) {
    if (s[i] != '0') {
      pos = i;
      break;
    }
  }
  for (int i = pos; i < (int)s.size(); ++i) {
    cout << s[i];
  }
  cout << endl;
}

int main() {
  freopen("my.in", "r", stdin);
  freopen("out.txt", "w", stdout);
  int q;
  cin >> q;
  for (int i = 1; i <= q; ++i) {
    printf("Case #%d: ", i);
    work();
  }
  return 0;
}

#include <bits/stdc++.h>
using namespace std;

int main() {
  int T;
  cin >> T;
  for (int testCase = 1; testCase <= T; testCase++) {
    cout << "Case #" << testCase << ": ";
    int N, R, RY, Y, YB, B, RB;
    cin >> N;
    cin >> R;
    cin >> RY;
    cin >> Y;
    cin >> YB;
    cin >> B;
    cin >> RB;
    int n = N;
    int r = R;
    int ry = RY;
    int y = Y;
    int yb = YB;
    int b = B;
    int rb = RB;
    while (n > 3 && ry > 0 && b >= 2) {
      ry--;
      n -= 2;
      b -= 1;
    }
    while (n > 3 && yb > 0 && r >= 2) {
      yb--;
      n -= 2;
      r -= 1;
    }
    while (n > 3 && rb > 0 && y >= 2) {
      rb--;
      n -= 2;
      y -= 1;
    }
    vector<char> ans(n, ' ');
    if (n == 2 && ry == 1 && b == 1)
      ans = {'O', 'B'};
    else if (n == 2 && yb == 1 && r == 1)
      ans = {'G', 'R'};
    else if (n == 2 && rb == 1 && y == 1)
      ans = {'V', 'Y'};
    else if (ry > 0 || yb > 0 || rb > 0) {
      cout << "IMPOSSIBLE" << endl;
      continue;
    } else if (2 * r > n || 2 * y > n || 2 * b > n) {
      cout << "IMPOSSIBLE" << endl;
      continue;
    } else {
      if (r >= y && r >= b) {
        for (int i = 0; i < r; i++)
          ans[2 * i] = 'R';
        if (y >= b) {
          for (int i = r; i < r + y; i++) {
            if (ans[2 * i % n] == ' ')
              ans[2 * i % n] = 'Y';
            else
              ans[2 * i % n + 1] = 'Y';
          }
          for (int i = 0; i < n; i++) {
            if (ans[i] == ' ')
              ans[i] = 'B';
          }
        } else {
          for (int i = r; i < r + b; i++) {
            if (ans[2 * i % n] == ' ')
              ans[2 * i % n] = 'B';
            else
              ans[2 * i % n + 1] = 'B';
          }
          for (int i = 0; i < n; i++) {
            if (ans[i] == ' ')
              ans[i] = 'Y';
          }
        }
      } else if (y >= r && y >= b) {
        for (int i = 0; i < y; i++)
          ans[2 * i] = 'Y';
        if (r >= b) {
          for (int i = y; i < y + r; i++) {
            if (ans[2 * i % n] == ' ')
              ans[2 * i % n] = 'R';
            else
              ans[2 * i % n + 1] = 'R';
          }
          for (int i = 0; i < n; i++) {
            if (ans[i] == ' ')
              ans[i] = 'B';
          }
        } else {
          for (int i = y; i < y + b; i++) {
            if (ans[2 * i % n] == ' ')
              ans[2 * i % n] = 'B';
            else
              ans[2 * i % n + 1] = 'B';
          }
          for (int i = 0; i < n; i++) {
            if (ans[i] == ' ')
              ans[i] = 'R';
          }
        }
      } else {
        for (int i = 0; i < b; i++)
          ans[2 * i] = 'B';
        if (r >= y) {
          for (int i = b; i < b + r; i++) {
            if (ans[2 * i % n] == ' ')
              ans[2 * i % n] = 'R';
            else
              ans[2 * i % n + 1] = 'R';
          }
          for (int i = 0; i < n; i++) {
            if (ans[i] == ' ')
              ans[i] = 'Y';
          }
        } else {
          for (int i = b; i < b + y; i++) {
            if (ans[2 * i % n] == ' ')
              ans[2 * i % n] = 'Y';
            else
              ans[2 * i % n + 1] = 'Y';
          }
          for (int i = 0; i < n; i++) {
            if (ans[i] == ' ')
              ans[i] = 'R';
          }
        }
      }
    }
    for (int i = 0; i < n; i++) {
      cout << ans[i];
      if (ans[i] == 'R')
        while (yb < YB) {
          cout << "GR";
          yb++;
        }
      if (ans[i] == 'Y')
        while (rb < RB) {
          cout << "VY";
          rb++;
        }
      if (ans[i] == 'B')
        while (ry < RY) {
          cout << "OB";
          ry++;
        }
    }
    cout << endl;
  }
  return 0;
}

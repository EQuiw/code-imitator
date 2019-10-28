// Problem B

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

int get() {
  char c;
  while (c = getchar(), c != '-' && (c < '0' || c > '9'))
    ;
  bool flag = (c == '-');
  if (flag)
    c = getchar();
  int x = 0;
  while (c >= '0' && c <= '9') {
    x = x * 10 + c - '0';
    c = getchar();
  }
  return flag ? -x : x;
}

int R, O, Y, G, B, V;

void imp() { printf("IMPOSSIBLE"); }

void alt(char c1, char c2, int n) {
  for (int i = 0; i < n; i++) {
    putchar(c1);
    putchar(c2);
  }
}

void solve(char a, char b, char c, int A, int B, int C) {
  string s = "";
  while (B && C) {
    s += b;
    s += c;
    B--;
    C--;
  }
  while (B--)
    s += b;
  while (C--)
    s += c;
  for (int i = 0; i < A; i++) {
    int len = s.size();
    if (s[0] == s[len - 1] && s[0] != a)
      s += a;
    else {
      int p = -1;
      for (int j = 0; j + 1 < len; j++)
        if (s[j] == s[j + 1] && s[j] != a)
          p = j;
      if (p == -1) {
        for (int j = 0; j + 1 < len; j++)
          if ((s[j] == b && s[j + 1] == c) || (s[j] == c && s[j + 1] == b))
            p = j;
      }
      string t = "";
      for (int j = 0; j <= p; j++)
        t += s[j];
      t += a;
      for (int j = p + 1; j < len; j++)
        t += s[j];
      s = t;
    }
  }
  bool flag[128];
  memset(flag, 0, sizeof(flag));
  for (int i = 0; i < s.size(); i++) {
    char x = s[i];
    putchar(x);
    if (!flag[x]) {
      flag[x] = true;
      if (x == 'R')
        alt('G', 'R', G);
      else if (x == 'B')
        alt('O', 'B', O);
      else
        alt('V', 'Y', V);
    }
  }
}

int main() {
  int totalTest = get();
  for (int test = 1; test <= totalTest; test++) {
    printf("Case #%d: ", test);
    int N = get();
    R = get();
    O = get();
    Y = get();
    G = get();
    B = get();
    V = get();
    if (R == G && N == R + G)
      alt('R', 'G', R);
    else if (B == O && N == B + O)
      alt('B', 'O', B);
    else if (Y == V && N == Y + V)
      alt('Y', 'V', Y);
    else if ((R <= G && G > 0) || (B <= O && O > 0) || (Y <= V && V > 0))
      imp();
    else {
      R -= G;
      B -= O;
      Y -= V;
      int freq = max(R, max(B, Y));
      if (freq > N / 2)
        imp();
      else {
        if (freq == R)
          solve('R', 'B', 'Y', R, B, Y);
        else if (freq == 'B')
          solve('B', 'Y', 'R', B, Y, R);
        else
          solve('Y', 'R', 'B', Y, R, B);
      }
    }
    putchar('\n');
  }
  return 0;
}

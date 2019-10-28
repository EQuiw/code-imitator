#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

int N, R, O, Y, G, B, V;
char color[1005];

string solve() {
  int numcolor = 0;
  if (R)
    numcolor++;
  if (Y)
    numcolor++;
  if (B)
    numcolor++;
  if (numcolor == 1)
    return "IMPOSSIBLE";
  int maxn;
  if (numcolor == 2)
    maxn = N / numcolor;
  else
    maxn = (N + numcolor - 1) / numcolor;
  string ret;
  if (R > maxn || Y > maxn || B > maxn)
    return ret = "IMPOSSIBLE";
  else {
    int pos = 0;
    if (R) {
      for (int i = 0; i < R; i++) {
        color[pos % N] = 'R';
        pos += 3;
      }
    }
    if (Y) {
      pos++;
      for (int i = 0; i < Y; i++) {
        color[pos % N] = 'Y';
        pos += 3;
      }
    }
    if (B) {
      pos++;
      for (int i = 0; i < B; i++) {
        color[pos % N] = 'B';
        pos += 3;
      }
    }
    ret = string(color);
  }
  return ret;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int t = 1; t <= T; t++) {
    scanf("%d%d%d%d%d%d%d", &N, &R, &O, &Y, &G, &B, &V);
    string ans = solve();
    printf("Case #%d: %s\n", t, ans.c_str());
  }
  return 0;
}
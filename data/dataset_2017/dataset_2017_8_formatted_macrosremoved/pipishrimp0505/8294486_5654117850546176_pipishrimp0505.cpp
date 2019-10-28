#include <cstdio>
#include <iostream>

using namespace std;

int n, R, O, Y, G, B, V;

void Print(int j) {
  if (j == 1) {
    if (G > 0) {
      printf("RGR");
      G--;
    } else {
      printf("R");
    }
  } else if (j == 2) {
    if (V > 0) {
      printf("YVY");
      V--;
    } else {
      printf("Y");
    }
  } else {
    if (O > 0) {
      printf("BOB");
      O--;
    } else {
      printf("B");
    }
  }
}

void solve1() { // R 最大
  int p = B + Y - R;
  if (p < 0) {
    printf("IMPOSSIBLE\n");
    return;
  }
  for (int i = 1; i <= p; i++) {
    Print(1);
    Print(2);
    Print(3);
  }
  R -= p, Y -= p, B -= p;
  for (int i = 1; i <= Y; i++)
    Print(1), Print(2);
  for (int i = 1; i <= B; i++)
    Print(1), Print(3);
  printf("\n");
}

void solve2() { // B 最大
  int p = Y + R - B;
  if (p < 0) {
    printf("IMPOSSIBLE\n");
    return;
  }
  for (int i = 1; i <= p; i++) {
    Print(3);
    Print(1);
    Print(2);
  }
  R -= p, Y -= p, B -= p;
  for (int i = 1; i <= R; i++)
    Print(3), Print(1);
  for (int i = 1; i <= Y; i++)
    Print(3), Print(2);
  printf("\n");
}

void solve3() {
  int p = B + R - Y;
  // printf("%d\n", p);
  if (p < 0) {
    printf("IMPOSSIBLE\n");
    return;
  }
  for (int i = 1; i <= p; i++) {
    Print(2);
    Print(1);
    Print(3);
  }
  R -= p, Y -= p, B -= p;
  for (int i = 1; i <= B; i++)
    Print(2), Print(3);
  for (int i = 1; i <= R; i++)
    Print(2), Print(1);
  printf("\n");
}

int main() {
  freopen("B-small-attempt2.in", "r", stdin);
  freopen("B-small-attempt2.out", "w", stdout);
  int T, cnt = 0;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d%d%d%d%d", &n, &R, &O, &Y, &G, &B, &V);
    R -= G, B -= O, Y -= V;
    // printf("%d %d %d\n", R, B, Y);
    printf("Case #%d: ", ++cnt);
    if (R < G || B < O || Y < V) {
      printf("IMPOSSIBLE\n");
      continue;
    }
    // printf("%d %d %d\n", B, R, Y);
    if (R >= B && R >= Y)
      solve1();
    else if (B >= R && B >= Y)
      solve2();
    else
      solve3();
  }
}

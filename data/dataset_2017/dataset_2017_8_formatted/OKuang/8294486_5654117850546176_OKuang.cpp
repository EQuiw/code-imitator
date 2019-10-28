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

void solve1() {
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
  R -= p;
  Y -= p;
  B -= p;
  for (int i = 1; i <= Y; i++) {
    Print(1);
    Print(2);
  }
  for (int i = 1; i <= B; i++) {
    Print(1);
    Print(3);
  }
  printf("\n");
}
void solve2() {
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
  R -= p;
  Y -= p;
  B -= p;
  for (int i = 1; i <= R; i++) {
    Print(3);
    Print(1);
  }
  for (int i = 1; i <= Y; i++) {
    Print(3);
    Print(2);
  }
  printf("\n");
}
void solve3() {
  int p = B + R - Y;
  if (p < 0) {
    printf("IMPOSSIBLE\n");
    return;
  }
  for (int i = 1; i <= p; i++) {
    Print(2);
    Print(1);
    Print(3);
  }
  R -= p;
  Y -= p;
  B -= p;
  for (int i = 1; i <= B; i++) {
    Print(2);
    Print(3);
  }
  for (int i = 1; i <= R; i++) {
    Print(2);
    Print(1);
  }
  printf("\n");
}
int main() {
  freopen("small.in", "r", stdin);
  freopen("small.out", "w", stdout);
  int T;
  scanf("%d", &T);
  for (int tcas = 1; tcas <= T; tcas++) {
    printf("Case #%d: ", tcas);
    scanf("%d%d%d%d%d%d%d", &n, &R, &O, &Y, &G, &B, &V);
    if (R >= B && R >= Y)
      solve1();
    else if (B >= R && B >= Y)
      solve2();
    else
      solve3();
  }
}

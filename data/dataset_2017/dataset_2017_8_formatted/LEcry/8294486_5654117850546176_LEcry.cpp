//============================================================================
// Name        : A.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#define MAXN 100050
#define eps 1e-8
#define max(x, y) ((x) > (y) ? (x) : (y))
#define min(x, y) ((x) < (y) ? (x) : (y))
using namespace std;
int R, O, Y, G, B, V;
// RYB
// O RY
// G YB
// V RB
struct node {
  char c;
  int num;
  node() {}
  node(char cc, int numm) {
    c = cc;
    num = numm;
  }
} s[5];
bool cmp(node a, node b) { return a.num > b.num; }
char ans[MAXN];
int main() {
  freopen("B-small-attempt1.in", "r", stdin);
  freopen("B-small-attempt1.out", "w", stdout);
  int tt, ri = 0;
  scanf("%d", &tt);
  while (tt--) {
    int n;
    scanf("%d", &n);
    scanf("%d%d%d%d%d%d", &R, &O, &Y, &G, &B, &V);
    printf("Case #%d: ", ++ri);
    int flag = 1;
    if (B < O)
      flag = 0;
    if (B == O && B != 0) {
      if (R + Y + G + V != 0)
        flag = 0;
      else {
        for (int i = 0; i < B; ++i) {
          printf("BO");
        }
        puts("");
        continue;
      }
    }

    if (R < G)
      flag = 0;
    if (R == G && R != 0) {
      if (B + Y + O + V != 0)
        flag = 0;
      else {
        for (int i = 0; i < R; ++i) {
          printf("RG");
        }
        puts("");
        continue;
      }
    }

    if (Y < V)
      flag = 0;
    if (Y == V && Y != 0) {
      if (B + R + O + G != 0)
        flag = 0;
      else {
        for (int i = 0; i < Y; ++i) {
          printf("YV");
        }
        puts("");
        continue;
      }
    }

    Y -= V;
    R -= G;
    B -= O;
    n -= 2 * (V + G + O);
    //		printf("n:%d %d\n",n,flag);
    if (Y * 2 > n)
      flag = 0;
    if (R * 2 > n)
      flag = 0;
    if (B * 2 > n)
      flag = 0;
    if (flag == 0) {
      puts("IMPOSSIBLE");
      continue;
    }
    s[0] = node('Y', Y);
    s[1] = node('R', R);
    s[2] = node('B', B);
    sort(s, s + 3, cmp);
    //		printf("%d %d %d\n",s[0].num,s[1].num,s[2].num);
    for (int i = 0; i < n; i += 2) {
      if (s[0].num > 0) {
        s[0].num--;
        ans[i] = s[0].c;
      } else if (s[1].num > 0) {
        s[1].num--;
        ans[i] = s[1].c;
      } else {
        s[2].num--;
        ans[i] = s[2].c;
      }
    }
    for (int i = 1; i < n; i += 2) {
      if (s[0].num > 0) {
        s[0].num--;
        ans[i] = s[0].c;
      } else if (s[1].num > 0) {
        s[1].num--;
        ans[i] = s[1].c;
      } else {
        s[2].num--;
        ans[i] = s[2].c;
      }
    }
    //		ans[n]=0;
    //		printf("ans:%s %d %d %d\n",ans,O,G,V);
    for (int i = 0; i < n; ++i) {
      printf("%c", ans[i]);
      if (ans[i] == 'B') {
        for (int j = 0; j < O; ++j) {
          printf("OB");
        }
        O = 0;
      }
      if (ans[i] == 'R') {
        for (int j = 0; j < G; ++j) {
          printf("GR");
        }
        G = 0;
      }
      if (ans[i] == 'Y') {
        for (int j = 0; j < V; ++j) {
          printf("VY");
        }
        V = 0;
      }
    }
    puts("");
  }
  return 0;
}

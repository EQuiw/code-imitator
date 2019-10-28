#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
typedef long long ll;
typedef pair<int, int> pt;
typedef pair<float, float> ptf;
const int base = 1000000007;
const int maxn = 102;
const float esp = 0.0001;

int n, P, res;
int R[maxn], Q[maxn][maxn], a[maxn], c[maxn];
float low[maxn], high[maxn];

bool intersect(ptf a, ptf b) {
  return (a.x <= b.x && a.y >= b.x) || (a.x >= b.x && b.y >= a.x);
}

float roundup(float x) {
  if (abs(x - int(x)) < 0.00001)
    return x;
  else
    return int(x) + 1;
}

void solve1() {
  int i, j;

  res = 0;
  for (i = 1; i <= P; i++) {
    int cando = Q[1][i] / R[1];
    float ing = cando * R[1];
    if (Q[1][i] <= 1.1 * ing + 0.0001) {
      res++;
      continue;
    }

    cando = roundup(float(Q[1][i]) / R[1]); // int(Q[1][i]/R[1])+1;
    ing = cando * R[1];
    if (Q[1][i] >= 0.9 * ing - 0.0001)
      res++;
  }
}

void solve2() {
  int i, j, k;
  ptf p1, p2;

  res = 0;
  for (i = 1; i <= P; i++)
    c[i] = i;
  do {
    int tmp = 0;
    for (i = 1; i <= P; i++)
      a[i] = Q[2][c[i]];

    for (i = 1; i <= P; i++) {
      p1.x = roundup((Q[1][i] / 1.1) / R[1]);
      while (p1.x * R[1] * 0.9 > Q[1][i] + esp)
        p1.x -= 1;
      p1.y = int((Q[1][i] / 0.9 + esp) / R[1]);
      p2.x = roundup(a[i] / 1.1 / R[2]);
      while (p2.x * R[2] * 0.9 > a[i] + esp)
        p2.x -= 1;
      p2.y = int((a[i] / 0.9 + esp) / R[2]);

      //  printf("%f %f %f %f\n",p1.x,p1.y,p2.x,p2.y);
      if (intersect(p1, p2))
        tmp++;
    }

    res = max(res, tmp);
  } while (next_permutation(c + 1, c + P + 1));
}

void solve(int test) {
  int i, j, k, v;
  char h;

  scanf("%d%d", &n, &P);
  for (i = 1; i <= n; i++)
    scanf("%d", &R[i]); // low[i] = 0.9*R[i]/; high[i] = R[i]*1.1;}
  for (i = 1; i <= n; i++)
    for (j = 1; j <= P; j++)
      scanf("%d", &Q[i][j]);

  if (n == 1)
    solve1();
  else
    solve2();

  printf("Case #%d: %d\n", test, res);
}

int main() {
  int i, t;
  freopen("b3.in", "r", stdin);
  freopen("B1.out", "w", stdout);

  scanf("%d", &t);
  for (i = 1; i <= t; i++)
    solve(i);

  return 0;
}

#include <stdio.h>
using namespace std;

int hr[1000], hs[1000], d[1000][1000];
double ans[1000];

double min1(double a, double b) {
  return a == -1 ? b : b == -1 ? a : a < b ? a : b;
}

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char **argv) {
  FILE *in = fopen("C-small-attempt0.in", "r");
  FILE *out = fopen("C-small.out", "w");
  int qw;
  fscanf(in, "%d", &qw);
  for (int qwe = 1; qwe <= qw; qwe++) {
    fprintf(out, "Case #%d: ", qwe);
    int n, q;
    fscanf(in, "%d%d", &n, &q);
    for (int i = 0; i < n; i++) {
      fscanf(in, "%d%d", &hr[i], &hs[i]);
    }
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        fscanf(in, "%d", &d[i][j]);
    for (int i = 0; i < q; i++) {
      int a, b;
      fscanf(in, "%d%d", &a, &b);
    }
    ans[n - 1] = 0;
    for (int i = n - 2; i >= 0; i--) {
      double s1, s = 0;
      for (int j = n - 1; j > i; j--)
        s += (double)d[j - 1][j];
      double a = hr[i] < s ? -1 : s / hs[i], b = -1;
      s1 = d[i][i + 1];
      double min = 0;
      for (int j = i + 1; j <= n && s1 <= hr[i]; j++) {
        if (ans[j] != -1)
          b = min1(b, ans[j] + s1 / hs[i]);
        s1 += (double)d[j][j + 1];
      }
      ans[i] = min1(a, b);
    }
    fprintf(out, "%lf\n", ans[0]);
  }
  return 0;
}

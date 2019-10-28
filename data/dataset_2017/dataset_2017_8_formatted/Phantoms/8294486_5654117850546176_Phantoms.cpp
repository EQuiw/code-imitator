#include <iostream>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
char ans[1000];

int max3(int a, int b, int c) {
  return (a >= b && a >= c) ? a : b >= c ? b : c;
}
int max(int a, int b) { return a >= b ? a : b; }

int main(int argc, char **argv) {
  FILE *in = fopen("B-small-attempt0.in", "r");
  FILE *out = fopen("B-small.out", "w");
  int qwe;
  fscanf(in, "%d", &qwe);
  for (int qw = 1; qw <= qwe; qw++) {
    fprintf(out, "Case #%d: ", qw);
    int r, o, y, g, b, v, n;
    fscanf(in, "%d%d%d%d%d%d%d", &n, &r, &o, &y, &g, &b, &v);
    int n1 = n;
    if (((g > 0 && r < g) || (r == g && n > r + g)) ||
        ((o > 0 && b < o) || (b == o && n > b + o)) ||
        ((v > 0 && y < v) || (y == v && n > y * 2 + 1)))
      fprintf(out, "IMPOSSIBLE\n");
    else {
      int i = 0;
      if (o > 0) {
        ans[i] = 'B';
        i++;
        b--;
        while (o > 0) {
          ans[i] = 'O';
          ans[i + 1] = 'B';
          b--;
          o--;
          n -= 2;
          i += 2;
        }
      }
      if (g > 0) {
        ans[i] = 'R';
        i++;
        r--;
        while (g > 0) {
          ans[i] = 'G';
          ans[i + 1] = 'R';
          r--;
          g--;
          n -= 2;
          i += 2;
        }
      }
      if (v > 0) {
        ans[i] = 'Y';
        i++;
        r--;
        while (v > 0) {
          ans[i] = 'V';
          ans[i + 1] = 'Y';
          y--;
          n -= 2;
          v--;
          i += 2;
        }
      }
      n = r + y + b;
      if (n > 0) {
        if (r * 2 > n + 1 || y * 2 > n + 1 || b * 2 > n + 1)
          fprintf(out, "IMPOSSIBLE\n");
        else {
          bool fl = true;
          while (r + y + b > 0) {
            if (i == 0) {
              if (r >= y && r >= b) {
                ans[i] = 'R';
                r--;
              } else if (y >= r && y >= b) {
                ans[i] = 'Y';
                y--;
              } else {
                ans[i] = 'B';
                b--;
              }
            } else if (ans[i - 1] == 'R') {
              if (y >= b) {
                ans[i] = 'Y';
                y--;
              } else {
                ans[i] = 'B';
                b--;
              }
            } else if (ans[i - 1] == 'B') {
              if (r >= y) {
                ans[i] = 'R';
                r--;
              } else {
                ans[i] = 'Y';
                y--;
              }
            } else {
              if (r >= b) {
                ans[i] = 'R';
                r--;
              } else {
                ans[i] = 'B';
                b--;
              }
            }

            if (r < 0 || b < 0 || y < 0)
              fl = false;
            i++;
          }
          if (ans[0] == ans[n1 - 1] && n1 > 1)
            fl = false;
          if (!fl)
            fprintf(out, "IMPOSSIBLE\n");
          else {
            for (int j = 0; j < n1; j++)
              fprintf(out, "%c", ans[j]);
            fprintf(out, "\n");
          }
        }
      } else {
        for (int j = 0; j < n1; j++)
          fprintf(out, "%c", ans[j]);
        fprintf(out, "\n");
      }
    }
  }
  return 0;
}

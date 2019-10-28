#include <iostream>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
char a[101][101];
int main(int argc, char **argv) {
  FILE *in = fopen("A-small-attempt0.in", "r");
  FILE *out = fopen("A-small.out", "w");
  int t;
  fscanf(in, "%d", &t);
  for (int q = 1; q <= t; q++) {
    fprintf(out, "Case #%d: \n", q);
    int r, m;
    fscanf(in, "%d%d", &r, &m);

    fscanf(in, "%c", &a[99][99]);
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < m; j++)
        fscanf(in, "%c", &a[i][j]);
      fscanf(in, "%c", &a[i][100]);
    }

    for (int i = 0; i < r; i++)
      for (int j = 0; j < m; j++) {
        if (a[i][j] != '?') {
          int maxi = i, maxj = j, mini = i, minj = j;
          for (int k = 0; k < r; k++)
            for (int l = 0; l < m; l++)
              if (a[k][l] == a[i][j]) {
                if (k > maxi)
                  maxi = k;
                else if (k < mini)
                  mini = k;
                if (l > maxj)
                  maxj = l;
                else if (l < minj)
                  minj = l;
              }
          for (int k = mini; k <= maxi; k++)
            for (int l = minj; l <= maxj; l++)
              a[k][l] = a[i][j];
        }
      }
    for (int i = 1; i < r; i++)
      for (int j = 0; j < m; j++)
        if (a[i][j] == '?') {
          bool fl = true;
          for (int l = 0; l < m; l++)
            if (a[i - 1][l] == a[i - 1][j] && a[i][l] != '?' &&
                a[i][l] != a[i - 1][j])
              fl = false;
          if (fl)
            a[i][j] = a[i - 1][j];
        }
    for (int i = r - 2; i >= 0; i--)
      for (int j = 0; j < m; j++)
        if (a[i][j] == '?') {
          bool fl = true;
          for (int l = 0; l < m; l++)
            if (a[i + 1][l] == a[i + 1][j] && a[i][l] != '?' &&
                a[i][l] != a[i + 1][j])
              fl = false;
          if (fl)
            a[i][j] = a[i + 1][j];
        }
    for (int i = 0; i < r; i++)
      for (int j = 1; j < m; j++)
        if (a[i][j] == '?') {
          bool fl = true;
          for (int l = 0; l < r; l++)
            if (a[l][j - 1] == a[i][j - 1] && a[l][j] != '?' &&
                a[l][j] != a[i][j - 1])
              fl = false;
          if (fl)
            a[i][j] = a[i][j - 1];
        }
    for (int i = 0; i < r; i++)
      for (int j = m - 2; j >= 0; j--)
        if (a[i][j] == '?') {
          bool fl = true;
          for (int l = 0; l < r; l++)
            if (a[l][j + 1] == a[i][j + 1] && a[l][j] != '?' &&
                a[l][j] != a[i][j + 1])
              fl = false;
          if (fl)
            a[i][j] = a[i][j + 1];
        }
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < m; j++)
        fprintf(out, "%c", a[i][j]);
      fprintf(out, "\n");
    }
  }
  return 0;
}

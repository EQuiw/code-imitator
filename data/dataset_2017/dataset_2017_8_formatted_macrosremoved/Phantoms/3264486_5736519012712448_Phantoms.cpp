#include <cstdio>
#include <string.h>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char **argv) {
  FILE *in = fopen("A-small-attempt0.in", "r");
  FILE *out = fopen("A-small.out", "w");
  int qwe;
  fscanf(in, "%d", &qwe);
  for (int qw = 1; qw <= qwe; qw++) {
    fprintf(out, "Case #%d: ", qw);
    char *s = new char[1000];
    int k;

    if (qw == 1)
      fgets(s, 1000, in);
    fgets(s, 1000, in);
    k = 0;
    int n = 0;
    while (s[n])
      n++;
    n--;
    int pow = 1;
    while (s[n - 1] >= '0' && s[n - 1] <= '9' && n > 0) {
      n--;
      k += (s[n] - '0') * pow;
      pow *= 10;
    }
    n--;
    bool fl = true;
    int kol = 0;
    int i = 0;
    while (i < n && fl) {
      if (s[i] == '-') {
        if (i + k > n)
          fl = false;
        else {
          for (int j = i; j < i + k; j++)
            s[j] = (s[j] == '-') ? '+' : '-';
          kol++;
          i++;
        }
      } else
        i++;
    }
    if (!fl)
      fprintf(out, "IMPOSSIBLE\n");
    else
      fprintf(out, "%d\n", kol);
  }
  return 0;
}

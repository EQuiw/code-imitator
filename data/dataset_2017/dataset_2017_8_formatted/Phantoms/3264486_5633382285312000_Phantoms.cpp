#include <stdio.h>
using namespace std;

bool prov(long long n) {
  bool fl = true;
  while (n > 0 && fl) {
    if (n % 10 < (n / 10) % 10)
      fl = false;
    n = n / 10;
  }
  return fl;
}

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char **argv) {
  FILE *in = fopen("B-small.in", "r");
  FILE *out = fopen("B-small.out", "w");
  int t;
  fscanf(in, "%d", &t);
  for (int u = 0; u < t; u++) {
    long long n;
    fscanf(in, "%lld", &n);
    long long pow = 10, sl = 9;
    while (!prov(n)) {
      n = (n / pow - 1) * pow + sl;
      pow *= 10;
      sl = sl * 10 + 9;
    }
    fprintf(out, "Case #%d: %lld\n", u + 1, n);
  }
  return 0;
}

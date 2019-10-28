#include <fstream>
#include <iostream>
using namespace std;

int main() {
  ifstream infile;
  ofstream outfile;
  infile.open("broom.in");
  outfile.open("broom.txt");
  int i, j, t, k, n, i2;
  infile >> t;
  for (i = 0; i < t; i++) {
    infile >> n >> k;
    bool *g = new bool[n + 2];
    for (j = 0; j < n + 2; j++)
      g[j] = 0;
    int *le = new int[n + 2];
    for (j = 1; j < n + 1; j++)
      le[j] = j - 1;
    int *re = new int[n + 2];
    for (j = 1; j < n + 1; j++)
      re[j] = n - j;
    g[0] = 1;
    g[n + 1] = 1;
    le[0] = 0;
    le[n + 1] = 0;
    re[0] = 0;
    re[n + 1] = 0;
    for (i2 = 0; i2 < k; i2++) {
      int leftmost = 0, biggest = 0, biggest2 = 0;
      for (j = 1; j < n + 1; j++) {
        if (!g[j]) {
          if (min(le[j], re[j]) > biggest) {
            leftmost = j;
            biggest = min(le[j], re[j]);
            biggest2 = max(le[j], re[j]);
          }
          if (min(le[j], re[j]) == biggest) {
            if (max(le[j], re[j]) > biggest2) {
              leftmost = j;
              biggest = min(le[j], re[j]);
              biggest2 = max(le[j], re[j]);
            }
          }
        }
      }
      g[leftmost] = 1;
      int counter = 0;
      for (j = 1; j < n + 1; j++) {
        le[j] = counter;
        counter++;
        if (g[j] == 1)
          counter = 0;
      }
      counter = 0;
      for (j = n; j > 0; j--) {
        re[j] = counter;
        counter++;
        if (g[j] == 1)
          counter = 0;
      }
      if (i2 == k - 1)
        outfile << "Case #" << i + 1 << ": " << biggest2 << " " << biggest
                << endl;
    }
  }
  return 0;
}

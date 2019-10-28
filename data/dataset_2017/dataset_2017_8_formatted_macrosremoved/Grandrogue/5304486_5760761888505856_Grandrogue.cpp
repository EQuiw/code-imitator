#include <fstream>

using namespace std;

ifstream fin("A-small-attempt0.in");
ofstream fout("out.txt");

int main() {
  int tests;
  fin >> tests;
  for (int test = 0; test < tests; ++test) {
    char a[25][25];
    int n, m;
    fin >> n >> m;
    int lastj = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        fin >> a[i][j];
        if (a[i][j] != '?' && j > lastj) {
          lastj = j;
        }
      }
    }

    for (int j = 0; j < m; j++) {
      int lasti = -1;
      for (int i = 0; i < n; i++) {
        if (a[i][j] != '?') {
          char c = a[i][j];
          a[i][j] = '?';
          for (int k = i; a[k][j] == '?' && k > lasti; --k) {
            for (int l = j; a[k][l] == '?' && l >= 0; --l) {
              a[k][l] = c;
            }
          }
          lasti = i;
        }
      }
      if (lasti != -1 && lasti != n - 1) {
        char c = a[lasti][j];
        for (int k = n - 1; a[k][j] == '?' && k > lasti; --k) {
          for (int l = j; a[k][l] == '?' && l >= 0; --l) {
            a[k][l] = c;
          }
        }
      }
    }
    for (int i = 0; i < n; ++i) {
      for (int j = lastj + 1; j < m; ++j) {
        a[i][j] = a[i][lastj];
      }
    }
    fout << "Case #" << test + 1 << ":" << endl;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        fout << a[i][j];
      }
      fout << endl;
    }
  }
  return 0;
}

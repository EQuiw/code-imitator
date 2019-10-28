#include <fstream>
#include <iostream>
#include <set>
#include <utility>
#include <vector>
using namespace std;

ofstream outfile;

void calculate(char **g, int r, int c, set<char> ls, char in[1000],
               int bounds[1000][4]) {
  int i, j, k, l, temp, temp2;
  set<char>::iterator it;
  set<char>::iterator it2;
  for (i = 0; i < r; i++) {
    for (j = 0; j < c; j++) {
      if (g[i][j] == '?') {
        for (it = ls.begin(); it != ls.end(); it++) {
          for (k = 0; k < 1000; k++)
            if (in[k] == *it)
              break;
          temp = k;
          bool breaker = 0;
          for (it2 = ls.begin(); it2 != ls.end(); it2++) {
            if (*it == *it2)
              continue;
            for (k = 0; k < 1000; k++)
              if (in[k] == *it2)
                break;
            temp2 = k;
            for (k = bounds[temp2][0]; k <= bounds[temp2][2]; k++) {
              for (l = bounds[temp2][1]; l <= bounds[temp2][3]; l++) {
                if (k == i && l == j) {
                  breaker = 1;
                  break;
                }
              }
            }
          }
          for (k = min(bounds[temp][0], i); k <= max(bounds[temp][2], i); k++) {
            for (l = min(bounds[temp][1], j); l <= max(bounds[temp][3], j);
                 l++) {
              if (g[k][l] != '?' && g[k][l] != *it) {
                breaker = 1;
                break;
              }
            }
          }
          if (!breaker) {
            g[i][j] = *it;
            bounds[temp][0] = min(bounds[temp][0], i);
            bounds[temp][1] = min(bounds[temp][1], j);
            bounds[temp][2] = max(bounds[temp][2], i);
            bounds[temp][3] = max(bounds[temp][3], j);
          }
        }
      }
    }
  }
  for (i = 0; i < r; i++) {
    for (j = 0; j < c; j++)
      outfile << g[i][j];
    outfile << endl;
  }
}

int main() {
  ifstream infile;
  infile.open("cake.in");
  outfile.open("cake.txt");
  int i, j, k, t, r, c;
  infile >> t;
  for (i = 0; i < t; i++) {
    int counter = 0;
    infile >> r >> c;
    set<char> ls;
    char in[1000];
    int bounds[1000][4];
    char **g = new char *[r];
    for (j = 0; j < r; j++)
      g[j] = new char[c];
    for (j = 0; j < r; j++) {
      for (k = 0; k < c; k++) {
        infile >> g[j][k];
        if (g[j][k] != '?') {
          ls.insert(g[j][k]);
          in[counter] = g[j][k];
          bounds[counter][0] = j;
          bounds[counter][1] = k;
          bounds[counter][2] = j;
          bounds[counter][3] = k;
          counter++;
        }
      }
    }
    outfile << "Case #" << i + 1 << ": " << endl;
    calculate(g, r, c, ls, in, bounds);
  }
  return 0;
}

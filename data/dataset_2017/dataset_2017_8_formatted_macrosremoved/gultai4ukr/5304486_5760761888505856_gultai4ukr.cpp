#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
  ifstream fin("/home/roman/CodeliteProjects/Competitive/GCJ17_R1A/in.txt");
  ofstream fout("/home/roman/CodeliteProjects/Competitive/GCJ17_R1A/out.txt");

  int t;
  fin >> t;
  for (int testcase = 0; testcase < t; ++testcase) {
    int r, c;
    fin >> r >> c;
    vector<string> v(r);
    for (int i = 0; i < r; ++i) {
      fin >> v[i];
      //			cout << v[i] << endl;
    }

    for (int i = 0; i < r; ++i) {
      for (int j = 0; j < c; ++j) {
        if (v[i][j] == '?') {
          int dist = c, index = j;
          for (int k = 0; k < c; ++k) {
            if (v[i][k] != '?') {
              if (abs(j - k) < dist) {
                dist = abs(j - k);
                index = k;
              }
            }
          }
          for (int k = min(j, index); k < max(j, index) + 1; ++k) {
            v[i][k] = v[i][index];
          }
        }
      }
    }

    for (int i = 0; i < r; ++i) {
      if (v[i][0] == '?') {
        int dist = r, index = -1;
        for (int k = 0; k < r; ++k) {
          if (v[k][0] != '?') {
            if (abs(i - k) < dist) {
              dist = abs(i - k);
              index = k;
            }
          }
        }
        assert(index >= 0);
        for (int j = 0; j < c; ++j) {
          v[i][j] = v[index][j];
        }
      }
    }

    fout << "Case #" << testcase + 1 << ":" << endl;
    for (int i = 0; i < r; ++i) {
      for (int j = 0; j < c; ++j) {
        fout << v[i][j];
      }
      fout << endl;
    }
  }

  fin.close();
  fout.close();
  return 0;
}

#include <bits/stdc++.h>

#define PAUSE system("pause")
#define LL long long int
#define LD long double
#define PB push_back
#define PF push_front
#define MP make_pair
#define FORi(i, a, b) for (int i = a; i < b; ++i)
#define FORd(i, a, b) for (int i = a; i > b; --i)

using namespace std;

int main(int argc, char **argv) {
  ifstream fin("/home/roman/CodeliteProjects/Competitive/GCJ17_R1A/in.txt");
  ofstream fout("/home/roman/CodeliteProjects/Competitive/GCJ17_R1A/out.txt");

  int t;
  fin >> t;
  FORi(testcase, 0, t) {
    int r, c;
    fin >> r >> c;
    vector<string> v(r);
    FORi(i, 0, r) {
      fin >> v[i];
      //			cout << v[i] << endl;
    }

    FORi(i, 0, r) {
      FORi(j, 0, c) {
        if (v[i][j] == '?') {
          int dist = c, index = j;
          FORi(k, 0, c) {
            if (v[i][k] != '?') {
              if (abs(j - k) < dist) {
                dist = abs(j - k);
                index = k;
              }
            }
          }
          FORi(k, min(j, index), max(j, index) + 1) { v[i][k] = v[i][index]; }
        }
      }
    }

    FORi(i, 0, r) {
      if (v[i][0] == '?') {
        int dist = r, index = -1;
        FORi(k, 0, r) {
          if (v[k][0] != '?') {
            if (abs(i - k) < dist) {
              dist = abs(i - k);
              index = k;
            }
          }
        }
        assert(index >= 0);
        FORi(j, 0, c) { v[i][j] = v[index][j]; }
      }
    }

    fout << "Case #" << testcase + 1 << ":" << endl;
    FORi(i, 0, r) {
      FORi(j, 0, c) { fout << v[i][j]; }
      fout << endl;
    }
  }

  fin.close();
  fout.close();
  return 0;
}

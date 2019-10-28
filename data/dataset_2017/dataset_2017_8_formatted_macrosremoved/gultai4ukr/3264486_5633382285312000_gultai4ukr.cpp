#include <bits/stdc++.h>
using namespace std;

bool is_tidy(int n) {
  int d = 9;
  while (n) {
    if (n % 10 > d) {
      return 0;
    }
    d = n % 10;
    n /= 10;
  }
  return 1;
}

int main(int argc, char **argv) {
  ifstream fin("/home/roman/CodeliteProjects/Competitive/GCJ17_Quals/in.txt");
  ofstream fout("/home/roman/CodeliteProjects/Competitive/GCJ17_Quals/out.txt");

  int t;
  fin >> t;
  for (int testcase = 0; testcase < t; ++testcase) {
    long long int n;
    fin >> n;
    long long int tidy = 1;
    for (int i = n; i > 1; --i) {
      if (is_tidy(i)) {
        tidy = i;
        break;
      }
    }
    fout << "Case #" << testcase + 1 << ": " << tidy << endl;
  }

  fin.close();
  fout.close();
  return 0;
}

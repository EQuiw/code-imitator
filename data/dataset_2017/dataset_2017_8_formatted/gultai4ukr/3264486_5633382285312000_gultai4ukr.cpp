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
  FORi(testcase, 0, t) {
    LL n;
    fin >> n;
    LL tidy = 1;
    FORd(i, n, 1) {
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

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
  ifstream fin("/home/roman/CodeliteProjects/Competitive/GCJ17_R1B/in.txt");
  ofstream fout("/home/roman/CodeliteProjects/Competitive/GCJ17_R1B/out.txt");

  int t;
  fin >> t;
  FORi(testcase, 0, t) {
    LL d, n, k, s;
    fin >> d >> n;
    double max_time = 0;
    FORi(i, 0, n) {
      fin >> k >> s;
      //			cout << k << s << endl;
      max_time = max(max_time, 1.0 * (d - k) / s);
    }

    fout << "Case #" << testcase + 1 << ": " << fixed << setprecision(7)
         << d / max_time << endl;
  }

  fin.close();
  fout.close();
  return 0;
}

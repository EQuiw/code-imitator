#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
  ifstream fin("/home/roman/CodeliteProjects/Competitive/GCJ17_R1B/in.txt");
  ofstream fout("/home/roman/CodeliteProjects/Competitive/GCJ17_R1B/out.txt");

  int t;
  fin >> t;
  for (int testcase = 0; testcase < t; ++testcase) {
    long long int d, n, k, s;
    fin >> d >> n;
    double max_time = 0;
    for (int i = 0; i < n; ++i) {
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

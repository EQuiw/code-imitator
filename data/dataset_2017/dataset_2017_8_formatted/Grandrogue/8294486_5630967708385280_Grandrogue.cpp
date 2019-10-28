#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

ifstream fin("A-small-attempt0.in");
ofstream fout("out.txt");

struct h {
  double k;
  double s;
  double t;
};

h horse[1000];

bool comp(h a, h b) { return a.k > b.k; }
int main() {
  int tests;
  fin >> tests;
  for (int test = 0; test < tests; ++test) {
    int n;
    double d;
    fin >> d >> n;
    for (int i = 0; i < n; ++i) {
      h a;
      fin >> a.k >> a.s;
      horse[i] = a;
    }
    sort(horse, horse + n, comp);
    double time = -1.0;
    for (int i = 0; i < n; ++i) {
      if (time == -1.0) {
        time = (d - horse[i].k) / horse[i].s;
        horse[i].t = time;
      } else {
        double t = (d - horse[i].k) / horse[i].s;
        if (t < horse[i - 1].t) {
          horse[i].t = horse[i - 1].t;
        } else {
          horse[i].t = t;
        }
      }
    }

    fout << fixed << setprecision(8) << "Case #" << test + 1 << ": "
         << d / horse[n - 1].t << endl;
  }
  return 0;
}
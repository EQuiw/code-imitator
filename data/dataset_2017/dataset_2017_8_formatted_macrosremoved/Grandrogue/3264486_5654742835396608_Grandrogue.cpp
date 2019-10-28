#include <fstream>
#include <queue>

using namespace std;

ifstream fin("C-small-1-attempt0.in");
ofstream fout("out.txt");

int main() {
  int tests;
  fin >> tests;
  for (int test = 0; test < tests; ++test) {
    long long n, k, l, r;
    fin >> n >> k;
    pair<long long, long long> a(n, 1), b(0, 0);

    while (true) {
      pair<long long, long long> an(0, 0), bn(0, 0);
      if (k <= a.second) {
        if (a.first % 2) {
          l = r = a.first / 2;
        } else {
          l = a.first / 2;
          r = l - 1;
        }

        break;
      }
      if (a.first % 2) {
        an.first = a.first / 2;
        an.second = a.second * 2;
      } else {
        an.first = a.first / 2;
        an.second = a.second;
        bn.first = an.first - 1;
        bn.second = a.second;
      }
      k -= a.second;

      if (b.second) {
        if (k <= b.second) {
          if (b.first % 2) {
            l = r = b.first / 2;
          } else {
            l = b.first / 2;
            r = l - 1;
          }

          break;
        }

        if (b.first % 2) {
          bn.second += b.second * 2;
        } else {
          an.second += b.second;
          bn.first = an.first - 1;
          bn.second += b.second;
        }
      }
      k -= b.second;

      a = an;
      b = bn;
    }

    fout << "Case #" << test + 1 << ": " << l << " " << r << endl;
  }

  return 0;
}

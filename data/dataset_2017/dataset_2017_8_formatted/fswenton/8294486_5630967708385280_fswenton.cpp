#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

template <class P0, class P1>
ostream &operator<<(ostream &os, const pair<P0, P1> &p) {
  return os << "(" << p.first << "," << p.second << ")";
}
template <class T> void _dump(const T &t) {
  cerr << "[";
  for (auto it = t.begin(); it != t.end(); ++it)
    cerr << " " << *it;
  cerr << " ]"
       << "\n";
}

#define dump(x)                                                                \
  {                                                                            \
    cerr << #x << ": ";                                                        \
    _dump(x);                                                                  \
  }
#define trace(x)                                                               \
  { cerr << #x << ": " << x << "\n"; }

#if 0
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;
#define Integer cpp_int
#define Rational cpp_rational
#define Float cpp_dec_float_50
#endif

int main(void) {
  int T;
  cin >> T;

  for (int iCase = 1; iCase <= T; ++iCase) {
    cout << "Case #" << iCase << ": ";

    int i, j, d, n;
    cin >> d >> n;
    map<double, double> horses; // pos |--> speed
    for (i = 0; i < n; ++i) {
      double pos, speed;
      cin >> pos >> speed;
      horses[pos] = speed;
    }

    dump(horses);

    double slowest = 0.0;
    for (auto it = horses.begin(); it != horses.end(); ++it) {
      double time = (d - it->first) / it->second;
      if (time > slowest)
        slowest = time;
    }

    cout << setprecision(8) << d / slowest;
    cout << "\n";
  }

  return 0;
}

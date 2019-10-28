#include <iostream>
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
template <class T> void dump(const T &t) {
  cerr << "[";
  for (auto it = t.begin(); it != t.end(); ++it)
    cerr << " " << *it;
  cerr << " ]"
       << "\n";
}

#if 0
#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;
#define Integer cpp_int
#endif

int main(void) {
  int T;
  cin >> T;

  for (int iCase = 1; iCase <= T; ++iCase) {
    cout << "Case #" << iCase << ":";

    string s;
    cin >> s;
    // cerr << s << "\n";
    int i0, i, n = s.length();

    if (n > 1) {
      for (i0 = 1; i0 < n; ++i0)
        if (s[i0] < s[i0 - 1])
          break;

      if (i0 < n) {
        // cerr << i0 << "\n";

        // i0 is position of first actual drop in digit
        for (i = i0; i < n; ++i)
          s[i] = '9';
        --s[--i0];

        // cerr << " --> " << s;

        while (i0 > 0 && s[i0] < s[i0 - 1]) {
          --s[i0 - 1];
          s[i0] = '9';
          --i0;
        }

        // cerr << " --> " << s;

        if (s[0] == '0')
          s = s.substr(1);

        // cerr << " --> " << s << "\n";
      }
    }

    cout << " " << s << "\n";
  }

  return 0;
}

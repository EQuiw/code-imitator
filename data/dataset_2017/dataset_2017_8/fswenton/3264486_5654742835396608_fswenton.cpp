#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <sstream>
using namespace std;

template<class P0, class P1> ostream &operator<<(ostream &os, const pair<P0, P1> &p) { return os << "(" << p.first << "," << p.second << ")"; }
template<class T> void dump(const T &t) { cerr << "["; for (auto it = t.begin(); it != t.end(); ++it) cerr << " " << *it; cerr << " ]" << "\n"; } 

#if 0
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
using namespace boost::multiprecision;
#define Integer cpp_int
#define Rational cpp_rational
#define Float cpp_dec_float_50
#endif

int main(void) {
  int T; cin >> T;
  
  for (int iCase = 1; iCase <= T; ++iCase) {
    cout << "Case #" << iCase << ":";
    int i, n, k; cin >> n >> k;

    multiset<int> gaps;
    gaps.insert(-n);

    int left, right;
    for (i = 0; i < k; ++i) {
      int gap = -*gaps.begin(); gaps.erase(gaps.begin());
      
      --gap;
      right = gap/2;
      left = gap - right;

      if (left) gaps.insert(-left);
      if (right) gaps.insert(-right);
    }

    cout << " " << left << " " << right;

    cout << "\n";
  }

  return 0;
}

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

void flip(string &s, int i) { s[i] = ('+' + '-' - s[i]); }

int main(void) {
  int T; cin >> T;
  
  for (int iCase = 1; iCase <= T; ++iCase) {
    cout << "Case #" << iCase << ":";
    string state0; cin >> state0;
    int k; cin >> k;
    int i, j, n = state0.length();

    //cerr << k << "\n";

    map<string, int> flips;
    multimap<int, string> toDo;
    toDo.insert(make_pair(0, state0));

    while (!toDo.empty()) {
      //dump(flips);
      //cerr << "=====\n";

      int flips0 = toDo.begin()->first;
      string s0 = toDo.begin()->second;
      toDo.erase(toDo.begin());
      if (flips.find(s0)!=flips.end()) continue;
      flips[s0] = flips0;
      if (k > n) continue;
      for (i = 0; i < k; ++i) flip(s0, i);

      i = 0;
      while (true) {
	toDo.insert(make_pair(flips0+1, s0));
	if (i+k==n) break;
	flip(s0, i);
	flip(s0, i+k);
	++i;
      }
    }

    map<string, int>::iterator iFlips = flips.find(string(n, '+'));
    if (iFlips==flips.end())
      cout << " IMPOSSIBLE";
    else
      cout << " " << iFlips->second;

    cout << "\n";
  }

  return 0;
}

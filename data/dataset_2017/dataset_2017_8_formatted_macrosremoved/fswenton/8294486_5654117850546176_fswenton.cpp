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
string colors = "ROYGBV";

int main(void) {
  int T;
  cin >> T;

  for (int iCase = 1; iCase <= T; ++iCase) {
    cout << "Case #" << iCase << ":";

    int i, j, n;
    cin >> n;

    vector<int> count(6, 0);
    for (i = 0; i < 6; ++i)
      cin >> count[i];

    {
      cerr << "count"
           << ": ";
      _dump(count);
    };

    int maxChunk = 0, maxChunkStart = 0;
    for (i = 0; i < 6; ++i) {
      int chunk = 0;
      for (j = 0; j <= 1; ++j)
        chunk += count[(i + j) % 6];
      if (chunk > maxChunk) {
        maxChunkStart = i;
        maxChunk = chunk;
      }
    }

    if (maxChunk * 2 > n) {
      cout << " IMPOSSIBLE\n";
      continue;
    }

    maxChunkStart = (maxChunkStart + 1) & (~1);
    {
      cerr << "maxChunk"
           << ": " << maxChunk << "\n";
    };
    {
      cerr << "maxChunkStart"
           << ": " << maxChunkStart << "\n";
    };

    //=====SMALL
    int plus2 = (maxChunkStart + 2) % 6, plus4 = (maxChunkStart + 4) % 6;
    string sPlus2(maxChunk, ' '), sPlus4(maxChunk, ' ');
    for (i = 0; i < count[plus2]; ++i)
      sPlus2[i] = colors[plus2];
    for (i = 0; i < count[plus4]; ++i)
      sPlus4[maxChunk - 1 - i] = colors[plus4];

    {
      cerr << "sPlus2"
           << ": " << sPlus2 << "\n";
    };
    {
      cerr << "sPlus4"
           << ": " << sPlus4 << "\n";
    };

    string result = "";
    for (i = 0; i < maxChunk; ++i) {
      result += colors[maxChunkStart];
      if (sPlus2[i] != ' ')
        result += sPlus2[i];
      if (sPlus4[i] != ' ')
        result += sPlus4[i];
    }

    cout << " " << result << "\n";
    if (result.length() < n)
      cerr << "****" << iCase << "****\n";
  }

  return 0;
}

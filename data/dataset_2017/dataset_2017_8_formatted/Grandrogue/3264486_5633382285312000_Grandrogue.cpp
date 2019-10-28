#include <fstream>
#include <string>

using namespace std;

ifstream fin("B-small-attempt0.in");
ofstream fout("out.txt");

int main() {
  int tests;
  fin >> tests;
  for (int test = 0; test < tests; ++test) {
    string s;
    fin >> s;
    for (int i = 0; i < s.length() - 1; ++i) {
      if (s[i] > s[i + 1]) {
        --s[i];
        while (i > 0 && s[i - 1] > s[i]) {
          --i;
          --s[i];
        }

        if (s[0] == '0') {
          s.pop_back();
        } else {
          ++i;
        }

        for (i = i; i < s.length(); ++i) {
          s[i] = '9';
        }

        break;
      }
    }

    fout << "Case #" << test + 1 << ": " << s << endl;
  }

  return 0;
}
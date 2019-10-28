#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef vector<bool> vb;

int main() {

  int t;
  cin >> t;
  int cas = 1;
  while (t--) {
    cout << "Case #" << cas << ": ";
    cas++;
    vb b = vb();
    string s;
    cin >> s;
    int k;
    cin >> k;

    for (int i = 0; i < s.size(); i++) {
      if (s[i] == '-')
        b.push_back(false);
      else if (s[i] == '+')
        b.push_back(true);
    }

    int count = 0;
    for (int i = 0; i < b.size() - k + 1; i++) {
      if (!b[i]) {
        for (int j = i; j < i + k; j++) {
          b[j] = !b[j];
        }
        count++;
      }
    }

    // check the last (k - 1) to see if they are all flipped
    bool complete = true;
    for (int i = b.size() - (k - 1); i < b.size(); i++) {
      complete = complete & b[i];
    }

    if (complete)
      cout << count << endl;
    else
      cout << "IMPOSSIBLE" << endl;
  }

  return 0;
}
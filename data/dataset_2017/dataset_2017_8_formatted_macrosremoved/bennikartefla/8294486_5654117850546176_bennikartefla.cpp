#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef long long ll;
const int INF = ~(1 << 31);
const double pi = acos(-1);

int main() {
  cin.sync_with_stdio(false);
  ofstream fout("ansb2.txt");
  int t;
  cin >> t;
  string nice = "ROYGBVXXX";
  for (int u = (0); u < (t); u++) {
    int arr[8];
    memset(arr, 0, sizeof(arr));
    int n;
    cin >> n;
    for (int i = (0); i < (6); i++)
      cin >> arr[i];
    string s = "";
    int last = 7;
    int og = n;
    bool can = true;
    while (n != 0) {
      int bst = 0;
      int index = 0;
      for (int i = (0); i < (6); i++)
        if (arr[i] >= bst && nice[i] != nice[last] && arr[i] != 0) {
          if (arr[i] == bst && arr[i] != 0) {
            if (n != og) {
              if (s[0] == nice[i]) {
                bst = arr[i];
                index = i;
              }
            }
          } else if (arr[i] > bst) {
            bst = arr[i];
            index = i;
          }
        }
      arr[index]--;
      if (bst == -1) {
        can = false;
        break;
      }
      s += nice[index];
      last = index;
      n--;
    }
    if (s.size() != og)
      can = false;
    for (int i = (0); i < (s.size() - 1); i++)
      if (s[i] == s[i + 1])
        can = false;
    for (int i = (1); i < (s.size()); i++)
      if (s[i] == s[i - 1])
        can = false;
    fout << "Case #" << u + 1 << ": ";
    if (s[0] == s[s.size() - 1] || !can)
      fout << "IMPOSSIBLE" << endl;
    else
      fout << s << endl;
  }
  return 0;
}

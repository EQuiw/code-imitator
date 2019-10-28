#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int A[20];
int main() {
  ios::sync_with_stdio(0);
  freopen("readable.txt", "w", stdout);
  int t;
  cin >> t;
  for (int ca = 1; ca <= t; ca++) {
    cout << "Case #" << ca << ": ";
    string s;
    cin >> s;
    int n = s.size();
    for (int i = 0; i < n; i++)
      A[i] = s[i] - '0';
    int last = 0;
    for (int i = 1; i < n; i++) {
      if (A[i] > A[i - 1])
        last = i;
      else
        break;
    }
    bool tidy = true;
    for (int i = 1; i < n; i++)
      if (A[i] < A[i - 1])
        tidy = false;
    if (!tidy) {
      A[last]--;
      for (int i = last + 1; i < n; i++)
        A[i] = 9;
    }
    bool started = false;
    for (int i = 0; i < n; i++) {
      if (A[i] != 0) {
        started = true;
        cout << A[i];
      } else if (started) {
        cout << A[i];
      }
    }
    cout << endl;
  }
  return 0;
}

// g++ -std=c++11 -O2 -Wfatal-errors -Im -Wall -Wextra -o "output.txt"
// "code.cpp"
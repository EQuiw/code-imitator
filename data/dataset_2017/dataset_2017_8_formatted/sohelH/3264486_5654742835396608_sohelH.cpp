#include <bits/stdc++.h>

using namespace std;

// input reading
template <class T> vector<T> takeInput(int n) {
  vector<T> v;
  T a;
  for (int i = 0; i < n; i++) {
    cin >> a;
    v.push_back(a);
  }
  return v;
}

int main() {
  int test;
  cin >> test;
  for (int cases = 1; cases <= test; cases++) {
    long long n, k;
    cin >> n >> k;
    map<long long int, long long> m;
    m[n] = 1;

    long long res = -1;
    while (true) {
      long long key = m.rbegin()->first;
      long long value = m.rbegin()->second;
      if (value >= k) {
        res = key;
        break;
      }

      k -= value;

      long long half = key / 2;
      if (key % 2) {
        m[half] += value * 2;
      } else {
        m[half] += value;
        m[half - 1] += value;
      }
      map<long long, long long>::iterator it = m.end();
      --it;
      m.erase(it);
    }

    cout << "Case #" << cases << ": ";
    long long left = res / 2;
    long long right = res / 2;
    if (res % 2 == 0)
      right--;
    cout << left << " " << right << endl;
  }
  return 0;
}

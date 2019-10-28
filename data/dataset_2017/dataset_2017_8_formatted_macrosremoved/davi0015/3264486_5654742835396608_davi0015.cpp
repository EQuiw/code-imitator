#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
typedef long long int ll;

int main() {
  int T;
  cin >> T;

  for (int i = 0; i < T; i++) {
    ll N, K;
    cin >> N >> K;

    map<ll, ll> stallCount;
    vector<ll> stall;

    stallCount[N] = 1;
    stall.push_back(N);

    ll currentCount = 0;
    ll space = 0;
    int index = 0;
    while (currentCount < K) {
      space = stall[index];
      currentCount += stallCount[space];

      if (stallCount[space / 2] == 0) {
        stall.push_back(space / 2);
      }
      stallCount[space / 2] += stallCount[space];

      if (stallCount[(space - 1) / 2] == 0) {
        stall.push_back((space - 1) / 2);
      }
      stallCount[(space - 1) / 2] += stallCount[space];

      index++;
    }

    cout << "Case #" << i + 1 << ": " << space / 2 << " " << (space - 1) / 2
         << endl;
  }

  return 0;
}

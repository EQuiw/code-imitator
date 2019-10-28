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
  cout << fixed << setprecision(7);

  for (int i = 0; i < T; i++) {
    int D, N;
    cin >> D >> N;

    int K, S;
    double speed = 1e20;
    for (int j = 0; j < N; j++) {
      cin >> K >> S;
      speed = min(speed, (double)D / ((double)(D - K) / (double)S));
    }

    cout << "Case #" << i + 1 << ": " << speed << endl;
  }

  return 0;
}

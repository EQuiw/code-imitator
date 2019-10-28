#include <algorithm>
#include <array>
#include <chrono>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <deque>
#include <forward_list>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <valarray>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cout << setprecision(12);

  int T;
  cin >> T;
  for (int t = 0; t < T; t++) {
    double D;
    int N;
    cin >> D >> N;

    double maxTime = 0.0f;
    for (int i = 0; i < N; i++) {
      double K, S;
      cin >> K >> S;
      double time = (D - K) / S;
      if (time > maxTime) {
        maxTime = time;
      }
    }

    double mySpeed = D / maxTime;
    cout << "Case #" << t + 1 << ": " << mySpeed << endl;
  }

  return 0;
}

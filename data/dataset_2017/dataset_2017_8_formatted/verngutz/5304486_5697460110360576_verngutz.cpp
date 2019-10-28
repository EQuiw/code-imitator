#include <bits/stdc++.h>
using namespace std;

int T;
int N, P;
int a[50];
pair<int, int> b[50][50];
vector<int> counters;

bool can_move() {
  for (int i = 0; i < counters.size(); i++) {
    if (counters[i] == P) {
      return false;
    }
  }
  return true;
}
int main() {
  cin >> T;
  for (int t = 1; t <= T; t++) {
    cin >> N >> P;
    for (int i = 0; i < N; i++) {
      cin >> a[i];
    }
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < P; j++) {
        int bb;
        cin >> bb;
        int max_servings = int(bb * 100.0 / 90 / a[i]) + 10;
        int min_servings = max(1, int(bb * 100.0 / 110 / a[i]) - 10);
        int r_max_servings = -1;
        int r_min_servings = max_servings;
        for (int s = min_servings; s <= max_servings; s++) {
          if (a[i] * s * 90 <= bb * 100 && bb * 100 <= a[i] * s * 110) {
            r_max_servings = max(r_max_servings, s);
            r_min_servings = min(r_min_servings, s);
          }
        }
        b[i][j] = {r_min_servings, r_max_servings};
      }
    }
    for (int i = 0; i < N; i++) {
      sort(b[i], b[i] + P);
    }
    /*
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < P; j++) {
            if(b[i][j].second > 0) {
                cout << b[i][j].first << "-" << b[i][j].second << " ";
            }
        }
        cout << endl;
    }
    */
    counters.clear();
    for (int i = 0; i < N; i++) {
      counters.push_back(0);
    }
    int ans = 0;
    while (can_move()) {
      bool valid = true;
      for (int i = 0; i < N; i++) {
        if (b[i][counters[i]].second == -1) {
          counters[i]++;
          valid = false;
        }
      }
      if (valid) {
        int greatest_lower_bound = b[0][counters[0]].first;
        int least_upper_bound = b[0][counters[0]].second;
        for (int i = 1; i < N; i++) {
          greatest_lower_bound =
              max(greatest_lower_bound, b[i][counters[i]].first);
          least_upper_bound = min(least_upper_bound, b[i][counters[i]].second);
        }
        // cout << greatest_lower_bound << " " << least_upper_bound << endl;
        bool allgood = true;
        for (int i = 0; i < N; i++) {
          if (!(greatest_lower_bound <= b[i][counters[i]].second &&
                b[i][counters[i]].first <= least_upper_bound)) {
            allgood = false;
          }
        }
        if (allgood) {
          ans++;
          for (int i = 0; i < counters.size(); i++) {
            counters[i]++;
          }
        } else {
          int mini = b[0][counters[0]].first;
          int min_index = 0;
          for (int i = 1; i < N; i++) {
            if (b[i][counters[i]].first < mini) {
              mini = b[i][counters[i]].first;
              min_index = i;
            }
          }
          counters[min_index]++;
        }
      }
    }
    cout << "Case #" << t << ": " << ans << endl;
  }
  return 0;
}

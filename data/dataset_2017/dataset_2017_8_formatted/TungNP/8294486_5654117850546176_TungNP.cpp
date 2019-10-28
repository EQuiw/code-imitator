//
//  main.cpp
//  ProblemB
//
//  Created by Tung Nguyen on 4/22/17.
//
//

#include <cmath>
#include <fstream>

using namespace std;

char chars[] = {'R', 'O', 'Y', 'G', 'B', 'V'};
int nums[6];
int N;

bool possible;
char result[1001];

bool can_match(int i, int j) {
  if (abs(i - j) <= 1 || abs(i - j) == 5) {
    return false;
  }
  return true;
}

int get_max(int idx, int i0) {
  int r = -1;
  int r_m = 0;
  for (int i = 0; i < 6; i++) {
    if ((idx == -1 || can_match(idx, i)) && nums[i] > 0) {
      int i_m = 0;
      for (int j = 0; j < 6; j++) {
        if (!can_match(i, j)) {
          i_m += nums[j];
        }
      }

      if (r_m < i_m) {
        r = i;
        r_m = i_m;
      } else if (r_m == i_m && i0 != -1) {
        if (!can_match(i0, i)) {
          r = i;
        }
      }
    }
  }
  return r;
}

void solve() {
  int idx = -1;
  int first = -1;
  int last = -1;
  possible = true;
  for (int i = 0; i < N; i++) {
    idx = get_max(idx, first);
    if (idx == -1) {
      possible = false;
      break;
    }
    if (i == 0) {
      first = idx;
    }
    if (i == N - 1) {
      last = idx;
    }
    result[i] = chars[idx];
    nums[idx]--;
  }
  result[N] = 0;
  if (possible) {
    if (!can_match(first, last)) {
      possible = false;
    }
  }
}

int main(int argc, const char *argv[]) {
  ifstream fin("B-small-attempt0.in.txt");
  ofstream fout("B-small-attempt0.out.txt");

  int T;
  fin >> T;
  for (int Case = 1; Case <= T; Case++) {
    fin >> N >> nums[0] >> nums[1] >> nums[2] >> nums[3] >> nums[4] >> nums[5];
    solve();
    fout << "Case #" << Case << ": ";
    if (possible) {
      fout << result;
    } else {
      fout << "IMPOSSIBLE";
    }
    fout << endl;
  }

  fin.close();
  fout.close();
  return 0;
}

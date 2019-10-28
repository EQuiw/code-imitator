#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

map<char, int> mmm;

struct my_sort {
  bool operator()(const pair<int, char> &left, const pair<int, char> &right) {
    if (left.first > right.first) {
      return true;
    } else if (left.first < right.first) {
      return false;
    } else {
      return mmm[left.second] < mmm[right.second];
    }
  }
};

int solve(int cc) {
  mmm.clear();
  int n, r, o, y, g, b, v;
  cin >> n >> r >> o >> y >> g >> b >> v;
  pair<int, char> arr[3];
  arr[0] = pair<int, char>(r, 'R');
  arr[1] = pair<int, char>(y, 'Y');
  arr[2] = pair<int, char>(b, 'B');
  sort(arr, arr + 3, greater<pair<int, char>>());

  //    for(int i=0;i<3;i++){
  //        cout<<arr[i].first<<arr[i].second<<endl;
  //    }
  for (int i = 0; i < 3; i++) {
    mmm[arr[i].second] = i;
  }

  cout << "Case #" << cc << ": ";
  string sol = "";
  bool im = false;
  char last = '-';
  for (int i = 0; i < n && !im; i++) {
    int mi = -1;
    sort(arr, arr + 3, my_sort());
    for (int j = 0; j < 3; j++) {
      if (arr[j].second != last) {
        mi = j;
        break;
      }
    }
    if (mi == -1 || arr[mi].first <= 0) {
      im = true;
      break;
    }
    sol += arr[mi].second;
    last = arr[mi].second;
    arr[mi].first--;
  }
  if (im || (sol[0] == sol[n - 1])) {
    cout << "IMPOSSIBLE" << endl;
  } else {
    cout << sol << endl;
  }
  return 1;
}

int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
  return 0;
}

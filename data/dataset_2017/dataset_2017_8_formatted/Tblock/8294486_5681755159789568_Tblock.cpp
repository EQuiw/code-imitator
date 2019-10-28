#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#define EPS 1e-9

using namespace std;

typedef vector<char> vc;
typedef vector<vc> vvc;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;

vi e;
vi s;
vvll d;
vvll apsp;
vvll reach; // reach[h] gives list of cities that horse h can reach

vd memo; // memo[h] gives answer if we start in city h and pick the horse

double solve(int h) {

  // cout << "solving " << h << endl;
  // for (int i = 0; i < memo.size(); i++) {
  //	cout << memo[i] << " ";
  //}
  // cout << endl;

  if (memo[h] != -1.0) {
    return memo[h];
  }

  if (h == apsp.size() - 1) {
    // base case
    return memo[h] = 0.0;
  }

  double min_time = 1e300;
  // ride the horse to all reachable cities
  for (int i = 0; i < reach[h].size(); i++) {
    // cout << h << " - " << i << endl;
    double ttr = (double)apsp[h][reach[h][i]] / s[h];
    double total_time = ttr + solve(reach[h][i]);
    // cout << "time from city " << h << ", switching at " << reach[h][i] << "
    // is " << total_time << endl;
    if (total_time < min_time) {
      min_time = total_time;
    }
  }

  // cout << "determined minimum time for " << h << " is " << min_time << endl;
  return memo[h] = min_time;
}

int main() {

  int t;
  cin >> t;
  int cas = 1;
  while (t--) {
    cout << "Case #" << cas << ":";
    cas++;

    int n, queries;
    cin >> n >> queries;
    e.clear();
    s.clear();
    d = vvll(n, vll(n, 0));
    apsp = vvll(n, vll(n, 0));

    for (int i = 0; i < n; i++) {
      int temp1;
      int temp2;
      cin >> temp1 >> temp2;
      e.push_back(temp1);
      s.push_back(temp2);
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        double temp;
        cin >> temp;
        if (temp < 0.0) {
          d[i][j] = 1e15;
          apsp[i][j] = 1e15;
        } else {
          d[i][j] = temp;
          apsp[i][j] = temp;
        }
      }
    }

    // floyd warshall
    for (int k = 0; k < n; k++) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          apsp[i][j] = min(apsp[i][j], apsp[i][k] + apsp[k][j]);
        }
      }
    }

    // if (cas == 17) {
    //	for (int i = 0; i < n; i++) {
    //		for (int j = 0; j < n; j++) {
    //			cout << d[i][j] << " ";
    //		}
    //		cout << endl;
    //	}
    //}

    for (int q = 0; q < queries; q++) {
      int u, v;
      cin >> u >> v;
      u--;
      v--;

      memo = vd(n, -1.0);
      reach.clear();

      // compute list of cities horse h can reach
      for (int h = 0; h < n; h++) {
        reach.push_back(vll());
        for (int c = 0; c < n; c++) {
          if (c != h && apsp[h][c] <= e[h]) {
            reach[h].push_back(c);
          }
        }
      }

      // temp
      // for (int h = 0; h < n; h++) {
      //	cout << h << " can reach: ";
      //	for (int c = 0; c < reach[h].size(); c++) {
      //		cout << reach[h][c] << " ";
      //	}
      //	cout << endl;
      //}

      cout << " " << solve(u);
    }

    cout << endl;
  }
  return 0;
}
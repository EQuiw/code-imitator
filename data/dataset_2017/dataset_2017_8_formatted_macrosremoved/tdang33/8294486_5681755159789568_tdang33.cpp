#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

using namespace std;

void solve(vector<vector<long long>> &v, vector<vector<long long>> &g,
           vector<vector<long long>> &d, long long n, long long q) {
  double result = 0.0;
  // pow(10,18)*1.0;
  // doub
  vector<long long> dist(n, 0);
  for (int i = 1; i < n; i++) {
    dist[i] = dist[i - 1] + g[i - 1][i];
  }
  vector<double> temp(n, 0.0);
  for (int i = 1; i < n; i++) {
    double cur = pow(10, 18) * 1.0;
    for (int j = 0; j < i; j++) {
      long long distance = dist[i] - dist[j];
      long long canGo = v[j][0];
      long long speed = v[j][1];
      // cout << distance <<"  "<<canGo<<" "<<speed<<endl;
      if (canGo >= distance) {
        cur = min(cur, temp[j] + distance / (1.0 * speed));
        // v[j][0] -= dist;
      }
      // cout <<"end j"<< endl;
    }
    // cout <<"end i"<<endl;
    temp[i] = cur;
    // cout << "temp: "<<temp<<endl;
    // double temp = ;
    // result += temp;
    // result = min(result, temp);
  }
  // for (auto i: temp) {
  //     cout << "current: "<<i <<endl;
  //     result += i;
  // }
  // return result;
  cout << setprecision(16) << temp[n - 1] << endl;
}

int main() {
  int T;
  cin >> T;
  for (int i = 0; i < T; i++) {
    long long n;
    cin >> n;
    long long q;
    cin >> q;
    vector<vector<long long>> v(n, vector<long long>(2));
    for (int i1 = 0; i1 < n; i1++) {
      for (int i2 = 0; i2 < 2; i2++) {
        cin >> v[i1][i2];
      }
    }
    vector<vector<long long>> g(n, vector<long long>(n));
    for (int i1 = 0; i1 < n; i1++) {
      for (int i2 = 0; i2 < n; i2++) {
        cin >> g[i1][i2];
      }
    }
    vector<vector<long long>> d(n, vector<long long>(n));
    for (int i1 = 0; i1 < q; i1++) {
      for (int i2 = 0; i2 < 2; i2++) {
        cin >> d[i1][i2];
      }
    }

    // cout << n <<" " <<q <<endl;
    //
    // for (int i1 = 0; i1< n; i1++) {
    //     for (int i2 = 0; i2 < 2;i2++) {
    //         cout << v[i1][i2]<<" ";
    //     }
    //     cout <<endl;
    // }
    // for (int i1 = 0; i1< n; i1++) {
    //     for (int i2 = 0; i2 < n;i2++) {
    //         cout << g[i1][i2]<<" ";
    //     }
    //     cout<<endl;
    // }
    // for (int i1 = 0; i1< q; i1++) {
    //     for (int i2 = 0; i2 < 2;i2++) {
    //         cout<< d[i1][i2]<<" ";
    //     }
    //     cout<<endl;
    // }
    cout << setprecision(16) << "Case #" << i + 1 << ": ";
    solve(v, g, d, n, q);
  }
  return 0;
}

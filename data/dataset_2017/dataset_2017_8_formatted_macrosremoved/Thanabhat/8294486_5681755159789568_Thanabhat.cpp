#include <iostream>

using namespace std;

int solve(int cc) {
  long long n, q, e[105], s[105], d[105], temp;
  cin >> n >> q;
  for (int i = 0; i < n; i++) {
    cin >> e[i] >> s[i];
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (j == i + 1) {
        cin >> d[i];
      } else {
        cin >> temp;
      }
    }
  }
  cin >> temp >> temp;

  //    for(int i=0;i<n;i++){
  //        cout<<e[i]<<" "<<s[i]<<" "<<d[i]<<endl;
  //    }

  long double dp[105];
  for (int i = 0; i < n; i++) {
    dp[i] = 1e11;
  }
  dp[n - 1] = 0;
  for (int i = n - 2; i >= 0; i--) {
    long double sss = 0;
    long long ee = e[i];
    long double tt = 0;
    for (int j = i; j < n - 1; j++) {
      ee -= d[j];
      if (ee < 0) {
        break;
      }
      tt += (1.0 * d[j]) / s[i];
      //            cout<<"->"<<tt<<" "<<d[j]<<" "<<s[i]<<" "<<tt+dp[j+1]<<endl;
      if (j == i || tt + dp[j + 1] < sss) {
        sss = tt + dp[j + 1];
        //                cout<<sss;
      }
    }
    dp[i] = sss;
    //        cout<<"-->"<<dp[i]<<endl;
  }
  cout << "Case #" << cc << ": " << fixed << dp[0] << endl;
  return 1;
}

int main() {
  int t;
  cin >> t;
  cout.precision(7);
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
  return 0;
}

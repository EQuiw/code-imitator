
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int N, Q;
vector<double> E, S;
vector<vector<ll>> D;

void solve() {
  //    cout << "hogege" << endl;

  for (int k = 0; k < N; k++) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++)
        if (D[i][k] != -1 && D[k][j] != -1) {
          if (D[i][j] == -1)
            D[i][j] = D[i][k] + D[k][j];
          else
            D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
        }
    }
  }

  //    cout << "fugaga" << endl;

  //    for(int i=0; i<N; i++){
  //        for(int j=0; j<N; j++)
  //            cout << D[i][j] << " ";
  //        cout << endl;
  //    }

  vector<vector<double>> nD(N, vector<double>(N, 1e100));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++)
      if (D[i][j] != -1 && D[i][j] <= E[i]) {
        nD[i][j] = min(nD[i][j], D[i][j] / S[i]);
      }
  }

  //    for(int i=0; i<N; i++){
  //        for(int j=0; j<N; j++)
  //            cout << nD[i][j] << " ";
  //        cout << endl;
  //    }

  //    cout << "hoge" << endl;

  for (int k = 0; k < N; k++)
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
        nD[i][j] = min(nD[i][j], nD[i][k] + nD[k][j]);

  //    cout << "fuga" << endl;

  for (int i = 0; i < Q; i++) {
    int s, t;
    cin >> s >> t;
    s--;
    t--;
    cout << " " << nD[s][t];
  }
  cout << endl;
}

int main() {
  cout.precision(16);
  cout.setf(ios::fixed);

  int T;
  cin >> T;
  for (int i = 0; i < T; i++) {
    cout << "Case #" << i + 1 << ":";
    cin >> N >> Q;
    E.resize(N);
    S.resize(N);
    for (int i = 0; i < N; i++)
      cin >> E[i] >> S[i];

    //        D.resize(N, vector<ll>(N));
    D.clear();

    //        cout << "unko" << endl;
    for (int i = 0; i < N; i++) {
      vector<ll> vec(N);
      for (int j = 0; j < N; j++) {
        cin >> vec[j];
      }
      D.push_back(vec);
      //    cout << D[i].size() << endl;
    }
    //        cout << "buri" << endl;

    solve();
  }

  return 0;
}

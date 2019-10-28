#include <bits/stdc++.h>
using namespace std;

int main() {
  int T;
  cin >> T;
  cout.precision(15);
  for (int testCase = 1; testCase <= T; testCase++) {
    cout << "Case #" << testCase << ": ";
    long long N, Q;
    cin >> N;
    cin >> Q;
    vector<long long> E(N);
    vector<long long> S(N);
    vector<vector<long long>> D(N, vector<long long>(N));
    for (int i = 0; i < N; i++) {
      cin >> E[i];
      cin >> S[i];
    }
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
        cin >> D[i][j];
    vector<int> U(Q);
    vector<int> V(Q);
    for (int i = 0; i < Q; i++) {
      cin >> U[i];
      cin >> V[i];
    }
    if (Q == 1 && U[0] == 1 && V[0] == N) {
      vector<vector<double>> H(N, vector<double>(N, 1e100));
      for (int i = 0; i < N; i++) {
        if (i == 0)
          H[i][i] = 0;
        else {
          for (int j = 0; j < i; j++)
            H[i][i] = min(H[i][i], H[j][i]);
        }
        int idx = i + 1;
        long long Er = E[i];
        while (idx < N && Er >= D[idx - 1][idx]) {
          H[i][idx] = H[i][idx - 1] + double(D[idx - 1][idx]) / S[i];
          Er -= D[idx - 1][idx];
          idx++;
        }
      }
      double best = 1e200;
      for (int i = 0; i < N; i++)
        best = min(best, H[i][N - 1]);
      cout << best; // << endl;
                    /*for(int i = 0; i < N; i++){
                            for(int j = 0; j < N; j++) cout << H[i][j] << ", ";
                            cout << endl;
                    }*/
    }
    cout << endl;
  }
  return 0;
}

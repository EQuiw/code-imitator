#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
  ifstream fin("/home/roman/CodeliteProjects/Competitive/GCJ17_Quals/in.txt");
  ofstream fout("/home/roman/CodeliteProjects/Competitive/GCJ17_Quals/out.txt");

  int t;
  fin >> t;
  for (int testcase = 0; testcase < t; ++testcase) {
    string s;
    int k;
    fin >> s >> k;
    int n = s.size();

    vector<bool> v;
    for (int i = 0; i < n; ++i) {
      v.push_back(s[i] == '+');
    }

    int cnt = 0;
    for (int i = 0; i < n - k + 1; ++i) {
      if (!v[i]) {
        for (int j = i; j < i + k; ++j) {
          v[j] = !v[j];
        }
        cnt++;
      }

      //			FORi(j,0,n){
      //				cout << v[j];
      //			}
      //			cout << endl;
    }

    for (int i = n - k; i < n; ++i) {
      if (!v[i]) {
        cnt = -1;
      }
    }

    fout << "Case #" << testcase + 1 << ": ";
    if (cnt == -1) {
      fout << "IMPOSSIBLE" << endl;
    } else {
      fout << cnt << endl;
    }
  }

  fin.close();
  fout.close();
  return 0;
}

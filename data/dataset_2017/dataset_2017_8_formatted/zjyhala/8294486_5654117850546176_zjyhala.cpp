#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
using namespace std;

int N, A, B, C, AB, BC, AC, _A, _B, _C, _AB, _BC, _AC;
string ans[1009];
map<string, string> Col;

void Output(string s1, string s2, int t) {
  for (int i = 1; i <= t; i++)
    cout << Col[s1] << Col[s2];
  cout << "\n";
}

bool Solve() {
  _A = A;
  _B = B;
  _C = C;
  _AB = AB;
  _BC = BC;
  _AC = AC;
  if (AB < C)
    C -= AB;
  else if (AB > C)
    return false;
  else if (AB == C) {
    if (AB == 0)
      ;
    else if (AB + C == N) {
      Output("AB", "C", N / 2);
      return true;
    } else
      return false;
  }

  if (BC < A)
    A -= BC;
  else if (BC > A)
    return false;
  else if (BC == A) {
    if (BC == 0)
      ;
    else if (BC + A == N) {
      Output("BC", "A", N / 2);
      return true;
    } else
      return false;
  }

  if (AC < B)
    B -= AC;
  else if (AC > B)
    return false;
  else if (AC == B) {
    if (AC == 0)
      ;
    else if (AC + B == N) {
      Output("AC", "B", N / 2);
      return true;
    } else
      return false;
  }

  if (A > B + C || B > A + C || C > A + B)
    return false;
  // cerr<<A<<" "<<B<<" "<<C<<"\n";
  if (A + B + C == 1) {
    if (A == 1)
      ans[0] = "A";
    if (B == 1)
      ans[0] = "B";
    if (C == 1)
      ans[0] = "C";
  } else {
    int L = min(A, min(B, C));
    A -= L;
    B -= L;
    C -= L;
    N = 3 * L;
    for (int i = 0; i < L; i++) {
      ans[i * 3] = "A";
      ans[i * 3 + 1] = "B";
      ans[i * 3 + 2] = "C";
    }
    if (N == 0) {
      int R;
      if (A == 0) {
        R = min(B, C);
        B -= R;
        C -= R;
        N = 2 * R;
        for (int i = 0; i < R; i++) {
          ans[i * 2] = "B";
          ans[i * 2 + 1] = "C";
        }
      } else if (B == 0) {
        R = min(A, C);
        A -= R;
        C -= R;
        N = 2 * R;
        for (int i = 0; i < R; i++) {
          ans[i * 2] = "A";
          ans[i * 2 + 1] = "C";
        }
      } else if (C == 0) {
        R = min(A, B);
        A -= R;
        B -= R;
        N = 2 * R;
        for (int i = 0; i < R; i++) {
          ans[i * 2] = "A";
          ans[i * 2 + 1] = "B";
        }
      }
    }
    for (; A > 0 || B > 0 || C > 0;) {
      // cerr<<A<<" "<<B<<" "<<C<<"   "<<"N="<<N<<"\n";
      // for(int i=0;i<N;i++) cerr<<ans[i];cerr<<"\n";
      bool ck;

      if (A > 0) {
        ck = false;
        for (int i = 0; i < N; i++)
          if (ans[i] != "A" && ans[(i + 1) % N] != "A") {
            for (int j = N; j >= i + 2; j--)
              ans[j] = ans[j - 1];
            ans[i + 1] = "A";
            N++;
            A--;
            ck = true;
            break;
          }
        if (ck)
          continue;
      }
      if (B > 0) {
        ck = false;
        for (int i = 0; i < N; i++)
          if (ans[i] != "B" && ans[(i + 1) % N] != "B") {
            for (int j = N; j >= i + 2; j--)
              ans[j] = ans[j - 1];
            ans[i + 1] = "B";
            N++;
            B--;
            ck = true;
            break;
          }
        if (ck)
          continue;
      }
      if (C > 0) {
        ck = false;
        for (int i = 0; i < N; i++)
          if (ans[i] != "C" && ans[(i + 1) % N] != "C") {
            for (int j = N; j >= i + 2; j--)
              ans[j] = ans[j - 1];
            ans[i + 1] = "C";
            N++;
            C--;
            ck = true;
            break;
          }
        if (ck)
          continue;
      }
    }
    // for(int i=0;i<N;i++) cerr<<ans[i];cerr<<"\n";
  }
  bool cA = 0, cB = 0, cC = 0;
  for (int i = 0; i < N; i++) {
    cout << Col[ans[i]];
    if (cA == 0 && ans[i] == "A") {
      for (int j = 0; j < _BC; j++)
        cout << Col["BC"] << Col["A"];
      cA = 1;
    }
    if (cB == 0 && ans[i] == "B") {
      for (int j = 0; j < _AC; j++)
        cout << Col["AC"] << Col["B"];
      cB = 1;
    }
    if (cC == 0 && ans[i] == "C") {
      for (int j = 0; j < _AB; j++)
        cout << Col["AB"] << Col["C"];
      cC = 1;
    }
  }
  cout << "\n";
  return true;
}

int main() {
  Col.clear();
  Col["A"] = "R";
  Col["B"] = "Y";
  Col["C"] = "B";
  Col["AB"] = "O";
  Col["BC"] = "G";
  Col["AC"] = "V";
  int Test;
  cin >> Test;
  for (int i = 1; i <= Test; i++) {
    cin >> N >> A >> AB >> B >> BC >> C >> AC;
    cout << "Case #" << i << ": ";
    bool tmp = Solve();
    if (!tmp)
      cout << "IMPOSSIBLE\n";
  }
}
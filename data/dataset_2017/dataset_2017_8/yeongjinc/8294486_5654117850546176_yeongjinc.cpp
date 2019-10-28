#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <cmath>
#include <numeric>
#include <climits>

using namespace std;

const string IMP = "IMPOSSIBLE";

void print(int testNo, string ans) {
  cout << "Case #" << testNo << ": " << ans << endl;
}


string replace(string s, char p, const string& n) {
  int pos = s.find(p);
  string ret = s.substr(0, pos);
  ret += n;
  ret += s.substr(pos + 1);
  return ret;
}

string getNew(char A, char B, int rep) {
  string ret = "";
  ret += A;
  for (int i = 0; i < rep; ++i) {
    ret += B;
    ret += A;
  }
  // cout << ret << endl;
  return ret;
}

string getShort(int R, int Y, int B) {
  string ret;
  //cout << R << Y << B << endl;
  while (R > 0 || Y > 0 || B > 0) {
    if (ret.size() == 0) {
      int maxCnt = max({R, Y, B});
      if (R == maxCnt) {
        ret += 'R';
        --R;
      } else if (Y == maxCnt) {
        ret += 'Y';
        --Y;
      } else {
        ret += 'B';
        --B;
      }
    } else {
      if (ret[ret.size() - 1] == 'R') {
        if (Y > B) {
          ret += 'Y', --Y;
        } else if (Y < B) {
          ret += 'B', --B;
        } else if (Y == 0) {
          return IMP;
        } else if (ret.size() == 1) {
          ret += 'Y', --Y;
        } else if (ret[0] == 'Y') {
          ret += 'Y', --Y;
        } else {
          ret += 'B', --B;
        }
      }
      else if (ret[ret.size() - 1] == 'Y') {
        if (B > R) {
          ret += 'B', --B;
        } else if (B < R) {
          ret += 'R', --R;
        } else if (B == 0) {
          return IMP;
        } else if (ret.size() == 1) {
          ret += 'B', --B;
        } else if (ret[0] == 'B') {
          ret += 'B', --B;
        } else {
          ret += 'R', --R;
        }
      }
      else {
        if (R > Y) {
          ret += 'R', --R;
        } else if (R < Y) {
          ret += 'Y', --Y;
        } else if (R == 0) {
          return IMP;
        } else if (ret.size() == 1) {
          ret += 'R', --R;
        } else if (ret[0] == 'R') {
          ret += 'R', --R;
        } else {
          ret += 'Y', --Y;
        }
      }
    }
    //cout << ret << endl;
  }
  if (ret.size() > 1 && ret[0] == ret[ret.size() - 1])
    return IMP;
  return ret;
}

string getLong(int R, int O, int Y, int G, int B, int V) {
  int nR = R - G;
  int nY = Y - V;
  int nB = B - O;

  if (R == G && O == 0 && Y == 0 && B == 0 && V == 0)
    return getNew('R', 'G', G - 1) + 'G';
  if (Y == V && O == 0 && R == 0 && B == 0 && G == 0)
    return getNew('Y', 'V', V - 1) + 'V';
  if (B == O && R == 0 && Y == 0 && B == 0 && V == 0)
    return getNew('B', 'O', O - 1) + 'O';


  if (G > 0 && R < G + 1) return IMP;
  if (V > 0 && Y < V + 1) return IMP;
  if (O > 0 && B < O + 1) return IMP;

  string s = getShort(nR, nY, nB);
  if (s == IMP)
    return IMP;

  if (G > 0)
    s = replace(s, 'R', getNew('R', 'G', G));
  if (V > 0)
    s = replace(s, 'Y', getNew('Y', 'V', V));
  if (O > 0)
    s = replace(s, 'B', getNew('B', 'O', O));

  return s;
}

int main() {
  int totalTestNo;
  cin >> totalTestNo;
  for (int testNo = 1; testNo <= totalTestNo; ++testNo) {
    int N, R, O, Y, G, B, V;
    cin >> N >> R >> O >> Y >> G >> B >> V;
    string ans = getLong(R, O, Y, G, B, V);
    print(testNo, ans);
  }
}

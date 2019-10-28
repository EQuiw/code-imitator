#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

int max(int a1, int a2, int a3, int a4, int a5, int a6) {
  int m1 = max(a1, a2);
  int m2 = max(a3, a4);
  int m3 = max(a5, a6);
  return max(m1, max(m2, m3));
}

bool comp(char a, char b) {
  if (a == 'R') {
    if (b == 'O' || b == 'V' || b == 'R')
      return false;
    return true;
  }
  if (a == 'Y') {
    if (b == 'O' || b == 'G' || b == 'Y')
      return false;
    return true;
  }
  if (a == 'B') {
    if (b == 'G' || b == 'V' || b == 'B')
      return false;
    return true;
  }
  if (a == 'O') {
    if (b == 'B')
      return true;
    return false;
  }
  if (a == 'G') {
    if (b == 'R')
      return true;
    return false;
  }
  if (a == 'V') {
    if (b == 'Y')
      return true;
    return false;
  }
}

int main() {
  int T;
  cin >> T;
  for (int I = 1; I <= T; I++) {
    cout << "Case #" << I << ": ";
    int n, r, o, y, g, b, v;
    cin >> n >> r >> o >> y >> g >> b >> v;

    for (int ii = 0; ii < 100; ii++) {
      int ri = r, oi = o, yi = y, gi = g, bi = b, vi = v;
      int ni = n;
      vector<char> ans;
      while (ni > 0) {
      bbb:;
        vector<char> vc;
        vector<pair<int, char>> aaa;
        /*pair<int,char> pp;
        aaa.push_back(make_pair(-ri,rand()%2?'R':'r'));
        aaa.push_back(make_pair(-oi,rand()%2?'O':'o'));
        aaa.push_back(make_pair(-yi,rand()%2?'Y':'y'));
        aaa.push_back(make_pair(-gi,rand()%2?'G':'g'));
        aaa.push_back(make_pair(-bi,rand()%2?'B':'b'));
        aaa.push_back(make_pair(-vi,rand()%2?'V':'v'));
        sort(aaa.begin(),aaa.end());
        for(int i=0;i<aaa.size();i++)
        {
                vc.push_back(aaa[i].second&(~32));// magic
                random_shuffle(vc.begin(),vc.end());
        }*/

        if (ri)
          vc.push_back('R');
        if (oi)
          vc.push_back('O');
        if (yi)
          vc.push_back('Y');
        if (gi)
          vc.push_back('G');
        if (bi)
          vc.push_back('B');
        if (vi)
          vc.push_back('V');
        random_shuffle(vc.begin(), vc.end());
        if (ni == n) {
          ni--;
          ans.push_back(vc[0]);
          if (vc[0] == 'R')
            ri--;
          if (vc[0] == 'O')
            oi--;
          if (vc[0] == 'Y')
            yi--;
          if (vc[0] == 'G')
            gi--;
          if (vc[0] == 'B')
            bi--;
          if (vc[0] == 'V')
            vi--;

          goto bbb;
        }
        int mx = max(ri, oi, yi, gi, bi, vi);
        aaa.push_back(make_pair(-ri, 'R'));
        aaa.push_back(make_pair(-oi, 'O'));
        aaa.push_back(make_pair(-yi, 'Y'));
        aaa.push_back(make_pair(-gi, 'G'));
        aaa.push_back(make_pair(-bi, 'B'));
        aaa.push_back(make_pair(-vi, 'V'));
        sort(aaa.begin(), aaa.end());
        for (int i = 0; i < aaa.size(); i++) {
          if (aaa[i].first < 0 && aaa[i].second == 'R' &&
              comp(ans[ans.size() - 1], 'R')) {
            ans.push_back('R');
            ni--;
            ri--;
            goto bbb;
          }
          if (aaa[i].first < 0 && aaa[i].second == 'O' &&
              comp(ans[ans.size() - 1], 'O')) {
            ans.push_back('O');
            ni--;
            oi--;
            goto bbb;
          }
          if (aaa[i].first < 0 && aaa[i].second == 'Y' &&
              comp(ans[ans.size() - 1], 'Y')) {
            ans.push_back('Y');
            ni--;
            yi--;
            goto bbb;
          }
          if (aaa[i].first < 0 && aaa[i].second == 'G' &&
              comp(ans[ans.size() - 1], 'G')) {
            ans.push_back('G');
            ni--;
            gi--;
            goto bbb;
          }
          if (aaa[i].first < 0 && aaa[i].second == 'B' &&
              comp(ans[ans.size() - 1], 'B')) {
            ans.push_back('B');
            ni--;
            bi--;
            goto bbb;
          }
          if (aaa[i].first < 0 && aaa[i].second == 'V' &&
              comp(ans[ans.size() - 1], 'V')) {
            ans.push_back('V');
            ni--;
            yi--;
            goto bbb;
          }
        }
        /*
        for(int i=0;i<vc.size();i++)
        {
                if(vc[i]=='R' && comp(ans[ans.size()-1],'R'))
                {
                        ans.push_back('R');
                        ni--;
                        ri--;
                        goto bbb;
                }
                if(vc[i]=='O' && comp(ans[ans.size()-1],'O'))
                {
                        ans.push_back('O');
                        ni--;
                        oi--;
                        goto bbb;
                }
                if(vc[i]=='Y' && comp(ans[ans.size()-1],'Y'))
                {
                        ans.push_back('Y');
                        ni--;
                        yi--;
                        goto bbb;
                }
                if(vc[i]=='G' && comp(ans[ans.size()-1],'G'))
                {
                        ans.push_back('G');
                        ni--;
                        gi--;
                        goto bbb;
                }
                if(vc[i]=='B' && comp(ans[ans.size()-1],'B'))
                {
                        ans.push_back('B');
                        ni--;
                        bi--;
                        goto bbb;
                }
                if(vc[i]=='V' && comp(ans[ans.size()-1],'V'))
                {
                        ans.push_back('V');
                        ni--;
                        vi--;
                        goto bbb;
                }
                //break;
        }*/
        break;
      }
      if (!comp(ans[0], ans[ans.size() - 1]))
        ni++;
      if (!ni) {
        for (int i = 0; i < n; i++)
          cout << ans[i];
        cout << endl;
        goto aaa;
      }
    }
    cout << "IMPOSSIBLE" << endl;
  aaa:;
    cerr << I << endl;
  }
}

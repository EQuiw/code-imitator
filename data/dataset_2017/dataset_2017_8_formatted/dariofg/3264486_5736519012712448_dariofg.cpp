#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

int f(const vector<bool> &v, int k) {
  queue<pair<vector<bool>, int>> q;
  pair<vector<bool>, int> p1, p2, p3;
  p1.first = v;
  p1.second = 0;
  q.push(p1);
  set<vector<bool>> st;
  while (!q.empty()) {
    p1 = q.front();
    q.pop();
    for (int i = 0; i < v.size(); i++) {
      // cout << p1.first[i] << endl;
      if (!p1.first[i])
        goto aaaa;
    }
    return p1.second;
  aaaa:;
    // cout << "HELP" << endl;
    if (st.find(p1.first) != st.end())
      continue;
    // cout << "HELP2" << endl;
    st.insert(p1.first);
    // cout << "HELP3" << endl;
    p2.second = p1.second + 1;
    p2.first = vector<bool>(v.size());
    for (int i = 0; i < k; i++)
      p2.first[i] = !p1.first[i];
    for (int i = k; i < v.size(); i++)
      p2.first[i] = p1.first[i];
    // cout << "HELP3" << endl;

    q.push(p2);

    // cout << "HELP3" << endl;
    for (int i = k; i < v.size(); i++) {

      //	cout << "HELP3" << endl;
      p2.first[i] = !p1.first[i];
      p2.first[i - k] = p1.first[i - k];
      q.push(p2);
    }
  }
  return -1;
}

int main() {
  int T;
  cin >> T;
  for (int I = 1; I <= T; I++) {
    cout << "Case #" << I << ": ";
    string s;
    int k;
    cin >> s >> k;
    vector<bool> v(s.size());
    for (int i = 0; i < v.size(); i++)
      v[i] = s[i] == '+';
    int aaa = k - 1;
    int bbb = v.size() - k;
    bool ok = true; /*
       if(bbb<aaa)
       {
               for(int i=bbb;i<=aaa;i++)
               {
                       if(v[i]!=v[bbb])
                               ok = false;
               }
       }*/
    if (!ok)
      cout << "IMPOSSIBLE" << endl;
    else {
      int a = f(v, k);
      if (a >= 0)
        cout << a << endl;
      else
        cout << "IMPOSSIBLE" << endl;
    }
  }
}

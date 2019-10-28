#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef void (*VoidFunc)(ll, ll, ll);

ll t, n;
ll r, y, b, tmp;
bool solved = false;
ll TME;

void colR(ll, ll, ll), colB(ll, ll, ll), colY(ll, ll, ll);

vector<ll> anw;
void rec(ll r, ll y, ll b) {
  if (solved || (double)(clock() - TME) / CLOCKS_PER_SEC > 1) {
    return;
  }
  if (anw.size() < n - 1) {
    VoidFunc funcs[] = {colR, colY, colB};
    random_shuffle(funcs, funcs + 3);
    funcs[0](r, y, b);
    funcs[1](r, y, b);
    funcs[2](r, y, b);
  } else {
    if (r > 0 && (anw.back() != 'R' && anw[0] != 'R')) {
      anw.push_back('R');
      solved = true;
      for (char l : anw)
        cout << l;
      cout << endl;
    } else if (y > 0 && (anw.back() != 'Y' && anw[0] != 'Y')) {
      anw.push_back('Y');
      solved = true;
      for (char l : anw)
        cout << l;
      cout << endl;
    } else if (b > 0 && (anw.back() != 'B' && anw[0] != 'B')) {
      anw.push_back('B');
      solved = true;
      for (char l : anw)
        cout << l;
      cout << endl;
    }
  }
}

void colR(ll r, ll y, ll b) {
  if (r > 0 && (anw.empty() || anw.back() != 'R')) {
    anw.push_back('R');
    rec(r - 1, y, b);
    anw.pop_back();
  }
}

void colY(ll r, ll y, ll b) {
  if (y > 0 && (anw.empty() || anw.back() != 'Y')) {
    anw.push_back('Y');
    rec(r, y - 1, b);
    anw.pop_back();
  }
}

void colB(ll r, ll y, ll b) {
  if (b > 0 && (anw.empty() || anw.back() != 'B')) {
    anw.push_back('B');
    rec(r, y, b - 1);
    anw.pop_back();
  }
}

void solve() {
  TME = clock();
  cin >> n >> r >> tmp >> y >> tmp >> b >> tmp;
  solved = false;
  anw.clear();
  rec(r, y, b);
  if (!solved) {
    cout << "IMPOSSIBLE" << endl;
  }
}

int main() {
  ios::sync_with_stdio(0);
  cout.precision(10);
  cin >> t;
  for (int i = 1; i <= t; i++) {
    cout << "Case #" << i << ": ";
    solve();
  }
}

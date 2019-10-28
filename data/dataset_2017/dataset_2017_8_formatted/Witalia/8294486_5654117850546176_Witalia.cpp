#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <map>
#include <memory.h>
#include <set>
#include <stdio.h>
#include <string>
#include <vector>
#define _USE_MATH_DEFINES
#include <complex>
#include <fstream>
#include <iomanip>
#include <limits.h>
#include <list>
#include <math.h>
#include <queue>
#include <stack>
#include <time.h>

#define Cpp11
#ifdef Cpp11
#include <atomic>
#include <cassert>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <random>
#include <regex>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <valarray>
using namespace std::chrono;
#endif
using namespace std;

typedef double ld;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

// const int mx[4] = { 1, 0, -1, 0 };
// const int my[4] = { 0, 1, 0, -1 };

const int Inf = 1000000000;
const int Mi = 1000000007;
const int N = 500005;
const int M = 100005;
// const int K = 20;
const ld eps = 10e-7;
const ld PI = 2 * acos(0.0);
const ll InfLL = ll(Inf) * ll(Inf);

unsigned rand16() { return rand() % (1 << 16); }
unsigned rand32() { return (rand16() << 16) + rand16(); }
ull rand64() { return (((ull)rand32()) << 32) + rand32(); }
int rand(int L, int R) {
  if (L > R)
    return R;
  return rand32() % (R - L + 1) + L;
}
ld random(ld L, ld R) {
  return rand(ceil((L - eps) * 100), floor((R + eps) * 100)) / 100.0;
}

ll Abs(ll a) { return a < 0 ? -a : a; }
ll sqr(ll a) { return a * a; }
ll gcd(ll a, ll b) { return !b ? a : gcd(b, a % b); }

string toStr(int n) {
  char s[100];
  sprintf(s, "%d", n);
  return string(s);
}

// Red					->	Yellow, Blue, Green
// Yellow				->	Red, Blue, Violet
// Blue					->	Red, Yellow, Orange
// Orange(red + yellow)	->	Blue
// Green(yellow + blue)	->	Red
// Violet(red + blue)	->	Yellow

//#define ONLINE_JUDGE
int main() {
  std::ios_base::sync_with_stdio(0);
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int T;
  cin >> T;
  for (int t = 0; t < T; ++t) {
    cout << "Case #" << (t + 1) << ": ";

    int n, R, O, Y, G, B, V;
    cin >> n >> R >> O >> Y >> G >> B >> V;
    string ans = "";

    // Try to alternate two colours
    if (R == G && R + G == n || O == B && O + B == n || V == Y && V + Y == n) {
      string two = R ? "RG" : (O ? "OB" : "VY");
      int cnt = max(R, max(Y, B));
      for (; cnt--;)
        ans += two;
    }
    // for x two-colours at least x+1 of opposite one-colour
    else if ((B > O || O == 0) && (R > G || G == 0) && (Y > V || V == 0)) {
      R -= G;
      B -= O;
      Y -= V;
      if (R <= B + Y && B <= R + Y && Y <= R + B) {
        pair<int, char> cols[] = {make_pair(R, 'R'), make_pair(B, 'B'),
                                  make_pair(Y, 'Y')};
        sort(cols, cols + 3);
        int fst_spare = cols[0].first - (cols[2].first - cols[1].first);
        for (int i = 0; i < cols[2].first; ++i) {
          ans += cols[2].second;
          if (cols[1].first) {
            --cols[1].first;
            ans += cols[1].second;
            if (fst_spare) {
              --fst_spare;
              ans += cols[0].second;
            }
          } else {
            ans += cols[0].second;
          }
        }
      }
      string x = ans;
      ans = "";
      for (char q : x) {
        for (int i = 0; i < (q == 'R' ? G : (q == 'B' ? O : V)); ++i) {
          ans += (q == 'R' ? "RG" : (q == 'B' ? "BO" : "YV"));
        }
        (q == 'R' ? G : (q == 'B' ? O : V)) = 0;
        ans += q;
      }
    }

    if (ans.size() != n && ans != "") {
      cout << "PROBLEM \n";
    }
    for (int i = 0; i < ans.size(); ++i) {
      if (ans[i] == ans[(i + 1) % ans.size()]) {
        cout << "PROBLEM\n";
      }
      (ans[i] == 'R' ? R : (ans[i] == 'B' ? B : Y)) -= 1;
    }
    if ((R != 0 || B != 0 || Y != 0) && ans != "") {
      cout << "PROBLEM\n";
    }

    cout << (ans == "" ? "IMPOSSIBLE" : ans) << endl;
  }
  return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <string>
#include <memory.h>
#include <map>
#define _USE_MATH_DEFINES
#include <math.h>
#include <list>
#include <fstream>
#include <time.h>
#include <iomanip>
#include <queue>
#include <stack>
#include <complex>
#include <limits.h>

#define Cpp11
#ifdef Cpp11
#include <cassert>
#include <chrono>
#include <regex>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <valarray>
using namespace std::chrono;
#endif
using namespace std;

typedef double ld;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<vi> vvi;
//typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

const int mx[4] = { 1, 0, -1, 0 };
const int my[4] = { 0, 1, 0, -1 };

const int Inf = 1000000000;
const int Mi = 1000000007;
const int N = 15;
const int M = 100005;
//const int K = 20;
const ld eps = 10e-7;
const ld PI = 2 * acos(0.0);
const ll InfLL = ll(Inf) * ll(Inf);

unsigned rand16() { return rand() % (1 << 16); }
unsigned rand32() { return (rand16() << 16) + rand16(); }
ull rand64() { return (((ull)rand32()) << 32) + rand32(); }
int rand(int L, int R) { if (L > R) return R; return rand32() % (R - L + 1) + L; }
ld random(ld L, ld R) { return rand(ceil((L - eps) * 100), floor((R + eps) * 100)) / 100.0; }

ll Abs(ll a) { return a < 0 ? -a : a; }
ll sqr(ll a) { return a*a; }
ll gcd(ll a, ll b) { return !b ? a : gcd(b, a % b); }


string toStr(int n) {
    char s[100];
    sprintf(s, "%d", n);
    return string(s);
}

struct pll {
    ll l, r;
    int i;
};

auto comp_l = [](const pll a, const pll b) {
    return a.l > b.l || a.l == b.l && (a.r > b.r || a.r == b.r && a.i > b.i);
};

auto comp_r = [](const pll a, const pll b) {
    return a.r < b.r || a.r == b.r && (a.l < b.l || a.l == b.l && a.i < b.i);
};

int n, p;
ll R[N];
ll A[N][N];
pll B[N][N];
int ptr[N];
multiset<pll, decltype(comp_l)> by_l(comp_l);
multiset<pll, decltype(comp_r)> by_r(comp_r);

pll get_bounds(ll Q, int tp) {
    ll r = 10 * Q / (9 * R[tp]);
    ll l = 10 * Q;
    ll denom = 11 * R[tp];
    l = (l + denom - 1) / denom;
    return pll{ l, r, tp };
}

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

        cin >> n >> p;
        for (int i = 0; i < n; ++i) {
            cin >> R[i];
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < p; ++j) {
                cin >> A[i][j];
            }
            sort(A[i], A[i] + p);
            for (int j = 0; j < p; ++j) {
                B[i][j] = get_bounds(A[i][j], i);
            }
        }
        by_l.clear();
        by_r.clear();
        for (int i = 0; i < n; ++i) {
            by_l.insert(B[i][0]);
            by_r.insert(B[i][0]);
            ptr[i] = 0;
        }
        ll ans = 0;
        for (;;) {
            auto x = *by_l.begin();
            auto y = *by_r.begin();
            if (y.r < x.l) {
                by_r.erase(by_r.find(y));
                by_l.erase(by_l.find(y));
                ++ptr[y.i];
                if (ptr[y.i] != p) {
                    by_l.insert(B[y.i][ptr[y.i]]);
                    by_r.insert(B[y.i][ptr[y.i]]);
                }
            }
            else {
                ++ans;
                by_l.clear();
                by_r.clear();
                for (int i = 0; i < n; ++i) {
                    ++ptr[i];
                    if (ptr[i] != p) {
                        by_l.insert(B[i][ptr[i]]);
                        by_r.insert(B[i][ptr[i]]);
                    }
                }
            }
            if (by_l.size() != n) {
                break;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
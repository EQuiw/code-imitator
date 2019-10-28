#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <climits>
#include <vector>
#include <string>
#include <queue>
#include <deque>
#include <list>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <fstream>

#define int long long
#define MOD7 1000000007
#define MOD9 1000000009

#define rep(i, n) for (int i = 0; i < (n); i++)
#define REP(i, a, n) for (int i = (a); i <= (n); i++)
#define all(a) (a).begin(), (a).end()

using namespace std;

int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, -1, 0, 1 };

int nextInt() {int a; cin >> a; return a;}
char nextChar() {char a; cin >> a; return a;}
double nextDouble() {double a; cin >> a; return a;}
string nextString() {string a; cin >> a; return a;}

template<class T> void inputVector(vector<T>& v, int n) {
    v.resize(n);
    for (int i = 0; i < v.size(); i++) cin >> v[i];
}

bool nondec(int N) {
	int prev = 9;
	while (N > 0) {
		int tmp = N % 10;
		if (tmp > prev) return false;
		prev = tmp;
		N /= 10;
	}
	return true;
}

signed main() {
	int T;
	cin >> T;

	ofstream out("output-B-small.txt");
	REP(loop, 1, T) {
		int N;
		cin >> N;

		for (int i = N; i > 0; i--) {
			if (nondec(i)) {
				out << "Case #" << loop << ": " << i << endl;
				break;
			}
		}
	}

    return 0;
}

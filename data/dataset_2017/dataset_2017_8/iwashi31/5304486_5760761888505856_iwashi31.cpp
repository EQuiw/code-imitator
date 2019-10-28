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

signed main() {
	int T;
	cin >> T;

	ofstream out("output-A-small.txt");
	REP(loop, 1, T) {
		int H, W;
		cin >> H >> W;
		
		vector<string> board;
		inputVector(board, H);

		rep(y, H) {
			char prev = '?';
			rep(x, W) {
				if (board[y][x] != '?') {
					prev = board[y][x];
				} else {
					board[y][x] = prev;
				}
			}
		}

		rep(y, H) {
			char prev = '?';
			for (int x = W - 1; x >= 0; x--) {
				if (board[y][x] != '?') {
					prev = board[y][x];
				} else {
					board[y][x] = prev;
				}
			}
		}

		REP(y, 1, H - 1) {
			rep(x, W) {
				if (board[y][x] == '?') {
					board[y][x] = board[y - 1][x];
				}
			}
		}
		for (int y = H - 2; y >= 0; y--) {
			rep(x, W) {
				if (board[y][x] == '?') {
					board[y][x] = board[y + 1][x];
				}
			}
		}

		cout << "Case #" << loop << ":" << endl;
		out << "Case #" << loop << ":" << endl;
		rep(y, H) {
			cout << board[y] << endl;
			out << board[y] << endl;
		}
	}

    return 0;
}

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

class Info {
public:
	int node;
	int leftDist;
	int speed;
	double time;

	Info() {}
	Info(int node, int leftDist, int speed, double time) {
		this->node = node;
		this->leftDist = leftDist;
		this->speed = speed;
		this->time = time;
	}

	bool operator< (const Info &a) const {
		return time > a.time;
	}
};

signed main() {
	int T;
	cin >> T;

	REP(loop, 1, T) {
		int N, Q;
		cin >> N >> Q;

		vector<int> E(N), S(N);
		rep(i, N) cin >> E[i] >> S[i];

		int D[110][110];
		rep(i, N) rep(j, N) cin >> D[i][j];

		rep(i, Q) {
			int gomi;
			cin >> gomi;
			cin >> gomi;
		}

		vector<double> time(N, LLONG_MAX);
		time[0] = 0;

		priority_queue<Info> q;
		q.push(Info(0, 0, 1, 0));
		while (!q.empty()) {
			auto nowinfo = q.top(); q.pop();

			if (nowinfo.node == N - 1) {
				printf("Case #%d: %.8f\n", loop, nowinfo.time);
				break;
			}

			REP(i, nowinfo.node + 1, N - 1) {
				int dist = D[nowinfo.node][i];
				if (dist == -1) continue;
				if (dist <= nowinfo.leftDist) {
					q.push(Info(i, nowinfo.leftDist - dist, nowinfo.speed, nowinfo.time + (double)dist / nowinfo.speed));
				}
				if (dist <= E[nowinfo.node]) {
					q.push(Info(i, E[nowinfo.node] - dist, S[nowinfo.node], nowinfo.time + (double)dist / S[nowinfo.node]));
				}
			}
		}
	}

    return 0;
}

#include <iostream>
#include <cstring>
using namespace std;

int R[50];
int Q[50][50];

int n;
int d[201][201];
int match[201];
bool visited[201];

bool matching(int k) {
	for (int i = 0; i < n; ++i) {
		if (d[k][i] && !visited[i]) {
			visited[i] = true;
			if (match[i] == -1 || matching(match[i])) {
				match[i] = k;
				return true;
			}
		}
	}
	return false;
}

void findInterval(int i, int j, int &a, int &b) {
	int need = R[i];
	int ingre = Q[i][j];
	a = int(ingre / (need * 1.1));
	while (a * need * 1.1 < ingre) {
		++a;
	}
	b = int(ingre / (need * 0.9));
	while (b * need * 0.9 > ingre) {
		--b;
	}
	//cout << need << ' ' << ingre << ' ' << a << ' ' << b << endl;
}

bool judge(int A, int B) {
	int a0, b0, a1, b1;
	findInterval(0, A, a0, b0);
	findInterval(1, B, a1, b1);
	if (a0 > b0 || a1 > b1) {
		return false;
	}
	if (a0 > a1 && a0 > b1) {
		return false;
	}
	if (a1 > a0 && a1 > b0) {
		return false;
	}
	return true;
}

int main() {
	int T;
	cin >> T;
	for (int c = 1; c <= T; ++c) {
		memset(d, 0, sizeof(d));
		memset(match, -1, sizeof(match));
		int N, P;
		cin >> N >> P;
		for (int i = 0; i < N; ++i) {
			cin >> R[i];
		}
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < P; ++j) {
				cin >> Q[i][j];
			}
		}
		if (N == 1) {
			int result = 0;
			for (int i = 0; i < P; ++i) {
				int a, b;
				findInterval(0, i, a, b);
				if (a <= b) {
					++result;
				}
			}
			cout << "Case #" << c << ": " << result << endl;
			continue;
		}
		for (int i = 0; i < P; ++i) {
			for (int j = 0; j < P; ++j) {
				if (judge(i, j)) {
					d[i][j] = 1;
				}
			}
		}/*
		for (int i = 0; i < P; ++i) {
			for (int j = 0; j < P; ++j) {
				cout << d[i][j];
			}
			cout << endl;
		}*/
		int result = 0;
		n = N;
		for (int i = 0; i < N; ++i) {
			memset(visited, false, sizeof(visited));
			if (matching(i)) {
				++result;
			}
		}
		cout << "Case #" << c << ": " << result << endl;
	}
	return 0;
}
#include <iostream>
#include <cstring>
using namespace std;

long long space[4], sum[4];

void print(long long k) {
	--k;
	if (k % 2 == 0) {
		cout << k / 2 << ' ' << k / 2;
	} else {
		cout << k / 2 + 1 << ' ' << k / 2;
	}
}

void update() {
	long long tmpA[4], tmpB[4];
	for (int i = 0; i < 4; ++i) {
		tmpA[i] = space[i];
		tmpB[i] = sum[i];
	}
	for (int j = 0; j < 3; ++j) {
		int maxs = -10, maxi = 0;
		for (int i = 1; i < 4; ++i) {
			if (tmpA[i] > maxs) {
				maxs = space[i];
				maxi = i;
			}
		}
		space[j] = tmpA[maxi];
		sum[j] = tmpB[maxi];
		tmpA[maxi] = -100;
	}
	space[3] = -1;
	sum[3] = 0;
}

void split() {
	int k = space[0] - 1;
	if (k % 2 == 0) {
		for (int i = 1; i < 4; ++i) {
			if (space[i] == k / 2 || space[i] == -1) {
				space[i] = k / 2;
				sum[i] += sum[0] * 2;
				break;
			}
		}
	} else {
		for (int i = 1; i < 4; ++i) {
			if (space[i] == k / 2 + 1|| space[i] == -1) {
				space[i] = k / 2 + 1;
				sum[i] += sum[0];
				break;
			}
		}
		for (int i = 1; i < 4; ++i) {
			if (space[i] == k / 2|| space[i] == -1) {
				space[i] = k / 2;
				sum[i] += sum[0];
				break;
			}
		}
		//cout << space[1] << ' ' << space[2] << endl;
	}
	update();
}

int main() {
	int T;
	cin >> T;
	for (int c = 1; c <= T; ++c) {
		long long N, K;
		cout << "Case #" << c << ": ";
		cin >> N >> K;
		space[0] = space[1] = space[2] = space[3] = -1;
		sum[0] = sum[1] = sum[2] = sum[3] = 0;
		space[0] = N;
		sum[0] = 1;
		while (K > 0) {
			if (K <= sum[0]) {
				print(space[0]);
				break;
			}
			K -= sum[0];
			split();
/*
			for (int i = 0; i < 4; ++i) {
				cout << space[i] << '|' << sum[i] << endl;
			}*/
		}
		cout << endl;
	}
	return 0;
}
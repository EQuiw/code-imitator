//Problem C

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#include<set>

using namespace std;

int get() {
	char c;
	while (c = getchar(), c != '-' && (c < '0' || c > '9'));
	bool flag = (c == '-');
	if (flag)
		c = getchar();
	int x = 0;
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return flag ? -x : x;
}

const int inf = 2000000000;

long long attackRounds(long long A, long long B, long long H) {
	long long ans = (H - 1) / A + 1;
	for (int i = 1; i <= ans; i++) {
		long long tmp = (H - 1) / (A + i * B) + 1;
		ans = min(ans, i + tmp);
	}
	return ans;
}

long long sum(long long A, long long D, long long n) {
	return A * n + D * n * (n - 1) / 2;
}

long long survive(long long A, long long D, long long H, long long m) {
	long long ans = inf;
	for (int i = 0; i <= m; i++) {
		long long A0 = A, H0 = H;
		long long cnt = i, sum = 0;
		for (int j = 0; j < m; j++) {
			if (A0 >= H0) {
				if (cnt && (A0 - D < H0)) {
					A0 = max(A0 - D, 0LL);
					cnt--;
				} else {
					H0 = H;
				}
				sum++;
			} else if (cnt) {
				cnt--;
				sum++;
				A0 = max(A0 - D, 0LL);
			}
			H0 -= A0;
			if (H0 <= 0)
				sum = inf;
		}
		ans = min(ans, sum);
	}
	return ans;
}

int main() {
	int totalTest = get();
	for (int test = 1; test <= totalTest; test++) {
		long long Hd = get(), Ad = get(), Hk = get(), Ak = get(), B = get(), D = get();
		long long Ar = attackRounds(Ad, B, Hk);
		long long Left = Ar, Right = 1000;
		while (Left < Right) {
			long long mid = (Left + Right) / 2;
			if (survive(Ak, D, Hd, mid - 1) > mid - Ar)
				Left = mid + 1;
			else
				Right = mid;
		}
		printf("Case #%d: ", test);
		if (Left == 1000)
			printf("IMPOSSIBLE\n");
		else
			cout << Left << endl;
	}
	return 0;
}

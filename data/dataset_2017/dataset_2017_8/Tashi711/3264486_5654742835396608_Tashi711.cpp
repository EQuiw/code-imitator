#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
#include<map>

using namespace std;

struct node
{
	long long u, v;
	node(int _u = 0, int _v = 0) : u(_u), v(_v) {
	}
	bool operator < (const node &r) const {
		return u < r.u;
	}
};

void work()
{
	long long n, k;
	cin >> n >> k;
	map <long long, long long> f;
	f[n] = 1;
	long long sum = 0;
	long long l = (n - 1) / 2, r = n / 2;
	while (sum < k) {
		long long u = f.rbegin()->first, v = f.rbegin()->second;
		f.erase(u);
		sum += v;
		l = (u - 1) / 2;
		r = u / 2;
		f[l] += v;
		f[r] += v;
	}
	cout << r << ' ' << l << endl;
}

int main()
{
	freopen("my.in", "r", stdin);
	freopen("out.txt", "w", stdout);
	int q;
	cin >> q;
	for (int i = 1; i <= q; ++i) {
		printf("Case #%d: ", i);
		work();
	}
	return 0;
}

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<string>
#include<iomanip>
#include<vector>
#include<map>
#include<set>

using namespace std;

const int N = 1100;

int n, cnt[6];
int ans[N];
char cc[6] = { 'R', 'O', 'Y', 'G', 'B', 'V' };

void pre()
{
	ans[0] = -10000;
}

bool nb(int u, int v)
{
	int res = u - v;
	return (res == 1 || res == -1 || res == 5 || res == -5 || res == 0);
}

bool dfs(int p)
{
	if (p == n + 1) {
		if (!nb(ans[1], ans[n])) {
			return true;
		}
		else {
			return false;
			for (int i = 1; i <= n; ++i) {
				printf("%c", cc[ans[i]]);
			}
			cout << endl;
		}
	}
	vector <int> pos;
	int maxc = -10000;
	for (int i = 0; i < 6; ++i) {
		if (cnt[i] > maxc && ! nb(i, ans[p-1])) {
			pos.clear();
			pos.push_back(i);
			maxc = cnt[i];
		}
		else if (cnt[i] == maxc) {
			pos.push_back(i);
		}
	}
	if (maxc == -10000) {
		return false;
	}
	for (int i = 0; i < (int)pos.size(); ++i) {
		int u = pos[i];
		if (!nb(u, ans[p - 1])) {
			cnt[u]--;
			ans[p] = u;
			bool res = dfs(p + 1);
			if (res) {
				return true;
			}
			cnt[u]++;
		}
	}
	return false;
}


void work()
{
	cin >> n;
	int maxc = 0;
	for (int i = 0; i < 6; ++i) {
		cin >> cnt[i];
		if (cnt[i] > maxc) {
			maxc = cnt[i];
		}
	}
	if (maxc > n / 2) {
		cout << "IMPOSSIBLE" << endl;
		return;
	}
	if (dfs(1)) {
		for (int i = 1; i <= n; ++i) {
			printf("%c", cc[ans[i]]);
		}
		cout << endl;
	}
	else {
		cout << "IMPOSSIBLE" << endl;
	}

}

int main()
{
	freopen("my.in", "r", stdin);
	freopen("out.txt", "w", stdout);

	pre();
	int q;
	cin >> q;
	for (int i = 1; i <= q; ++i) {
		printf("Case #%d: ", i);
		work();
	}
	return 0;
}

#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string solve(int r, int y, int b)
{
	int a[3] = { r, y, b };
	char c[4] = "RYB";
	
	int idx = 0;
	for (int i = 0; i < 3; ++i)
		if (a[i] > a[idx]) idx = i;

	string ret;
	int remain = r + y + b;

	int sidx = idx;
	while (remain)
	{
		ret = ret + c[idx];
		a[idx]--;
		remain--;

		int nidx = -1;
		for (int i = 0; i < 3; ++i)
		{
			if (i == idx) continue;
			if (nidx == -1 || a[i] > a[nidx] || a[i] == a[nidx] && i == sidx) nidx = i;
		}
		idx = nidx;
	}
	return ret;
}

int main()
{
	freopen("B-small-attempt1.in", "r", stdin);
	freopen("B-small-attempt1.out", "w", stdout);

	int T;
	scanf("%d", &T);

	int N, R, O, Y, G, B, V;
	for (int cn = 1; cn <= T; ++cn)
	{
		scanf("%d%d%d%d%d%d%d", &N, &R, &O, &Y, &G, &B, &V);
		if (2 * R > N || 2 * Y > N || 2 * B > N)
		{
			printf("Case #%d: IMPOSSIBLE\n", cn);
			continue;
		}
		string ret = solve(R, Y, B);
		printf("Case #%d: %s\n", cn, ret.c_str());
		if (ret[0] == ret[ret.size() - 1])
		{
			continue;
		}
	}
}
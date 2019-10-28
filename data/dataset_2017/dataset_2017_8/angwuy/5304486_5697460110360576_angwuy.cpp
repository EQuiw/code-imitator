#include <cstdio>
#include <cstring>
#include <algorithm>


const int MAXN = 60;

struct Tseg{
	int l, r;
};

bool cmp(Tseg a, Tseg b)
{
	return a.l < b.l;
}

int n, p;
int a[MAXN];
Tseg s[MAXN][MAXN];
int h[MAXN];

bool merge()
{
	int l = 0;
	int r = 0x7FFFFFFF;
	for (int i = 1; i <= n; ++i)
	{
		if (s[i][h[i]].l > l) l = s[i][h[i]].l;
		if (s[i][h[i]].r < r) r = s[i][h[i]].r;
	}
	return l <= r;
}

bool mov()
{
	for (int i = 1; i <= n; ++i)
	{
		++h[i];
		if (h[i] > p) return false;
	}
	return true;
}



void init()
{
	scanf("%d %d", &n, &p);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &a[i]);
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= p; ++j)
		{
			int q;
			scanf("%d", &q);
			s[i][j].l = (int)(q / 1.1 / (double)a[i] - 1E-8) + 1;
			s[i][j].r = (int)(q / 0.9 / (double)a[i]);
		}
	}
	for (int i = 1; i <= n; ++i)
		std::sort(s[i] + 1, s[i] + p + 1, cmp);
}

void solve()
{
	int t = 0;
	for (int i = 1; i <= n; ++i)
		h[i] = 1;
	while (1)
	{
		if (merge())
		{
			++t;
			if (!mov()) break;
		}
		else
		{
			int k = 1;
			for (int i = 2; i <= n; ++i)
			if (s[i][h[i]].l < s[k][h[k]].l)
				k = i;
			++h[k];
			if (h[k] > p) break;
		}
	}
	printf("%d\n", t);
}



int main()
{
	//freopen("b.in", "r", stdin);
	int tt;
	scanf("%d", &tt);
	for (int ii = 1; ii <= tt; ++ii)
	{
		init();
		printf("Case #%d: ", ii);
		solve();
	}
	return 0;
}

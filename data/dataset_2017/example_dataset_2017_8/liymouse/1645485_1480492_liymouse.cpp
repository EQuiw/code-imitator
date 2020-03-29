#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <numeric>
#include <cstring>

typedef long long i64d;

using namespace std;

double res;
int lastcar;
int lr[55];
int s[55];
double p[55];

double pt[55];
int n;

void find(double t)
{
	if (res < 0) return;
	double time = 1e10;
	for (int i = 0; i < n; i ++)
	{
		double ti = 1e10;
		for (int j = 0; j < n; j ++)
			if (lr[i] == lr[j] && s[i] > s[j] && p[i] <= p[j]-5)
			{
				ti = min(ti , (p[j]-p[i]-5) / (s[i]-s[j]));
			}
		time = min(ti , time);
	}
	if (fabs(time - 1e10) <= 1e-9) {res = -1; return;}
	if (time > 1e-9) lastcar = -1;
	for (int i = 0; i < n; i ++)
	{
		p[i] += s[i] * time;
	}
	int x = -1, y;
	for (int i = 0; i < n; i ++)
	{
		for (int j = 0; j < n; j ++)
			if (lr[i] == lr[j] && s[i] > s[j] && fabs(p[i] - p[j] + 5) <= 1e-9)
			{
				x = i; y = j;
				break;
			}
		if (x != -1) break;
	}
	int ok = 1;
	for (int i = 0; i < n; i ++)
		if (i != x && lr[i] != lr[x] && fabs(p[i] - p[x]) < 5.0) {ok = 0; break;}
	if (ok && x != lastcar)
	{
		lr[x] = 1-lr[x];
		lastcar = x;
		memcpy(pt , p , sizeof(p));
		find(t + time);
		memcpy(p , pt , sizeof(p));
		if (res < 0) return;
		lr[x] = 1-lr[x];
	}
	ok = 1;
	for (int i = 0; i < n; i ++)
		if (i != y && lr[i] != lr[y] && fabs(p[i] - p[y]) < 5.0) {ok = 0; break;}
	if (ok && y != lastcar)
	{
		lr[y] = 1-lr[y];
		lastcar = y;
		memcpy(pt , p , sizeof(p));
		find(t + time);
		memcpy(p , pt , sizeof(p));
		if (res < 0) return;
		lr[y] = 1-lr[y];
	}
	res = max(res , t + time);
}

int main()
{
	freopen("C-small-attempt1.in" , "r" , stdin);
	//freopen("input.txt" , "r" , stdin);
	freopen("C-small-attempt1.out" , "w" , stdout);
	int cas;
	scanf("%d" , &cas);
	for (int ca = 1; ca <= cas; ca ++)
	{
		printf("Case #%d: " , ca);
		scanf("%d" , &n);
		for (int i = 0; i < n; i ++)
		{
			char tmp[10];
			int x;
			scanf("%s %d %d" , tmp , &s[i] , &x);
			lr[i] = (tmp[0] == 'R') ? 1 : 0;
			p[i] = x;
		}
		res = 0;
		lastcar = -1;
		find(0);
		if (res == -1) printf("Possiable\n");
		else printf("%lf\n" , res);
	}
	return 0;
}
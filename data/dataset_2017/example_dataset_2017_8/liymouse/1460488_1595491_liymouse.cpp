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

int main()
{
	freopen("B-small-attempt0.in" , "r" , stdin);
	//freopen("input.txt" , "r" , stdin);
	freopen("B-small-attempt0.out" , "w" , stdout);
	int cas;
	scanf("%d" , &cas);
	for (int ca = 1; ca <= cas; ca ++)
	{
		printf("Case #%d: " , ca);
		int n , s , p , im = 0;
		int a[120] = {0};
		int su[120] , nsu[120];
		scanf("%d %d %d" , &n , &s , &p);
		for (int i = 0; i < n; i ++) scanf("%d" , &a[i]);
		sort(a , a + n);
		for (int i = 0; i < n; i ++)
		{
			if (a[i] > 1 && a[i] < 29) su[i] = (a[i]+4)/3;
			else {su[i] = -1; im ++;}
			nsu[i] = (a[i] + 2) / 3;
		}
		int res = 0;
		for (int i = n-1; i >= 0; i --)
		{
			if (a[i] > 28 || a[i] < 2)
			{
				if (nsu[i] >= p) res ++;
			}
			else
			{
				if (nsu[i] >= p) res ++;
				else if (su[i] >= p && s > 0) {res ++; s --;}
			}
		}
		printf("%d\n" , res);
	}
	return 0;
}
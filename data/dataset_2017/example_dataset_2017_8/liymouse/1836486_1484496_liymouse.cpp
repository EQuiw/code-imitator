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

char check[2000010] = {0};
int pre[2000010];

int main()
{
	freopen("C-small-attempt0.in" , "r" , stdin);
	//freopen("input.txt" , "r" , stdin);
	freopen("C-small-attempt0.out" , "w" , stdout);
	int cas;
	scanf("%d" , &cas);
	for (int ca = 1; ca <= cas; ca ++)
	{
		printf("Case #%d:\n" , ca);
		int n;
		scanf("%d" , &n);
		int a[510];
		i64d sum = 0;
		for (int i = 0; i < n; i ++) {scanf("%d" , &a[i]); sum += a[i];}
		memset(check , 0 , sizeof(check));
		check[0] = 1;
		pre[0] = -1;
		vector<int> x , y;
		int ok = 0;
		for (int i = 0; i < n; i ++)
		{
			for (int j = sum; j >= 0; j --)
				if (check[j] > 0)
				{
					int k = j + a[i];
					if (check[k] == 1)
					{
						int t = j;
						x.push_back(a[i]);
						while (pre[t] != -1)
						{
							x.push_back(pre[t]);
							t -= pre[t];
						}
						t = k;
						while (pre[t] != -1)
						{
							y.push_back(pre[t]);
							t -= pre[t];
						}
						ok = 1; break;
					}
					check[k] = 1; pre[k] = a[i];
				}
			if (ok) break;
		}
		if (ok == 0) printf("Impossible\n");
		else
		{
			memset(check , 0 , sizeof(check));
			sort(x.begin() , x.end());
			sort(y.begin() , y.end());
			for (int i = 0; i < x.size(); i ++) check[x[i]] ++;
			for (int j = 0; j < y.size(); j ++) check[y[j]] ++;
			vector<int> xx , yy;
			for (int i = 0; i < x.size(); i ++)
				if (check[x[i]] == 1) xx.push_back(x[i]);
			for (int i = 0; i < y.size(); i ++)
				if (check[y[i]] == 1) yy.push_back(y[i]);
			printf("%d" , xx[0]);
			for (int i = 1; i < xx.size(); i ++) printf(" %d" , xx[i]);
			printf("\n");
			printf("%d" , yy[0]);
			for (int i = 1; i < yy.size(); i ++) printf(" %d" , yy[i]);
			printf("\n");
		}
	}
	return 0;
}
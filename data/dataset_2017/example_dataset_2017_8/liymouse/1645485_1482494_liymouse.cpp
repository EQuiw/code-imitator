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

int cmp(pair<int , int> x , pair<int , int> y)
{
	if (x.second == y.second) return x.first < y.first;
	return x.second < y.second;
}

int main()
{
	freopen("B-small-attempt1.in" , "r" , stdin);
	//freopen("input.txt" , "r" , stdin);
	freopen("B-small-attempt1.out" , "w" , stdout);
	int cas;
	scanf("%d" , &cas);
	for (int ca = 1; ca <= cas; ca ++)
	{
		printf("Case #%d: " , ca);
		int n;
		vector<pair<int , int> > a;
		int b[1005] = {0};
		int tot = 0;
		int res = 0;
		scanf("%d" , &n);
		for (int i = 0; i < n; i ++)
		{
			int x , y;
			scanf("%d %d" , &x , &y);
			a.push_back(make_pair(x , y));
		}
		sort(a.begin() , a.end() , cmp);
		int r = a[0].second;
		int k = 0;
		while (1)
		{
			if (tot >= r)
			{
				if (b[k] == 0) tot += 2;
				else tot ++;
				b[k] = 2;
				res ++;
				while (k < n && b[k] == 2) k ++;
				if (k == n) break;
				r = a[k].second;
			}
			else
			{
				int have = 0;
				for (int i = n-1; i >= 0; i --)
					if (b[i] == 0 && tot >= a[i].first)
					{
						tot ++;
						b[i] = 1;
						res ++;
						have = 1;
						break;
					}
				if (have == 0) {res = -1; break;}
			}
		}
		if (res == -1) printf("Too Bad\n");
		else printf("%d\n" , res);
	}
	return 0;
}
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
	freopen("D-small-attempt2.in" , "r" , stdin);
	//freopen("input.txt" , "r" , stdin);
	freopen("D-small-attempt2.out" , "w" , stdout);
	int cas;
	scanf("%d" , &cas);
	for (int ca = 1; ca <= cas; ca ++)
	{
		printf("Case #%d: " , ca);
		int h , w , d;
		scanf("%d %d %d" , &h , &w , &d);
		char s[100];
		int x , y , xx[20000] , yy[20000];
		int b[20000] = {0};
		for (int i = 0; i < h; i ++)
		{
			scanf("%s" , s);
			for (int j = 0; j < w; j ++)
				if (s[j] == 'X') {x = 2*i-1; y = 2*j-1;}
		}
		h -= 2; w -= 2;
		h *= 2; w *= 2; d *= 2;
		int exh = (d / h + 1);
		int exw = (d / w + 1);
		int num = 0;
		for (int i = -exh; i <= exh; i ++)
			for (int j = -exw; j <= exw; j ++)
				if (i != 0 || j != 0)
				{
					int xt = i * h + ((abs(i)%2 == 1)?(h-x):x);
					int yt = j * w + ((abs(j)%2 == 1)?(w-y):y);
					if ((xt-x)*(xt-x) + (yt-y)*(yt-y) <= d*d)
					{
						xx[num] = xt;
						yy[num] = yt;
						num ++;
					}
				}
		int res = num;
		for (int i = 0; i < num; i ++)
			if (b[i] == 0)
			for (int j = i+1; j < num; j ++)
			if (b[j] == 0)
			{
				int x1 , y1 , x2 , y2;
				x1 = xx[i] - x;
				y1 = yy[i] - y;
				x2 = xx[j] - x;
				y2 = yy[j] - y;
				if (x1 * y2 - x2 * y1 == 0 && x1*x2 + y1*y2 > 0)
				{
					res --;
					if (x1*x1 + y1*y1 < x2*x2 + y2*y2) b[j] = 1;
					else {b[i] = 1; break;}
				}
			}
		printf("%d\n" , res);
	}
	return 0;
}
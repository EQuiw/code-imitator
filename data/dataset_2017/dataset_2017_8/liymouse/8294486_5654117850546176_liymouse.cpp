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
	freopen("B-small-attempt1.in" , "r" , stdin);
	freopen("B-small-attempt1.out" , "w" , stdout);
	//freopen("input.txt" , "r" , stdin);
	//freopen("output.txt" , "w" , stdout);
	int cas;
	scanf("%d" , &cas);
	for (int ca = 1; ca <= cas; ca ++)
	{
		printf("Case #%d: " , ca);
        int n;
        int r , o , y , g , b , v;
        scanf("%d %d %d %d %d %d %d" , &n , &r , &o , &y , &g , &b , &v);
        char s[1010] = {0};
        if (r > n/2 || y > n/2 || b > n/2)
        {
            printf("IMPOSSIBLE\n");
        }
        else
        {
            int num[3] = {r , y , b};
            char c[4] = "RYB";

            if (y > r && y > b)
            {
                num[0] = y; num[1] = r;
                c[0] = 'Y'; c[1] = 'R';
            }
            if (b > r && b > y)
            {
                num[0] = b; num[2] = r;
                c[0] = 'B'; c[2] = 'R';
            }

            int i = 0;
            if (num[0] > 0)
            {
                while (i < n)
                {
                    s[i] = c[0];
                    i += 2;
                    num[0] --;
                    if (num[0] == 0) break;
                }
            }
            if (num[1] > 0)
            {
                while (i < n)
                {
                    s[i] = c[1];
                    i += 2;
                    num[1] --;
                    if (num[1] == 0) break;
                }
                if (num[1] > 0)
                {
                    i = 1;
                    while (i < n)
                    {
                        s[i] = c[1];
                        i += 2;
                        num[1] --;
                        if (num[1] == 0) break;
                    }
                }
            }
            if (num[2] > 0)
            {
                for (i = 0; i < n; i ++)
                    if (s[i] == 0) s[i] = c[2];
            }
            printf("%s\n" , s);
        }
    }
    return 0;
}
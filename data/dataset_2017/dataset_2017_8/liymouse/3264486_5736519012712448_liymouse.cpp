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
	freopen("A-small-attempt0.in" , "r" , stdin);
	freopen("A-small-attempt0.out" , "w" , stdout);
	int cas;
	scanf("%d" , &cas);
	for (int ca = 1; ca <= cas; ca ++)
	{
		printf("Case #%d: " , ca);
        char s[2000] = {0};
        int k;
        scanf("%s %d" , s , &k);
        int L = strlen(s);
        int num = 0;
        for (int i = 0; i <= L - k; i ++)
            if (s[i] == '-')
            {
                for (int j = 0; j < k; j ++)
                    if (s[i+j] == '-') s[i+j] = '+';
                    else s[i+j] = '-';
                num ++;
            }
        for (int i = L-k; i < L; i ++)
            if (s[i] == '-') num = -1;
        if (num == -1) printf("IMPOSSIBLE\n");
        else printf("%d\n" , num);
    }
    return 0;
}
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
#define N 20 + 5

int Case, q[N];
char s[N];

bool dfs(int dep, bool op, int last)
{
	if (!dep) return 1;
	int top = op ? q[dep] : 9;
	for (int i = top; i >= last; i --)
		if (dfs(dep - 1, op & (i == top), i))
		{
			q[dep] = i;
			return 1;
		}
	return 0;
}

int main()
{
	scanf("%d", &Case);
	for (int T = 1; T <= Case; T ++)
	{
		printf("Case #%d: ", T);
		scanf("%s", s);
		q[0] = strlen(s);
		for (int i = 1; i <= q[0]; i ++)
			q[i] = s[q[0] - i] - '0';
		dfs(q[0], 1, 0);
		for (; !q[q[0]]; q[0] --) ;
		for (int i = q[0]; i; i --)
			printf("%d", q[i]);
		puts("");
	}
	return 0;
}

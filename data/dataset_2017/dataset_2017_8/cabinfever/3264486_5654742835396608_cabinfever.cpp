#include <bits/stdc++.h>

using namespace std;

priority_queue<int>q;
int n,k,x,y;
int T;

int main()
{
	freopen("cs.in","r",stdin);
	freopen("cs.out","w",stdout);
	cin >> T;
	for(int ii = 1; ii <= T; ii++)
	{
		cin >> n >> k;
		while(!q.empty())
			q.pop();
		q.push(n);
		for(int i = 0; i < k; i++)
		{
			int now = q.top();
			q.pop();
			x = now / 2;
			y = (now - 1) / 2;
			q.push(x);
			q.push(y);
		}
		printf("Case #%d: ",ii);
		printf("%d %d\n",x,y);
	}
	return 0;
}


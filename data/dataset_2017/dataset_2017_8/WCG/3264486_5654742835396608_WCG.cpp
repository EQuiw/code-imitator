#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <queue>
#include <map>
using namespace std;

int main()
{
	int tt;
	
	cin >> tt;
	
	for (int t = 1; t <= tt; ++t)
	{
		long long n, k, y, z;
		map<long long, long long> m;
		queue<long long> q;
		cin >> n >> k;
		
		q.push(n);
		m[n] = 1;
		
		while (k > 0)
		{
			long long c = q.front();
			q.pop();
			y = c / 2;
			z = (c - 1) / 2;
			k -= m[c];
			if (m.find(y) == m.end())
				q.push(y);
			m[y] += m[c];
			if (m.find(z) == m.end())
				q.push(z);
			m[z] += m[c];
		}
				
		cout << "Case #" << t << ": " << y << " " << z << endl;
	}

    return 0;
}

#include <bits/stdc++.h>
using namespace std;
int main()
{
	map <char,char> opposite;
	opposite['+'] = '-';
	opposite['-'] = '+';
	int t;
	cin>>t;
	for (int case_num = 1; case_num <= t; ++case_num)
	{
		string s;
		int k;
		cin>>s>>k;
		queue <int> q;
		int ans = 0;
		bool flag = true;
		for (int i = 0; i <= s.length(); ++i)
		{
			while(!q.empty() && q.front() <= i - k)
				q.pop();
			int flips = q.size()%2;
			if(flips)
				s[i] = opposite[s[i]];
			if(s[i] == '-')
			{
				if(i + k <= s.length())
				{
					q.push(i);
					ans++;
				}
				else
					flag = false;
			}
		}
		if(flag)
			cout<<"Case #"<<case_num<<": "<<ans<<"\n";
		else
			cout<<"Case #"<<case_num<<": IMPOSSIBLE\n";
	}
	return 0;
}
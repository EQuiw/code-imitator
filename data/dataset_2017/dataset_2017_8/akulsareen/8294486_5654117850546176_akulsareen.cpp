#include <bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	for (int case_num = 1; case_num <= t; ++case_num)
	{
		int n,r,o,y,g,b,v;
		cin>>n>>r>>o>>y>>g>>b>>v;
		// TODO: edge cases for large case
		vector < pair<int,char> > A;
		A.push_back(make_pair(r,'R'));
		A.push_back(make_pair(y,'Y'));
		A.push_back(make_pair(b,'B'));
		sort(A.begin(), A.end());
		vector <char> ans;
		for (int i = 0; i < 3; ++i)
		{
			vector <char> temp;
			int ctr = A[i].first;
			while(ctr || !ans.empty())
			{
				if(ctr)
				{
					ctr--;
					temp.push_back(A[i].second);
				}
				if(!ans.empty())
				{
					temp.push_back(ans.back());
					ans.pop_back();
				}
			}
			ans = temp;
		}
		bool exists = true;
		for (int i = 0; i < ans.size(); ++i)
		{
			if(ans[i] == ans[(i+1)%ans.size()])
				exists = false;
		}
		cout<<"Case #"<<case_num<<": ";
		if(!exists)
		{
			cout<<"IMPOSSIBLE\n";
		}
		else
		{
			for (int i = 0; i < ans.size(); ++i)
			{
				cout<<ans[i];
			}
			cout<<"\n";
		}
	}
	return 0;
}
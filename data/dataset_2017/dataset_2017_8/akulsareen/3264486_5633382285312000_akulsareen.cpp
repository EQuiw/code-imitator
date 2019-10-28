#include <bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	for (int case_num = 1; case_num <= t; ++case_num)
	{
		string num;
		cin>>num;
		string ans = "";
		for (int i = 0; i < num.length(); ++i)
		{
			for (char digit = '9'; digit >= '0'; --digit)
			{
				string temp = "";
				for (int j = i; j < num.length(); ++j)
					temp+=digit;
				temp = ans + temp;
				if(temp <= num)
				{
					ans+=digit;
					break;
				}
			}
		}
		bool printed = false;
		cout<<"Case #"<<case_num<<": ";
		for (int i = 0; i < ans.length(); ++i)
		{
			if(printed || ans[i] != '0')
			{
				printed = true;
				cout<<ans[i];
			}
		}
		cout<<"\n";
		assert(printed);
	}
	return 0;
}
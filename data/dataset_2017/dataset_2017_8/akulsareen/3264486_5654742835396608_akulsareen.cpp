#include <bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	for (int case_num = 1; case_num <= t; ++case_num)
	{
		long long int n,k;
		cin>>n>>k;
		k--;
		map <long long int,long long int> M;
		M[n] = 1;
		while(true)
		{
			long long int len = M.rbegin()->first;
			long long int ctr = M.rbegin()->second;
			if(k >= ctr)
			{
				k-=ctr;
				M.erase(len);
				M[len/2]+=ctr;
				M[(len - 1)/2]+=ctr;
			}
			else
			{
				M[len]-=k;
				k = 0;
				break;
			}
		}
		long long int ans_len = M.rbegin()->first;
		cout<<"Case #"<<case_num<<": "<<ans_len/2<<" "<<(ans_len - 1)/2<<"\n";
	}
	return 0;
}
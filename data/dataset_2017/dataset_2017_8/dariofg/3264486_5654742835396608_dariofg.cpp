#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int main()
{
	int T;
	cin >> T;
	for(int I=1;I<=T;I++)
	{
		cout << "Case #" << I << ": ";
		int n,k;
		cin >> n >> k;/*
		vector<int> distiz(n+2);
		vector<int> distder(n+2);
		distiz[0] = distiz[n+1] = distder[0] = distder[n+1] = 0;
		for(int i=1;i<=n;i++)
			distiz[i] = i-1,distder[i]=n-i;
		int mn,mx;
		for(int ii=0;ii<k;ii++)
		{
			vector<pair<pair<int,int>,int> > v;
			pair<pair<int,int>,int> pp;
			pair<int,int> p;
			for(int i=1;i<=n;i++)
			{
				pp.first.first=min(distiz[i],distder[i]);
				pp.first.second=max(distiz[i],distder[i]);
				pp.second = i;
				v.push_back(pp);
			}
			sort(v.begin(),v.end());
			mn = v[0].first.first;
			mx = v[0].first.second;
			int pos = v[0].second;
			distiz[pos] = distder[pos] = 0;
			distiz[pos+1] = 0;
			distder[pos-1] = 0;
		}
		cout << mx << " " << mn << endl;*/
		priority_queue<int> pq;
		pq.push(n);
		int mn,mx;
		for(int i=0;i<k;i++)
		{
			n = pq.top();
			pq.pop();
			int a = (n-1)/2;
			int b = n-a-1;
			mn = min(a,b);
			mx = max(a,b);
			pq.push(a);
			pq.push(b);
		}
		cout << mx << " " << mn << endl;
	}
}

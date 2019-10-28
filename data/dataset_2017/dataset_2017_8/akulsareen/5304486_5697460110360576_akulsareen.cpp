#include <bits/stdc++.h>
using namespace std;
const int MAXN = 55;
int req[MAXN], avbl_ctr[MAXN];
bool avbl[MAXN][MAXN];
struct Event
{
	int t, type, x, y;
	Event(int t, int type, int x, int y)
	{
		this->t = t;
		this->type = type;
		this->x = x;
		this->y = y;
	}
};
bool sorter(const Event &a, const Event &b)
{
	return make_pair(a.t,a.type) < make_pair(b.t,b.type);
}
void inc_ctr(int &ctr, int &non_zero)
{
	ctr++;
	if(ctr == 1)
		non_zero++;
}
void dec_ctr(int &ctr, int &non_zero)
{
	ctr--;
	if(ctr == 0)
		non_zero--;
}
int main()
{
	int t;
	cin>>t;
	for (int case_num = 1; case_num <= t; ++case_num)
	{
		int n,p;
		cin>>n>>p;
		for (int i = 0; i < n; ++i)
		{
			cin>>req[i];
		}
		vector <Event> events;
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < p; ++j)
			{
				int quan;
				cin>>quan;
				quan*=10;
				int r = (quan)/(9*req[i]);
				int l = max(1, (quan + (11*req[i] - 1))/(11*req[i]));
				if(l <= r)
				{
					Event x(l,-1,i,j);
					Event y(r,1,i,j);
					events.push_back(x);
					events.push_back(y);
				}
			}
		}
		sort(events.begin(), events.end(), sorter);
		memset(avbl, false, sizeof avbl);
		memset(avbl_ctr, 0, sizeof avbl_ctr);
		int ans = 0, non_zero = 0;
		for (int i = 0; i < events.size(); ++i)
		{
			Event curr = events[i];
			if(curr.type == -1)
			{
				// opening
				avbl[curr.x][curr.y] = true;
				inc_ctr(avbl_ctr[curr.x], non_zero);
				if(non_zero == n)
				{
					// make a kit
					ans++;
					for (int ii = 0; ii < n; ++ii)
					{
						for (int jj = 0; jj < p; ++jj)
						{
							if(avbl[ii][jj])
							{
								avbl[ii][jj] = false;
								dec_ctr(avbl_ctr[ii], non_zero);
								break;
							}
						}
					}
				}
			}
			else
			{
				// closing
				if(avbl[curr.x][curr.y])
				{
					avbl[curr.x][curr.y] = false;
					dec_ctr(avbl_ctr[curr.x], non_zero);
				}
			}
		}
		cout<<"Case #"<<case_num<<": "<<ans<<"\n";
	}
	return 0;
}
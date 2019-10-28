// Ratatouille.cpp : Defines the entry point for the console application.
//

#include <vector>
#include <iostream>
#include <algorithm>
#define MAX_N 52
using namespace std;

int  ingredients[MAX_N];
int pointers[MAX_N];
vector<int > segments[MAX_N];

int solve(int n)
{
	int res = 0;
	for (int i = 0; i <= n; ++i)
		pointers[i] = 0;
	for (int i = 1;; i++)
	{
		for(int j=0;j<n;++j)
		while (pointers[j] < segments[j].size() && ingredients[j] * i * 9 > segments[j][pointers[j]] * 10)pointers[j]++;
		bool good = true;
		for (int j = 0; j < n; ++j)
		{
			if (pointers[j] >= segments[j].size())
			{
				return res;
			}
			if (!(ingredients[j] * i * 11 >= segments[j][pointers[j]] * 10 && ingredients[j] * i * 9 <= segments[j][pointers[j]] * 10))good = false;
		}
		if (good)
		{
			i--;
			res++;
			for (int j = 0; j < n; ++j)
				pointers[j]++;
		}
	}
	return res;
}
int main()
{
	int ts,n,p,tmp;
	cin >> ts;
	for (int t = 1; t <= ts; ++t)
	{
		cin >> n >> p;
		for (int i = 0; i < n; ++i) {
			cin >> ingredients[i];
			segments[i].clear();
		}
		for(int i=0;i<n;++i)
			for (int j = 0; j < p; ++j)
			{
				int a, b;
				cin >> tmp;
				segments[i].push_back(tmp);
			}
		for (int i = 0; i < n; ++i)
			sort(segments[i].begin(), segments[i].end());
		cout << "Case #" << t << ": "<<solve(n)<< "\n";
	}
    return 0;
}


#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cstring>
#include <cstdio>
using namespace std;

char ch[30][30];
int r, c;

void fill(char cc, int x, int y, int dx, int dy)
{
	while ((x + dx >= 0) && (x + dx < r) && (y + dy >= 0) && (y + dy < c) && (ch[x+dx][y+dy] == '?'))
	{
		x += dx;
		y += dy;
		ch[x][y] = cc;
	}
}

int main()
{
	int tt;
	
	cin >> tt;
	
	for (int t = 1; t <= tt; ++t)
	{
		cin >> r >> c;
		for (int i = 0; i < r; ++i)
			for (int j = 0; j < c; ++j)
				cin >> ch[i][j];
		
		for (int i = 0; i < r; ++i)
			for (int j = 0; j < c; ++j)
				if (ch[i][j] != '?')
				{
					fill(ch[i][j], i, j, -1, 0);
					fill(ch[i][j], i, j, 1, 0);
				}
		for (int i = 0; i < r; ++i)
			for (int j = 0; j < c; ++j)
				if (ch[i][j] != '?')
				{
					fill(ch[i][j], i, j, 0, 1);
					fill(ch[i][j], i, j, 0, -1);
				}
		
		cout << "Case #" << t << ": " << endl;
		for (int i = 0; i < r; ++i)
		{
			for (int j = 0; j < c; ++j)
				cout << ch[i][j];
			cout << endl;
		}
	}

    return 0;
}

// Alphabet Cake.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#define MAX_N 30
using namespace std;
char tab[MAX_N][MAX_N];
void fill(int r,int c)
{
	char last = '?';
	for (int i = 0; i < r; ++i)
	{
		last = '?';
		for (int j = 0; j < c; ++j)
		{

			if (tab[i][j] != '?')
			{
				last = tab[i][j];
				char c = tab[i][j];
				int poz = j - 1;
				while (poz >= 0 && tab[i][poz] == '?') {
					tab[i][poz] = c;
					poz--;
				}
			}
			if (tab[i][j] == '?' && last != '?')
			{
				tab[i][j] = last;
			}
			
		}
		
	}
	
	
	for (int i = 0; i < c; ++i)
	{
		last = '?';
		for (int j = 0; j < r; ++j)
		{
			if (tab[j][i] != '?')
			{
				last = tab[j][i];
				char c = tab[j][i];
				int poz = j - 1;
				while (poz >= 0 && tab[poz][i] == '?') {
					tab[poz][i] = c;
					poz--;
				}
			}
			if (tab[j][i] == '?' && last != '?')
				tab[j][i] = last;

		}
	}

}
int main()
{
	int t,r,w;
	cin >> t;
	for (int i = 1; i <= t; ++i)
	{
		string s;
		cin >> r >> w;
		for (int j = 0; j < r; ++j)
		{
			cin >> s;
			for (int k = 0; k < w; ++k)
				tab[j][k] = s[k];
		//	cout << s << "\n";

		}
		fill(r,w);
		cout << "Case #" << i << ":\n";
		for (int j = 0; j < r; ++j)
		{
			for (int k = 0; k < w; ++k)
				cout << tab[j][k];
			cout << "\n";
		}
	}
    return 0;
}


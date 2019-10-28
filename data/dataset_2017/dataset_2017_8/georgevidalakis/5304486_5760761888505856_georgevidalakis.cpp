#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	ifstream fin("data.in");
	ofstream fout("data.out");
	unsigned int T;
	fin >> T;
	for (unsigned int x = 1; x <= T; x++)
	{
		fout << "Case #" << x << ":\n";
		unsigned int R, C;
		fin >> R >> C;
		string G[25];
		for (unsigned int i = 0; i < R; i++) fin >> G[i];
		bool HL[25];
		char FL[25];
		for (unsigned int i = 0; i < R; i++)
		{
			HL[i] = false;
			for (unsigned int j = 0; j < C; j++)
			{
				if (!HL[i] && G[i][j] != '?')
				{
					HL[i] = true;
					FL[i] = G[i][j];
				}
			}
		}
		for (unsigned int i = 0; i < R; i++)
		{
			if (HL[i])
			{
				char cl = FL[i];
				for (unsigned int j = 0; j < C; j++)
				{
					if (G[i][j] != '?') cl = G[i][j];
					G[i][j] = cl;
				}
			}
		}
		unsigned int flwl;
		for (flwl = 0; flwl < R; flwl++) if (HL[flwl]) break;
		for (unsigned int i = 0; i < flwl; i++) for (unsigned int j = 0; j < C; j++) G[i][j] = G[flwl][j];
		for (unsigned int i = flwl + 1; i < R; i++) if (!HL[i]) for (unsigned int j = 0; j < C; j++) G[i][j] = G[i - 1][j];
		for (unsigned int i = 0; i < R; i++)
		{
			for (unsigned int j = 0; j < C; j++) fout << G[i][j];
			fout << "\n";
		}
	}
	fin.close();
	fout.close();
	return(0);
}
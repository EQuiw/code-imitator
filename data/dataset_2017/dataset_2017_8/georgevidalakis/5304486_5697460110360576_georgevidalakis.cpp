#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	ifstream fin("data.in");
	ofstream fout("data.out");
	unsigned int T;
	fin >> T;
	vector<vector<unsigned int>> MIN;
	vector<unsigned int> tmpMIN;
	for (unsigned int i = 0; i < 50; i++) tmpMIN.push_back(0);
	for (unsigned int i = 0; i < 50; i++) MIN.push_back(tmpMIN);
	vector<vector<unsigned int>> MAX;
	vector<unsigned int> tmpMAX;
	for (unsigned int i = 0; i < 50; i++) tmpMAX.push_back(0);
	for (unsigned int i = 0; i < 50; i++) MAX.push_back(tmpMAX);
	for (unsigned int x = 1; x <= T; x++)
	{
		fout << "Case #" << x << ": ";
		unsigned int N, P, R[50];
		fin >> N >> P;
		for (unsigned int i = 0; i < N; i++) fin >> R[i];
		vector<vector<unsigned int>> Q;
		for (unsigned int i = 0; i < N; i++)
		{
			vector<unsigned int> tmpQ;
			unsigned int tmp;
			for (unsigned int j = 0; j < P; j++)
			{
				fin >> tmp;
				tmpQ.push_back(tmp);
			}
			sort(tmpQ.begin(), tmpQ.end());
			Q.push_back(tmpQ);
		}
		for (unsigned int i = 0; i < N; i++) sort(Q[i].begin(), Q[i].end());
		unsigned int y = 0, cp[50];
		for (unsigned int i = 0; i < N; i++) cp[i] = 0;
		for (unsigned int i = 0; i < N; i++) for (unsigned int j = 0; j < P; j++)
		{
			MIN[i][j] = Q[i][j] / (1.1 * R[i]);
			if (MIN[i][j] * 1.1 * R[i] < Q[i][j]) MIN[i][j]++;
			MAX[i][j] = Q[i][j] / (0.9 * R[i]);
			if (MAX[i][j] * 0.9 * R[i] > Q[i][j]) MAX[i][j]--;
		}
		bool done = false;
		unsigned int max = 0;
		while (!done)
		{
			bool moved;
			do
			{
				moved = false;
				for (unsigned int i = 0; i < N; i++) if (MIN[i][cp[i]] > max) max = MIN[i][cp[i]];
				for (unsigned int i = 0; i < N; i++) while (cp[i] < P && MAX[i][cp[i]] < max) { cp[i]++; moved = true; }
				for (unsigned int i = 0; i < N; i++) done = done || cp[i] == P;
				if (done) break;
			} while (moved);
			if (done) break;
			for (unsigned int i = 0; i < N; i++) cp[i]++;
			y++;
			for (unsigned int i = 0; i < N; i++) done = done || cp[i] == P;
		}
		fout << y << "\n";
	}
	fin.close();
	fout.close();
	return(0);
}
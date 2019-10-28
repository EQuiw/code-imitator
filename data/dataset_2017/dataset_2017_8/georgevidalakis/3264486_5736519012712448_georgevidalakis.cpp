#include <iostream>
#include <string>
#include <fstream>
#include <queue>
using namespace std;

int main()
{
	ifstream fin("data.in");
	ofstream fout("data.out");
	unsigned int T;
	int r;
	fin >> T;
	for (unsigned int x = 1; x <= T; x++)
	{
		fout << "Case #" << x << ": ";
		r = 0;
		string S;
		unsigned int K;
		fin >> S >> K;
		queue<int> F;
		bool f = false;
		for (unsigned int j = 0; j <= S.length() - K; j++)
		{
			if (!F.empty() && F.front() == j)
			{
				f = !f;
				F.pop();
			}
			if ((S[j] == '+' && f) || (S[j] == '-' && !f))
			{
				r++;
				F.push(j + K);
				f = !f;
			}
		}
		for (unsigned int j = S.length() - K + 1; j < S.length(); j++)
		{
			if (!F.empty() && F.front() == j)
			{
				f = !f;
				F.pop();
			}
			if ((S[j] == '+' && f) || (S[j] == '-' && !f))
			{
				r = -1;
				break;
			}
		}
		if (r == -1) fout << "IMPOSSIBLE\n";
		else fout << r << "\n";
	}
	fin.close();
	fout.close();
	return(0);
}
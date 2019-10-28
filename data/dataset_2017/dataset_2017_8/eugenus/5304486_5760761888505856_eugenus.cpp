#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <queue>
#include <map>
#include <string>
#include <vector>
#include <cstring>
#include <set>

#define forn(i,n) for(int i = 0; i < (n); i++)
#define forsn(i,s,n) for(int i = (s); i < (n); i++)
#define all(v) ((v).begin, (v).end)
#define pb push_back
#define x first
#define y second
#define mp make_pair

using namespace std;

typedef pair<int,int> par;
typedef long long int tint;

string cake[50];

int main()
{
	freopen("test.txt","r",stdin);
	freopen("out.txt","w",stdout);

	int t; cin >> t;
	int r,c;
	
	forsn(caso, 1, t+1)
	{
		cin >> r >> c;

		bool in[50];
		int mh[50], mah[50], ml[50], mal[50];

		forn(i,50)
		{
			mh[i] = 100; ml[i] = 100; in[i] = false;
			mah[i] = 0; mal[i] = 0;
		}
		//cout << "init" << endl;

		forn(i,r) cin >> cake[i];

		int co = 0;

		for(char l = 'A'; l <= 'Z'; l++)
		{
			forn(i,r)
			{
				forn(j,c)
				{
					if(cake[i][j] == l)
					{
						in[co] = true;
						mh[co] = min(mh[co], i);
						mah[co] = max(mh[co], i);
						ml[co] = min(ml[co], j);
						mal[co] = max(mal[co], j);
					}
				}
			}
			co++;
		}

		forn(i, 40)
		{
			if(in[i])
			{
				char l = (char)('A' + i);
				for(int a = mh[i]; a <= mah[i]; a++)
				{
					for(int b = ml[i]; b <= mal[i]; b++)
					{
						cake[a][b] = l;
					}
				}
			}
		}
		// horizontal
		forn(i, 40)
		{
			if(in[i])
			{
				char l = (char)('A' + i);
				//cout << l << endl;
				int mml = ml[i]; int mmal = mal[i];

				forsn(k, mal[i]+1, c)
				{
					bool ext = true;
					forsn(j, mh[i], mah[i]+1)
					{
						if(cake[j][k] != '?')
						{
							ext = false;
							break;
						}
					}
					if(ext)
					{
						mmal++;
						forsn(j, mh[i], mah[i]+1)
						{
							cake[j][k] = l;
						}
					}
					else break;
				}
				for(int k = ml[i]-1; k >= 0; k--)
				{
					bool ext = true;
					forsn(j, mh[i], mah[i]+1)
					{
						if(cake[j][k] != '?')
						{
							ext = false;
							break;
						}
					}
					if(ext)
					{
						mml--;
						forsn(j, mh[i], mah[i]+1)
						{							
							cake[j][k] = l;
						}
					}
					else break;
				}
				ml[i] = mml; mal[i] = mmal;
				//cout << ml[i] << " " << mal[i] << " " << mh[i] << " " << mah[i] << endl;
			}
		}

		// vertical
		forn(i, 40)
		{
			if(in[i])
			{
				char l = (char)('A' + i);
				int mmh = mh[i]; int mmah = mah[i];
				forsn(k, mah[i]+1, r)
				{
					bool ext = true;
					forsn(j, ml[i], mal[i]+1)
					{
						if(cake[k][j] != '?')
						{
							ext = false;
							break;
						}
					}
					if(ext)
					{
						mmah++;
						forsn(j, ml[i], mal[i]+1)
						{
							cake[k][j] = l;
						}
					}
					else break;
				}
				for(int k = mh[i]-1; k >= 0; k--)
				{
					bool ext = true;
					forsn(j, ml[i], mal[i]+1)
					{
						if(cake[k][j] != '?')
						{
							ext = false;
							break;
						}
					}
					if(ext)
					{
						mmh--;
						forsn(j, ml[i], mal[i]+1)
						{
							cake[k][j] = l;
						}
					}
					else break;
				}
				mh[i] = mmh; mah[i] = mmah;
			}
		}

		cout << "Case #" << caso <<": " << endl;
		forn(i,r) cout << cake[i] << endl;
	}

	return 0;
}
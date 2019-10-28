#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int ancho,alto;

bool ok;

bool valid(const vector<vector<char> >& m)
{
	vector<vector<bool> > vis(alto,vector<bool>(ancho));
	set<char> st;
	for(int i=0;i<alto;i++)
	{
		for(int j=0;j<ancho;j++)
		{
			if(vis[i][j])
				continue;
			char mander = m[i][j];
			if(st.find(mander)!=st.end())
				return false;
			vis[i][j] = true;
			int ii=i;
			while(ii<alto && m[ii][j]==mander)
				vis[ii][j] = true,ii++;
			int jj=j;
			while(jj<ancho && m[i][jj]==mander)
				vis[i][jj] = true,jj++;
			for(int k=i;k<ii;k++)
			{
				for(int l=j;l<jj;l++)
				{
					if(m[k][l]!=mander)
						return false;
					vis[k][l] = true;
				}
			}
			st.insert(mander);
		}
	}
	return true;
}

void rec(vector<vector<char> >& m,const vector<char>& asdf)
{
	if(ok)
		return;
	for(int i=0;i<alto;i++)
	{
		for(int j=0;j<ancho;j++)
		{
			if(m[i][j]=='?')
			{
				for(int k=0;k<asdf.size();k++)
				{
					m[i][j] = asdf[k];
					rec(m,asdf);
				}
				m[i][j]='?';
				return;
			}
		}
	}
	if(valid(m))
	{
		for(int i=0;i<alto;i++)
		{
			for(int j=0;j<ancho;j++)
			{
				cout << m[i][j];
			}
			cout << endl;
		}
		ok = true;
	}
}

int main()
{
	int T;
	cin >> T;
	for(int I=1;I<=T;I++)
	{
		cout << "Case #" << I << ":" << endl;
		cin >> alto >> ancho;
		vector<vector<char> > m(alto,vector<char>(ancho));
		vector<char> aaa;
		set<char> asdf;
		for(int i=0;i<alto;i++)
		{
			for(int j=0;j<ancho;j++)
			{
				cin >> m[i][j];
				if(m[i][j]!='?' && asdf.find(m[i][j])==asdf.end())
					aaa.push_back(m[i][j]);
				asdf.insert(m[i][j]);
			}
		}
		ok=false;
		rec(m,aaa);
	}
}

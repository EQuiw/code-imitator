#include <bits/stdc++.h>

#define PAUSE system("pause")
#define LL long long int
#define LD long double
#define PB push_back
#define PF push_front
#define MP make_pair
#define FORi(i, a, b) for(int i = a; i < b ; ++i)
#define FORd(i, a, b) for(int i = a; i > b ; --i)

using namespace std;

bool comp(pair<int, char>& l, pair<int, char>& r){
	return l.first < r.first;
}

int main(int argc, char **argv)
{
	ifstream fin("/home/roman/CodeliteProjects/Competitive/GCJ17_R1B/in.txt");
	ofstream fout("/home/roman/CodeliteProjects/Competitive/GCJ17_R1B/out.txt");
	
	int t;
	fin >> t;
	FORi(testcase, 0, t){
		int n,r,o,y,g,b,v;
		fin >> n >> r >> o >> y >> g >> b >> v;
		int m = max(r,max(y,b));
		fout << "Case #" << testcase+1 << ": ";
		
		pair<int, char> col[] = {{r,'R'}, {y,'Y'}, {b,'B'}};
		sort(col, &col[3], comp);
		
		if (r+y+b == 1){
			FORi(i,0,3){
				if (col[i].first){
					fout << col[i].second << endl;
				}
			}
			continue;
		}
		
		if (m > (r+y+b)/2.0){
			fout << "IMPOSSIBLE" << endl;
			continue;
		}
		
		while(col[1].first > col[0].first){
			fout << col[2].second << col[1].second;
			col[2].first--;
			col[1].first--;
		}
		int odd = 0;
		while(col[2].first){
			fout << col[2].second << col[odd%2].second;
			col[2].first--;
			col[odd%2].first--;
			odd++;
		}
		while(col[odd%2].first){
			fout << col[odd%2].second;
			col[odd%2].first--;
			odd++;
		}
		fout << endl;
	}
	
	fin.close();
	fout.close();
	return 0;
}

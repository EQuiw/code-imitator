#include <bits/stdc++.h>

#define PAUSE system("pause")
#define LLI long long int
#define LD long double
#define PB push_back
#define PF push_front
#define MP make_pair
#define FORi(i, a, b) for(int i = a; i < b ; ++i)
#define FORd(i, a, b) for(int i = a; i > b ; --i)

using namespace std;

int main(int argc, char **argv)
{
	ifstream fin("/home/roman/CodeliteProjects/Competitive/GCJ17_Quals/in.txt");
	ofstream fout("/home/roman/CodeliteProjects/Competitive/GCJ17_Quals/out.txt");
	
	int t;
	fin >> t;
	FORi(testcase, 0, t){
		string s;
		int k;
		fin >> s >> k;
		int n = s.size();
		
		vector<bool> v;
		FORi(i,0,n){
			v.PB(s[i] == '+');
		}
		
		int cnt = 0;
		FORi(i,0,n-k+1){
			if (!v[i]){
				FORi(j,i,i+k){
					v[j] = !v[j];
				}
				cnt++;
			}
			
//			FORi(j,0,n){
//				cout << v[j];
//			}
//			cout << endl;
		}
		
		FORi(i,n-k,n){
			if (!v[i]){
				cnt = -1;
			}
		}
		
		fout << "Case #" << testcase+1 << ": ";
		if (cnt == -1){
			fout << "IMPOSSIBLE" << endl;
		}
		else {
			fout << cnt << endl;
		}
	}
	
	fin.close();
	fout.close();
	return 0;
}

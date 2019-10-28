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
		int n,q,u,v;
		fin >> n >> q;
		assert(q==1);
		vector<LL> e(n),s(n);
		FORi(i,0,n){
			fin >> e[i] >> s[i];
		}
		vector<vector<LL> > d(n, vector<LL>(n));
		FORi(i,0,n){
			FORi(j,0,n){
				fin >> d[i][j];
			}
		}
		fin >> u >> v;
		
		vector<vector<LL> > dist(n, vector<LL> (n, -1));
		FORi(from,0,n){
			dist[from][from] = 0;
			FORi(to, from+1, n){
				dist[from][to] = dist[from][to-1] + d[to-1][to];
//				cout << from << ' ' << to << ' ' << dist[from][to] << endl;
			}
		}
		
		vector<double> dp(n, 1e18);
		dp[0] = 0;
		FORi(to,1,n){
			FORi(from, 0, to){
				if (dist[from][to] <= e[from]){
					dp[to] = min(dp[to], dp[from] + 1.0 * dist[from][to] / s[from]);
				}
			}
		}
		
		fout << "Case #" << testcase+1 << ": " << fixed << setprecision(7) << dp[n-1] << endl;
	}
	
	fin.close();
	fout.close();
	return 0;
}

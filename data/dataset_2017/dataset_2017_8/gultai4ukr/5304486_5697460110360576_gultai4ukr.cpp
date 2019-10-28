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

int main(int argc, char **argv)
{
	ifstream fin("/home/roman/CodeliteProjects/Competitive/GCJ17_R1A/in.txt");
	ofstream fout("/home/roman/CodeliteProjects/Competitive/GCJ17_R1A/out.txt");
	
	int t;
	fin >> t;
	FORi(testcase, 0, t){
		int n,p;
		fin >> n >> p;
		vector<int> need(n);
		FORi(i,0,n){
			fin >> need[i];
		}
		vector<vector<int> > q(n, vector<int> (p));
		FORi(i,0,n){
			FORi(j,0,p){
				fin >> q[i][j];
			}
		}
		
		assert(n<3);
		int ans = 0;
		if (n==1){
			FORi(i,0,p){
				int k = q[0][i]/need[0];
				long double fr1 = 1.0L*q[0][i]/(k*need[0]);
				if (0.9L<=fr1 && fr1<=1.1L){
					ans++;
					continue;
				}
				long double fr2 = 1.0L*q[0][i]/((k+1)*need[0]);
				if (0.9L<=fr2 && fr2<=1.1L){
					ans++;
				}
			}
		}
		else {
			vector<int> perm(p);
			FORi(i,0,p){
				perm[i] = i;
			}
			do{
				int cur = 0;
				FORi(i,0,p){
					int m1 = q[0][i]/need[0];
					int m2 = q[1][i]/need[1];
					if (m2 < m1){
						swap(m1,m2);
					}
					FORi(k, m1, m2+2){
						long double fr01 = 1.0L*q[0][i]/(k*need[0]);
						long double fr11 = 1.0L*q[1][perm[i]]/(k*need[1]);
						long double fr02 = 1.0L*q[0][i]/((k+1)*need[0]);
						long double fr12 = 1.0L*q[1][perm[i]]/((k+1)*need[1]);
						if (0.9L<=fr01 && fr01<=1.1L && 0.9L<=fr11 && fr11<=1.1L){
							cur++;
							break;
						}
						else if (0.9L<=fr02 && fr02<=1.1L && 0.9L<=fr12 && fr12<=1.1L){
							cur++;
							break;
						}
					}
				}
				ans = max(ans, cur);
			} while(next_permutation(perm.begin(), perm.end()));
		}
		
		fout << "Case #" << testcase+1 << ": " << ans << endl;
		
	}
	
	fin.close();
	fout.close();
	return 0;
}

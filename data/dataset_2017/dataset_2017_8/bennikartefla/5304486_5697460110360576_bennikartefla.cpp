#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = (a); i < (b); i++)
#define iter(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end();++it)
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef long long ll;
const int INF = ~(1<<31);
const double pi = acos(-1);

struct BpGraph {
	vvi adj;
	vi owner;
	vector<bool> done;

	BpGraph(int n, int m) {
		adj = vvi(n);
		done = vector<bool>(n);
		owner = vi(m,-1);
	}
	void addEdge(int a, int b) {
		adj[a].push_back(b);
	}
	int alternating_path(int left) {
		if(done[left]) return 0;
		done[left] = true;
		rep(i,0,adj[left].size()) {
			int right = adj[left][i];
			if(owner[right] == -1 || alternating_path(owner[right])) {
				owner[right] = left;
				return 1;
			}
		}
		return 0;
	}
	int maximum_matching(int n, int m) {
		int res = 0;
		rep(i,0,n) {
			rep(a,0,n) done[a] = 0;
			res += alternating_path(i);
		}
		return res;
	}
};

bool binary(double num, double need) {
	int lo = 1, hi = 100000000;
	while(lo <= hi) {
		int mid = (lo+hi)/2;
		double ok = mid*num;
		double res = need/ok;
		if(res >= 0.90 && res <= 1.1) {
			return true;
		} 
		if(res > 1.1) {
			lo = mid+1;
		} else hi = mid-1;
	}
	return false;
}

int main() {
	cin.sync_with_stdio(false);
	ofstream fout("ans.txt");
	int t;
	cin >> t;
	rep(u,0,t) {
		int n,p;
		cin >> n >> p;
		int bst = 0;
		if(n == 1) {
			int count = 0;
			double duds = 0;
			cin >> duds;
			rep(i,0,p) {
				double hold;
				cin >> hold;
				if(binary(duds,hold)) count++;
			}
			bst = count;
		} else {
			BpGraph bp(p,p);
			int count = 0;
			vector<double> duds(n);
			rep(i,0,n) cin >> duds[i];
			vector<double> first(p);
			vector<double> second(p);
			rep(i,0,p) cin >> first[i];
			rep(i,0,p) cin >> second[i];
			rep(i,0,p) {
				rep(a,0,p) {
					bool can = false;
					rep(z,1,1000001) {
						double ok = duds[0]*z;
						double otherok = duds[1]*z;
						double fin1 = first[i]/ok;
						double fin2 = second[a]/otherok;
						if(fin1 >= 0.9 && fin1 <= 1.1 && fin2 >= 0.9 && fin2 <= 1.1) {
							can = true;
							break;
						}
					}
					if(can) {
						bp.addEdge(i,a);
					}
				}
			}
			bst = bp.maximum_matching(p,p);
		}
		fout << "Case #" << u+1 << ": " << bst << endl;
	}
	return 0;
}


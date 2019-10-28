#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

#define MAXN 2
#define MAXM 8

int find_max(int cant, int req) {
	return (10*cant)/(9*req);
}

int find_min(int cant, int req) {
	int tmp = (10*cant)/(11*req);
	if ((10*cant)%(11*req) != 0) tmp++;
	return tmp;
}

bool intersect(int a, int b, int c, int d) {
	if (b<a || d<c || b < c || a > d) return false;
	else return true;
}

int main() {
	int T, t, N, M, n[MAXN], m[MAXN][MAXM], i, j, RES;
	
	cin >> T;
	for (t=1; t<=T; t++) {
		cin >> N >> M;
		for (i=0; i<N; i++) cin >> n[i];
		for (i=0; i<N; i++) for (j=0; j<M; j++) cin >> m[i][j];
		
		RES = 0;
		if (N == 1) {
			for (i=0; i<M; i++) if (find_min(m[0][i], n[0]) <= find_max(m[0][i], n[0])) RES++;
		} else {
			sort(m[1], m[1]+M);
			
			do {
				int tmp = 0;
				for (i=0; i<M; i++) if (intersect(find_min(m[0][i], n[0]), find_max(m[0][i], n[0]), find_min(m[1][i], n[1]), find_max(m[1][i], n[1]))) tmp++;
				RES = max(RES, tmp);
			} while (next_permutation(m[1], m[1]+M));
		}
		cout << "Case #" << t << ": " << RES << endl;
	}

	return 0;
}

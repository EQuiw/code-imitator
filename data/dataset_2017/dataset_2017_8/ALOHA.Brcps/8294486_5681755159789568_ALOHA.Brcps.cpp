#include <stdio.h>
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <assert.h>
using namespace std;

#define INF 987654321654897123LL

int main() {
	int T;
	freopen("C-small-attempt1.in", "r", stdin);
	freopen("output.txt", "w", stdout);

	scanf("%d", &T);
	
	for(int testCase = 1; testCase <= T; testCase++) {
		int N, Q;

		scanf("%d %d", &N, &Q);

		pair<long long, long long > horses[101];

		for (int i = 0; i < N; i++) {
			scanf("%lld %lld", &horses[i].first, &horses[i].second);
		}

		long long adj[101][101];

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%lld", &adj[i][j]);
			}
		}

		int S, E;
		scanf("%d %d", &S, &E);
		S--; E--;

		double dist[101];
		fill(dist, dist + 101, INF);

		dist[S] = 0;

		for (int s = S; s < E; s++) {
			long long d = 0;
			for (int e = s + 1; e <= E; e++) {
				d += adj[e - 1][e];
				if (d <= horses[s].first) {
					dist[e] = min(dist[e], dist[s] + d / (double)horses[s].second);
				}
			}
		}

		printf("Case #%d: ", testCase);
		printf("%.6lf\n", dist[E]);
	}

	return 0;
}
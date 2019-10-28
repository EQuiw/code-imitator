#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;

int N, Q, E[100], S[100], D[100][100], U, V;
int i, j, q;
queue<pair<pair<short, double>, pair<int, int> > > que; // where am I, time elapsed, remaining endurance, speed
pair<pair<short, double>, pair<int, int> > p, p2; // where am I, time elapsed, remaining endurance, speed
double best;

int main() {
    int cases;
    scanf("%d", &cases);
    for (int kejs = 1; kejs <= cases; kejs++) {
        printf("Case #%d:", kejs);
        scanf("%d%d", &N, &Q);
        for (i = 0; i < N; i++) {
            scanf("%d%d", &E[i], &S[i]);
        }
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                scanf("%d", &D[i][j]);
            }
        }
        for (q = 0; q < Q; q++) {
            scanf("%d%d", &U, &V);
            U--; V--;
            best = -1;
            p.first.first = U;
            p.first.second = 0;
            p.second.first = 0;
            p.second.second = 0;
            que.push(p);
            while (!que.empty()) {
                p = que.front(); que.pop();
                //fprintf(stderr, "%d %.10lf %d %d\n", p.first.first, p.first.second, p.second.first, p.second.second);
                if (p.first.first == V) {
                    if (best == -1 || best > p.first.second) best = p.first.second;
                    continue;
                }
                for (i = 0; i < N; i++) {
                    if (D[p.first.first][i] == -1) continue;
                    if (D[p.first.first][i] <= p.second.first) { // endurance of current horse suffices
                        p2.first.first = i;
                        p2.first.second = p.first.second + ((double)D[p.first.first][i]) / p.second.second;
                        p2.second.first = p.second.first - D[p.first.first][i];
                        p2.second.second = p.second.second;
                        que.push(p2);
                    }
                    if (D[p.first.first][i] <= E[p.first.first]) { // endurance of horse in current town suffices
                        p2.first.first = i;
                        p2.first.second = p.first.second + ((double)D[p.first.first][i]) / S[p.first.first];
                        p2.second.first = E[p.first.first] - D[p.first.first][i];
                        p2.second.second = S[p.first.first];
                        que.push(p2);
                    }
                }
            }

            printf(" %.10lf", best);
        }
        printf("\n");
    }
    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;


const double eps = 1e-8;
const double pi = acos(-1.0);

priority_queue<long long> que[2];
long long mx, mi;

void pop(int x) {
    long long u = que[x].top();
    que[x].pop();
    mx = u / 2;
    mi = u / 2 -(x==0);
    que[mx & 1].push(mx);
    que[mi & 1].push(mi);
}

int main() {
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);

    int T;
    cin >> T;

    for (int cas = 1; cas <= T; cas++) {
        long long n, k;
        cin >> n >> k;

        for (int i = 0; i < 2; i++) {
            while (!que[i].empty()) {
                que[i].pop();
            }
        }

        que[n & 1].push(n);

        for (int i = 1; i <= k; i++) {
            if (que[0].empty()) {
                pop(1);
            } else if (que[1].empty()) {
                pop(0);
            } else {
                long long odd = que[1].top();
                long long even = que[0].top();
                if (odd > even) {
                    pop(1);
                } else {
                    pop(0);
                }
            }
        }

        cout << "Case #" << cas << ": " << mx << " " << mi << endl;
    }
    return 0;
}


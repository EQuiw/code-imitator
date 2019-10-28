#include <bits/stdc++.h>
using namespace std;
string g[25];

int main() {
    int T;
    cin >> T;
    for(int t = 1; t <= T; t++) {
        cout << "Case #" << t << ":" << endl;
        int R, C;
        cin >> R >> C;
        for(int i = 0; i < R; i++) {
            cin >> g[i];
        }
        for(int i = 0; i < R; i++) {
            for(int j = 0; j < C; j++) {
                if(g[i][j] != '?') {
                    for(int k = j - 1; k >= 0; k--) {
                        if(g[i][k] == '?') {
                            g[i][k] = g[i][j];
                        } else {
                            break;
                        }
                    }
                    for(int k = j + 1; k < C; k++) {
                        if(g[i][k] == '?') {
                            g[i][k] = g[i][j];
                        } else {
                            break;
                        }
                    }
                }
            }
        }
        for(int i = 0; i < R; i++) {
            for(int j = 0; j < C; j++) {
                if(g[i][j] == '?') {
                    if(i == 0) {
                        for(int ii = i + 1; ii < R; ii++) {
                            if(g[ii][j] != '?') {
                                g[i][j] = g[ii][j];
                                break;
                            }
                        }
                    } else {
                        for(int ii = i - 1; ii >= 0; ii--) {
                            if(g[ii][j] != '?') {
                                g[i][j] = g[ii][j];
                                break;
                            }
                        }
                    }
                }
            }
        }
        for(int i = 0; i < R; i++) {
            cout << g[i] << endl;
        }
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

int H, W;
vector<string> grid;

int dh[4] = {1, -1, 0, 0};
int dw[4] = {0, 0, 1, -1};

bool infield(int h, int w){
    return (0<=h && h<H && 0<=w && w<W);
}

void solve(){
    cin >> H >> W;
    grid.resize(H);
    for(auto &s: grid)
        cin >> s;
    
    for(int d=0; d<4; d++){
        for(int h=0; h<H; h++){
            for(int w=0; w<W; w++) if(grid[h][w] != '?'){
                int nh = h + dh[d];
                int nw = w + dw[d];
                while(infield(nh, nw) && grid[nh][nw]=='?'){
                    grid[nh][nw] = grid[h][w];
                    nh += dh[d];
                    nw += dw[d];
                }
            }
        }
    }
    
    for(auto s: grid)
        cout << s << endl;
}

int main(){
    int T; cin >> T;
    for(int t=0; t<T; t++){
        cout << "Case #" << t+1 << ":" << endl;
        solve();
    }
    
    return 0;
}

//
//  main.cpp
//  ProblemA
//
//  Created by Tung Nguyen on 4/15/17.
//
//

#include <fstream>

using namespace std;

char cake[25][25];
int R, C;

void fill(int r){
    for (int c = 0; c < C; c++) {
        if (cake[r][c] != '?') {
            char fillch = cake[r][c];
            for (int c1 = 0; c1 < c; c1++) {
                cake[r][c1] = fillch;
            }
            for (int c2 = c + 1; c2 < C; c2++) {
                if (cake[r][c2] == '?') {
                    cake[r][c2] = fillch;
                }
                else{
                    fillch = cake[r][c2];
                }
            }
            break;
        }
    }
}

bool is_row_empty(int r){
    for (int c = 0; c < C; c++) {
        if (cake[r][c] != '?') {
            return false;
        }
    }
    return true;
}

void solve(){
    for (int r = 0; r < R; r++) {
        if (!is_row_empty(r)) {
            fill(r);
            for (int r1 = r + 1; r1 < R; r1++) {
                if (!is_row_empty(r1)) {
                    fill(r1);
                }
                else{
                    for (int c = 0; c < C; c++) {
                        cake[r1][c] = cake[r1 - 1][c];
                    }
                }
            }
            for (int r2 = r - 1; r2 >= 0; r2--) {
                for (int c = 0; c < C; c++) {
                    cake[r2][c] = cake[r2 + 1][c];
                }
            }
            break;
        }
    }
}

int main(int argc, const char * argv[]) {
    ifstream fin("A-small-attempt0.in.txt");
    ofstream fout("A-small-attempt0.out.txt");
    
    int T;
    fin >> T;
    for (int Case = 1; Case <= T; Case++) {
        fin >> R >> C;
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                fin >> cake[i][j];
            }
        }
        
        solve();
        
        fout << "Case #" << Case << ": " << endl;
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                fout << cake[i][j];
            }
            fout << endl;
        }
    }
    
    fin.close();
    fout.close();
    
    return 0;
}

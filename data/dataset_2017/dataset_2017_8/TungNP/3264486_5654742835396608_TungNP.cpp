//
//  main.cpp
//  ProblemC
//
//  Created by Tung Nguyen on 4/8/17.
//
//

#include <fstream>

using namespace std;

long long N, K;
long long maxLR, minLR;

long long n_c[1000];
long long n[1000];

int i, c;

void append(long long ni, long long ci){
    bool match = false;
    for (int j = i + 1; j < c; j++) {
        if (n[j] == ni) {
            n_c[j] += ci;
            match = true;
            break;
        }
    }
    if (!match) {
        n[c] = ni;
        n_c[c] = ci;
        c++;
    }
}

void solve(){
    i = 0;
    c = 1;
    n_c[0] = 1;
    n[0] = N;
    long long k = 0;
    while (i < c) {
        long long ni = n[i];
        k += n_c[i];
        if (k >= K) {
            maxLR = ni / 2;
            minLR = ni / 2;
            if (ni % 2 == 0) {
                minLR--;
            }
            break;
        }
        else{
            long long ni1 = ni / 2;
            long long ni2 = ni / 2;
            if (ni % 2 == 0) {
                ni2--;
            }
            append(ni1, n_c[i]);
            append(ni2, n_c[i]);
        }
        i++;
    }
}

int main(int argc, const char * argv[]) {
    ifstream fin("C-small-1-attempt0.in.txt");
    ofstream fout("C-small-1-attempt0.out.txt");
    
    int T;
    fin >> T;
    for (int Case = 1; Case <= T; Case++) {
        fin >> N >> K;
        solve();
        fout << "Case #" << Case << ": " << maxLR << " " << minLR << endl;
    }
    
    fout.close();
    fin.close();
    
    return 0;
}

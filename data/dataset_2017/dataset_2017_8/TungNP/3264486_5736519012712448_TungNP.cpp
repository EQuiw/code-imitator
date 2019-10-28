//
//  main.cpp
//  ProblemA
//
//  Created by Tung Nguyen on 4/8/17.
//
//

#include <fstream>
#include <string>
using namespace std;

int main(int argc, const char * argv[]) {
    ifstream fin("A-small-attempt0.in.txt");
    int T, K;
    fin >> T;

    ofstream fout("A-small-attempt0.out.txt");
    
    for (int i = 0; i < T; i++) {
        string S;
        fin >> S;
        fin >> K;
        
        int count = 0;
        for (int j = 0; j <= S.length() - K; j++){
            if (S[j] == '-') {
                count++;
                for (int k = j; k < j + K; k++) {
                    if (S[k] == '-') {
                        S[k] = '+';
                    }
                    else{
                        S[k] = '-';
                    }
                }
            }
        }
        
        bool possible = true;
        for (int j = 0; j < S.length(); j++) {
            if (S[j] == '-') {
                possible = false;
                break;
            }
        }
        fout << "Case #" << i + 1 << ": ";
        if (possible) {
            fout << count << endl;
        }
        else{
            fout << "IMPOSSIBLE" << endl;
        }
    }
    fout.close();
    fin.close();
    return 0;
}

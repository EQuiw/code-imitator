//
//  main.cpp
//  ProblemA
//
//  Created by Tung Nguyen on 4/22/17.
//
//

#include <fstream>
#include <cmath>

using namespace std;

long long D;
int N;

long long K[1000];
long long S[1000];

int main(int argc, const char * argv[]) {
    ifstream fin("A-small-attempt1.in.txt");
    ofstream fout("A-small-attempt1.out.txt");
    
    int T;
    fin >> T;
    for (int Case = 1; Case <= T; Case++) {
        fin >> D >> N;
        
        double minTime = 0;
        
        for (int i = 0; i < N; i++) {
            fin >> K[i] >> S[i];
            double time = (D - K[i]) * 1.0 / S[i];
            minTime = time > minTime ? time : minTime;
        }
        char buff[100];
        snprintf(buff, sizeof(buff), "%.6f", D / minTime);
        
        
        fout << "Case #" << Case << ": " << buff << endl;
    }
    
    fin.close();
    fout.close();
    return 0;
}

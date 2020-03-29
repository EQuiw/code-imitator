//
//  main.cpp
//  ProblemA
//
//  Created by Tung Nguyen on 4/30/17.
//
//

#include <fstream>
#include <string>
#include <cmath>

using namespace std;

int N, K;

long long R[1000];
long long H[1000];

double AR[1000];
double AH[1000];

bool removed[1000];

double result;

int maxAR(double *ar, long long *r){
    int count = 0;
    *r = 0;
    *ar = 0;
    for (int i = 0; i < N; i++) {
        if (!removed[i]) {
            if (R[i] > *r) {
                *r = R[i];
                count = 1;
                *ar = AR[i];
            }
            else if (R[i] == *r){
                count++;
            }
        }
    }
    return count;
}

void remove(){
    long long max_r;
    double max_ar;
    int max_ar_count = maxAR(&max_ar, &max_r);
    
    double r_a = -1;
    int removei = -1;
    for (int i = 0; i < N; i++) {
        if (removed[i]) {
            continue;
        }
        
        double a_n = AH[i];
        if (max_ar_count == 1 && R[i] == max_r) {
            removed[i] = true;
            
            double max_ar_n;
            long long max_r_n;
            maxAR(&max_ar_n, &max_r_n);
            
            a_n = AH[i] + (max_ar - max_ar_n);
            removed[i] = false;
        }
        
        if (r_a == -1 || a_n < r_a) {
            r_a = a_n;
            removei = i;
        }
    }
    removed[removei] = true;
}

void solve(){
    for (int i = 0; i < N; i++) {
        removed[i] = false;
    }
    for (int i = 0; i < (N - K); i++) {
        remove();
    }
    
    double ar = 0;
    double ah = 0;
    
    for (int i = 0; i < N; i++) {
        if (!removed[i]) {
            if (AR[i] > ar) {
                ar = AR[i];
            }
            ah += AH[i];
        }
    }
    result = ar + ah;
}

int main(int argc, const char * argv[]) {
    ifstream fin("A-small-attempt3.in.txt");
    ofstream fout("A-small-attempt3.out.txt");
    
    int T;
    fin >> T;
    for (int Case = 1; Case <= T; Case++) {
        fin >> N >> K;
        for (int i = 0; i < N; i++) {
            fin >> R[i] >> H[i];
            AR[i] = M_PI * R[i] * R[i];
            AH[i] = 2 * M_PI * R[i] * H[i];
        }
        
        solve();
        
        fout << "Case #" << Case << ": ";
        char buff[100];
        snprintf(buff, 100, "%.9f", result);
        fout << buff << endl;
    }
    
    fin.close();
    fout.close();
    return 0;
}

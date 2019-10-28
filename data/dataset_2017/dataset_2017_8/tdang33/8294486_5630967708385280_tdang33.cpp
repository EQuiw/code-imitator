#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <iomanip>

using namespace std;

double solve(vector<vector<long long>> & v, long long d, long long n) {
    double result = pow(10,18)*1.0;
    for (int i = 0; i < n; i++) {
        double temp = d*v[i][1]/(1.0*(d-v[i][0]));
        result = min(result, temp);
    }
    return result;

}

int main() {
    int T; cin >> T;
    for (int i = 0; i < T; i++) {
        long long d; cin >> d;
        long long n; cin >> n;
        vector<vector<long long>> v(n, vector<long long>(2));
        for (int i1 = 0; i1< n; i1++) {
            for (int i2 = 0; i2 < 2;i2++) {
                cin >> v[i1][i2];
            }
        }
        cout <<setprecision(16)<< "Case #" << i+1 <<": "<< solve(v, d, n) << endl;
    }
    return 0;
}

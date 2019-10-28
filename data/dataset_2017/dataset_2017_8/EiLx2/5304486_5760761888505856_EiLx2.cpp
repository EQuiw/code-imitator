#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <cmath>
#include <cstring>
using namespace std;

#define fi first
#define se second
typedef long long LL;
typedef long double LD;

int R,C,T; char a[50][50];

int main(){
    ifstream fin("input.in");
    ofstream fout("output.out");
    fin >> T;

    int t,i,j;
    for (t=1; t<=T; t++){
        fout << "Case #" << t << ":\n";
        fin >> R >> C;
        for (i=1; i<=R; i++)
            for (j=1; j<=C; j++)
                fin >> a[i][j];

        int l=1,k;
        for (i=1; i<=R; i++)
            for (j=1; j<=C; j++)
                if (a[i][j]!='?'){
                    int p=i-1;
                    while (a[p][j]=='?' && p>0) a[p][j]=a[i][j],p--;

                    p=i+1;
                    while (a[p][j]=='?' && p<=R) a[p][j]=a[i][j],p++;
                }

        for (i=1; i<=R; i++)
            for (j=1; j<=C; j++)
                if (a[i][j]!='?'){
                    int p=j-1;
                    while (a[i][p]=='?' && p>0) a[i][p]=a[i][j],p--;

                    p=j+1;
                    while (a[i][p]=='?' && p<=C) a[i][p]=a[i][j],p++;
                }

        for (i=1; i<=R; i++, fout << "\n")
            for (j=1; j<=C; j++)
                fout << a[i][j];
    }
    return 0;
}

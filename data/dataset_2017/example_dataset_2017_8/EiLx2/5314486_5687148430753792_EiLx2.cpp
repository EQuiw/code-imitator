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

struct ticket{
    int p,b;
    ticket(int p=0, int b=0) : p(p), b(b) {}
};

int T,N,M,C,cost,ind[1010];
bool oc[1010][1010],al[1010][1010];
ticket a[1010];
int cnt[3][3];

bool check(int nr){
    int i,k;
    for (i=1; i<=nr; i++){
        memset(oc[i],0,sizeof(oc[i]));
        memset(al[i],0,sizeof(al[i]));
        ind[i]=1;
    }

    int cst=0;
    for (k=1; k<=M; k++){
        bool g=0;
        for (i=1; i<=nr; i++)
            if (!oc[i][a[k].p] && !al[i][a[k].b]){
                g=1;
                oc[i][a[k].p]=1,al[i][a[k].b]=1;
                break;
            }

        if (g) continue;

        for (i=1; i<=nr; i++){
            if (!al[i][a[k].b]){
                while (oc[i][ind[i]] && ind[i]<=N)
                    ind[i]++;

                if (ind[i]<a[k].p){
                    g=1;
                    oc[i][ind[i]]=1;
                    al[i][a[k].b]=1;
                    cst++;
                    break;
                }
            }
        }

        if (!g) return 0;
    }

    cost=cst;
    return 1;
}

int main(){
    ifstream fin("input.in");
    ofstream fout("output.out");
    fin >> T;

    int i,t;
    for (t=1; t<=T; t++){
        fout << "Case #" << t << ": ";
        fin >> N >> C >> M;

        memset(cnt,0,sizeof(cnt));
        for (i=1; i<=M; i++){
            fin >> a[i].p >> a[i].b;
            if (t==4) cnt[a[i].p][a[i].b]++;
        }

        if (t==43){
            cout << N << " " << C << " " << M << "\n";

        }
        sort(a+1,a+M+1,[](ticket A, ticket B) { if (A.b==B.b) return A.p<B.b; else return A.b < B.b; });

        cost=10*M;
        int l=1,r=M;

        while (l<r){
            int mid=(l+r)/2;
            if (check(mid)) r=mid;
            else l=mid+1;
        }

        check(r);
        int res=cost;

        sort(a+1,a+M+1,[](ticket A, ticket B) { if (A.p==B.p) return A.b<B.b; else return A.p< B.p; });
        cost=10*M;
         l=1,r=M;

        while (l<r){
            int mid=(l+r)/2;
            if (check(mid)) r=mid;
            else l=mid+1;
        }

        res=min(res,cost);
        fout << r << " " << res << "\n";
    }
    return 0;
}

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

int T,N,M,ln[500],rn[500]; char a[110][110],p[110][110],xs[110][110],ans[110][110];
bool vc[110],vr[110]; bool v[500];
map<int,bool> mps,mpd;
vector<int> g[510];

bool match(int nod){
    if (v[nod])
        return 0;
    v[nod]=1;

    for (int next : g[nod]){
        if (!rn[next] || match(rn[next])){
            ln[nod]=next;
            rn[next]=nod;
            return 1;
        }
    }
    return 0;
}

int main(){
    ifstream fin("input.in");
    ofstream fout("output.out");
    fin >> T;

    int t,i,j;
    for (t=1; t<=T; t++){
        cout << t << "\n";
        fout << "Case #" << t << ": ";

        fin >> N >> M;
        for (i=1; i<=N; i++)
            for (j=1; j<=N; j++)
                a[i][j]=p[i][j]=xs[i][j]='.';

        int x,y; char c;
        memset(vc,0,sizeof(vc));
        memset(vr,0,sizeof(vr));
        mps.clear();
        mpd.clear();

        for (i=1; i<=M; i++){
            fin >> c >> x >> y;
            a[x][y]=c;
            if (c!='+') vr[x]=1,vc[y]=1;
            if (c!='x') mps[x+y]=1,mpd[x-y]=1;

            if (c!='x') p[x][y]='+';
            if (c!='+') xs[x][y]='x';
        }

        int l=1;
        for (i=1; i<=N; i++)
            if (!vr[i]){
                while (vc[l]) l++;
                xs[i][l]='x';
                vr[i]=vc[l]=1;
            }

        memset(g,0,sizeof(g));
        for (i=2; i<=2*N; i++)
            for (j=-(N-1); j<=N-1; j++){
                if ((i-j)%2!=0 || mps[i] || mpd[j]) continue;
                x=(i+j)/2;
                y=(i-j)/2;
                if (1<=x && x<=N && 1<=y && y<=N){
                    g[i-1].push_back(j+N);
                }
            }

        memset(rn,0,sizeof(rn));
        memset(ln,0,sizeof(ln));
        bool ex=1;
        while (ex){
            ex=0;
            memset(v,0,sizeof(v));
            for (i=1; i<=2*N-1; i++)
                if (!ln[i])
                    ex|=match(i);
        }

        for (i=1; i<=2*N-1; i++)
            if (ln[i]){
                int s=i+1,d=ln[i]-N;
                x=(s+d)/2;
                y=(s-d)/2;
                p[x][y]='+';
            }

        int res=0,mod=0;
        for (i=1; i<=N; i++)
            for (j=1; j<=N; j++){
                if (p[i][j]=='+' && xs[i][j]=='x') ans[i][j]='o',res+=2;
                else if (p[i][j]=='+') ans[i][j]='+',res++;
                else if (xs[i][j]=='x') ans[i][j]='x',res++;
                else ans[i][j]='.';

                if (ans[i][j]!=a[i][j]) mod++;
            }

        fout << res << " " << mod << "\n";
        for (i=1; i<=N; i++)
            for (j=1; j<=N; j++)
                if (ans[i][j]!=a[i][j]){
                    fout << ans[i][j] << " " << i << " " << j << "\n";
                }
    }
    return 0;
}

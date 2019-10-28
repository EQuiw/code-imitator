#include<bits/stdc++.h>
#define pb   push_back
using namespace std;
typedef long long ll;
typedef long double ld;

string g[55];

int T, R, C;

vector<int> x[55], y[55];

char get(int i, int j, int dx, int dy){
  if (i<0 || j<0 || i>=R || j>=C) return '?';
  if (g[i][j]!='?') return g[i][j];
  return g[i][j] = get(i+dx, j+dy, dx, dy);
}

int main(){
  ios_base::sync_with_stdio(false);cin.tie(0);
  cin >> T;
  for(int it=1;it<=T;it++){
    cin >> R >> C;
    for(int i=0;i<26;i++){
      x[i].clear(); y[i].clear();
    }
    for(int i=0;i<R;i++){
      cin >> g[i];
      for(int j=0;j<C;j++){
        if (g[i][j]=='?') continue;
        int l=g[i][j]-'A';
        x[l].pb(i);
        y[l].pb(i);
      }
    }
    for(int a=0;a<26;a++){
      if (!x[a].size())continue;
      sort(x[a].begin(),x[a].end());
      sort(y[a].begin(),y[a].end());
      for(int i=x[a][0];i<x[a][x[a].size()-1];i++)
        for(int j=y[a][0];j<y[a][x[a].size()-1];j++)
          g[i][j]=(char)('A'+a);
    }
    int dx, dy;
    for(int tt=0;tt<4;tt++){
      dx = 0;
      for(dy=-1;dy<2;dy+=2)
        for(int i=0;i<R;i++)
          for(int j=0;j<C;j++)
            if (g[i][j]=='?')
              get(i,j,dx,dy);
      dy = 0;
      for(dx=-1;dx<2;dx+=2)
        for(int i=0;i<R;i++)
          for(int j=0;j<C;j++)
            if (g[i][j]=='?')
              get(i,j,dx,dy);
    }
    cout << "Case #"<<it<<":"<<endl;
    for(int i=0;i<R;i++) cout << g[i] <<endl;
  }
}

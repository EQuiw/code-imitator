#include <bits/stdc++.h>
using namespace std;
#ifdef DEBUG
    #define debug(...) printf(__VA_ARGS__)
#else
    #define debug(...) (void)0
#endif
#define MP make_pair
#define PB push_back
#define LL long long
#define pii pair<int,int>



#define ALL(x) (x).begin(),(x).end()
#define SZ(x) ((int)(x).size())
//const int inf = 0x7fffffff; //beware overflow
//const LL INF = 0x7fffffffffffffff; //beware overflow
#define mem(x, y) memset(x, (y), sizeof(x) );
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
template<typename A, typename B>
ostream& operator <<(ostream &s, const pair<A,B> &p) {
     return s<<"("<<p.first<<","<<p.second<<")";
}
template<typename T>
ostream& operator <<(ostream &s, const vector<T> &c) {
    s << "[ ";
    for (auto it : c) s << it << " ";
    s << "]";
    return s;
}
template<typename T>
ostream& operator << (ostream &o, const set<T> &st) {
    o << "{";
    for (auto it=st.begin(); it!=st.end(); it++) o << (it==st.begin() ? "" : ", ") << *it;
    return o << "}";
}
template<typename T1, typename T2>
ostream& operator << (ostream &o, const map<T1, T2> &mp) {
    o << "{";
    for (auto it=mp.begin(); it!=mp.end(); it++) {
        o << (it==mp.begin()?"":", ") << it->first << ":" << it->second;
    }
    o << "}";
    return o;
}
inline LL getint(){
   LL _x=0,_tmp=1; char _tc=getchar();
   while( (_tc<'0'||_tc>'9')&&_tc!='-' ) _tc=getchar();
   if( _tc == '-' ) _tc=getchar() , _tmp = -1;
   while(_tc>='0'&&_tc<='9') _x*=10,_x+=(_tc-'0'),_tc=getchar();
   return _x*_tmp;
}
#define maxn
int main() {
    int T = getint();
    for(int testcase=1; testcase<=T; testcase++) {

        char t[50][50];
        bool empty[50];
        vector<pii> G[26];
        printf("Case #%d:\n", testcase);
        int R = getint(), C = getint();
        for(int i=0;i<R;i++) {

            scanf("%s", t[i]);
            empty[i] = all_of(t[i]+0, t[i]+C, [](char c) {
                    return c=='?';
                });
        }
        /*
        for(int i=0;i<R;i++)for(int j=0;j<C;j++) if(t[i][j]!='?')
            G[ t[i][j]-'A' ].push_back(MP(i,j));

        for(int i=0;i<26;i++) {
            int l=R, r=-1, u=R, d=-1;
            for(pii p : G[i]) {
                l = min(l, p.second);
                r = max(r, p.second);
                u = min(u, p.first);
                d = max(d, p.first);
            }
            if( r == -1 ) continue;
            for(int k = u; k <= d; k++)
                fill(t[k]+l, t[k]+r+1, 'A'+i);
        }
        */
        for(int i=0;i<R;i++) if( !empty[i]) {
            int ind;
            char c;
            for(int j=0;j<C;j++) {
                if( t[i][j] != '?' ) {
                    fill(t[i], t[i]+j, t[i][j]);
                    ind =j;
                    break;
                }
            }
            while(ind < C) {
                if( t[i][ind] == '?' ) {
                    t[i][ind] = c, ind++;
                }else
                    c = t[i][ind], ind++;
            }
        }
        vector<int> v(R);
        for(int i=0;i<R;i++) if( empty[i] ) {

            for(int j=i-1; j>=0; j--)
                if( !empty[j] ) {v[i] = j;break;}
            for(int j=i+1; j< R; j++)
                if( !empty[j]) {v[i]=j;break;}
        }
        for(int i=0;i<R;i++) {
            if(empty[i]) puts(t[ v[i] ]);
            else puts(t[i]);
        }
    }
}


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
#define maxn 100
int R[maxn];
int Q[50][50];

void solve() {
    int n = getint(), p = getint();
    for(int i=0;i<n;i++) R[i]=getint();
    for(int i=0;i<n;i++) {
        for(int j=0;j<p;j++) Q[i][j]=getint();
        sort(Q[i], Q[i]+p);
    }
    vector< vector<pii> > vv(n, vector<pii>(p));
    for(int i=0;i<n;i++)for(int j=0;j<p;j++) {
        int f =  (int)ceil(Q[i][j]*1.0/R[i]/1.1);
        int s = (int)floor(Q[i][j]*1.0/R[i]/0.9);
        if( f <= s ) vv[i][j] = MP(f, s);
    }
    //cout << vv << endl;

    int ans=0;

    vector<int> ptr(n, 0);
    for(int cur=1; cur<=  1e6; cur++) {
        for(int i=0;i<n;i++) {
            while( ptr[i] < SZ(vv[i]) && !(cur < vv[i][ptr[i]].first) && !(cur>=vv[i][ptr[i]].first&&cur<=vv[i][ptr[i]].second) )
                ptr[i]++;
        }

        vector<int> used(n, 0);
        for(int i=0;i<n;i++) {
            while( ptr[i]+used[i] < SZ(vv[i]) && vv[i][ptr[i]+used[i]].first <= cur && vv[i][ptr[i]+used[i]].second >= cur )
                used[i]++;
        }
        int tmp=*min_element(used.begin(), used.end());
        ans += tmp;
        for(int i=0;i<n;i++) ptr[i]+=tmp;

        for(int i=0;i<n;i++) if(ptr[i]==SZ(vv[i]) )break;
    }
    printf("%d\n", ans);
}
int main() {
    int T = getint();
    for(int testcase=1;testcase<=T;testcase++) {
        printf("Case #%d: ", testcase);
        solve();
    }
}


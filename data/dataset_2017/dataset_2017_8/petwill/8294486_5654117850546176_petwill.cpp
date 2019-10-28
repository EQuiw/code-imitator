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
    int T=getint();
    for(int testcase=1;testcase<=T;testcase++) {
        printf("Case #%d: ", testcase);
        int n=getint();
        int r, ry, y, yb, b, rb;
        scanf("%d %d %d %d %d %d" ,&r, &ry, &y, &yb, &b, &rb);
        if( n == 3 ) {
            if( r == 1 && b == 1 && y == 1 ) printf("RBY\n");
            else printf("IMPOSSIBLE\n");
        }else {

            pair<int, int> a[3] = { MP(r,'R'), MP(b, 'B'), MP(y, 'Y') };
            sort(a, a+3);
            if( a[0].first+a[1].first<a[2].first ) printf("IMPOSSIBLE\n");
            else {
                int len = 3*a[2].first;
                vector<char> v(len, 'A');
                int ind=0;
                for(int i=0;i<a[2].first;i++) v[ind] = a[2].second, ind+=3;

                ind = 1;
                for(int i=0;i<a[0].first;i++) v[ind] = a[0].second, ind += 3;
                ind = (ind+1)%len;
                for(int i=0;i<a[1].first;i++) v[ind] = a[1].second, ind = (ind+3)%len;

                for(char c : v) if( c != 'A' ) putchar(c);
                putchar('\n');
            }
        }
    }
}


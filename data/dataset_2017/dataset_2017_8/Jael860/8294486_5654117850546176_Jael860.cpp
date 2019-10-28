#include <bits/stdc++.h>


#define debug(x) cerr<< #x << ": "<< x << endl;
#define print(x) cerr<< x << endl;

#define mp make_pair
#define pb push_back
#define all(x) (x).begin() , (x).end()
#define rall(x) (x).rbegin() , (x).rend()
#define REP(i,x,y) for(int i=x;i<y;i++)
#define REPIT(it,A) for(typeof(A.begin()) it = (A.begin()); it!=A.end();it++)
#define fst first
#define snd second
#define sqr(x) ((x)*(x))

#define fastio ios_base::sync_with_stdio(0);cin.tie(0);
#define ones(x) __builtin_popcountll(x)
using namespace std;

typedef pair<int,int> ii ;
typedef long long ll ;
typedef vector<int> vi;
typedef vector<ii> vii;

const int MAXN = 1200;
const string OUT = "IMPOSSIBLE";
int N, R, O, Y, G, B, V;
pair<int, char> arr[10];
bool check(string res){

    REP(i,0,res.size()-1){
        if(res[i] == res[i+1]) return false;
    }
    return true;
}
int main(){
    fastio;
    int T;

    cin >> T;

    REP(test,1,T+1){
        cout<<"Case #"<<test<<": ";
        cin >> N >> R >> O >> Y >> G >> B >> V;
        if(V > 0 && V >= Y) {
            cout<<OUT<<endl;
            continue;
        }
        if(G > 0 && G >= R) {
            cout<<OUT<<endl;
            continue;
        }
        if(O > 0 && O >= B) {
            cout<<OUT<<endl;
            continue;
        }
        /*
        arr[0] = mp(Y - V, V);
        arr[1] = mp(R - G, G);
        arr[2] = mp(B - O, O);*/;
        arr[0] = mp(Y,'Y');
        arr[1] = mp(R,'R');
        arr[2] = mp(B,'B');
        string res = "";
        int ls = -1;
        bool flg = true;
        int ini = -1;
        REP(i,0,N){
            int mx = 0;
            int id = -1;
            REP(j,0,3){
                if(j == ls) continue;
                if(arr[j].fst > mx){
                    mx = arr[j].fst;
                    id = j;
                }else if(arr[j].fst == mx && mx > 0 && j == ini){
                    id = j;
                }
            }
            if(i == 0 ) ini = id;
            //cerr<<arr[0].fst<<" "<<arr[1].fst<<" "<<arr[2].fst<<endl;
            if(id == -1){
                flg = false;
                break;
            }
            ls = id;
            arr[id].fst--;
            res += arr[id].snd;
        }
        if(!flg || res[0] == res[N-1]){cout<<OUT<<endl; continue;}
        cout<<res<<endl;
    }



    return 0;
}

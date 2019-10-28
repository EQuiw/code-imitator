#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

class Edge{
public:
    int to, cap, rev;
    Edge(int _to, int _cap, int _rev): to(_to), cap(_cap), rev(_rev){};
};

class FordFulkerson{
private:
    vector<vector<Edge> > G;
    vector<bool> used;
    
public:
    FordFulkerson(int n){
        G.resize(n);
        used.resize(n);
    }
    
    void add_edge(int from, int to, int cap){
        G[from].push_back(Edge(to, cap, G[to].size()));
        G[to].push_back(Edge(from, 0, G[from].size()-1));
    }
    
    int dfs(int v, int t, int f){
        if(v == t)
            return f;
        used[v] = true;
        for(int i=0; i<G[v].size(); i++){
            Edge& e = G[v][i];
            if(!used[e.to] && e.cap > 0){
                int d = dfs(e.to, t, min(f, e.cap));
                if(d > 0){
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
    
    int max_flow(int s, int t){
        int res = 0;
        while(true){
            fill(used.begin(), used.end(), false);
            int f = dfs(s, t, INF);
            if(f == 0)
                return res;
            res += f;
        }
        return res;
    }
};

//int M = 100100;
int N, P;
vector<int> R;
vector<vector<int>> Q;
//vector<int> lbs(M, -1);
//vector<int> ubs(M, INF);

void solve(){
    cin >> N >> P;
    R.resize(N);
    for(auto &v: R)
        cin >> v;
    
    Q.clear();
    Q.resize(N);
    for(auto &vec: Q){
        for(int j=0; j<P; j++){
            int q; cin >> q;
            vec.push_back(q);
        }
    }
    
    vector<vector<pair<int, int>>> xQ;
    xQ.resize(N);
    
    for(int i=0; i<N; i++){
        for(int j=0; j<P; j++){
            int ub = floor(Q[i][j]/(R[i]*0.9) + 1e-6);
            int lb = ceil(Q[i][j]/(R[i]*1.1) - 1e-6);
            
            xQ[i].emplace_back(lb, ub);
        }
    }
    
    auto ff = FordFulkerson(N*P+2);
    for(int i=0; i<N-1; i++){
        for(int j=0; j<P; j++){
            for(int k=0; k<P; k++){
                if(xQ[i][j].first > xQ[i][j].second || xQ[i+1][k].first > xQ[i+1][k].second)
                    continue;
                
                if(xQ[i][j].first <= xQ[i+1][k].second && xQ[i+1][k].first <= xQ[i][j].second)
                    ff.add_edge(i*P+j, (i+1)*P+k, 1);
            }
        }
    }
    //s
    for(int i=0; i<P; i++){
        if(xQ[0][i].first > xQ[0][i].second)
            continue;
        ff.add_edge(N*P, i, 1);
    }
    //t
    for(int i=0; i<P; i++){
        if(xQ[(N-1)][i].first > xQ[(N-1)][i].second)
            continue;
        
        ff.add_edge((N-1)*P+i, N*P+1, 1);
    }
    
    cout << ff.max_flow(N*P, N*P+1) << endl;
}

int main(){
//    for(int i=0; i<M; i++){
//        int lb = i*(9+10-1)/10;
//        int ub = i*11/10;
//        for(int j=lb; j<=min(ub, M-1); j++){
//            lbs[j] = min(lbs[j], i);
//            ubs[j] = max(ubs[j], i);
//        }
//    }
    
    int T; cin >> T;
    for(int t=0; t<T; t++){
        cout << "Case #" << t+1 << ": ";
        solve();
    }
    
    return 0;
}

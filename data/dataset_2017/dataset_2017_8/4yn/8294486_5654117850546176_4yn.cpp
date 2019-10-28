#include <bits/stdc++.h>
using namespace std;

#define MAX_N 1009

struct AugPath {
    int A, B;   //size of left, right groups
    vector<vector<int> > G; //size A
    vector<bool> visited;   //size A
    vector<int> P;          //size B
    
    AugPath(int _A, int _B): A(_A), B(_B), G(_A), P(_B, -1) {}
    
    void AddEdge(int a, int b) {    //a from left, b from right
        G[a].push_back(b);
    }
    bool Aug(int x) {
        if (visited[x]) return 0;
        visited[x] = 1;
        /* Greedy heuristic */
        for (auto it:G[x]) {
            if (P[it] == -1) {
                P[it] = x;
                return 1;
            }
        }
        for (auto it:G[x]) {
            if (Aug(P[it])) {
                P[it] = x;
                return 1;
            }
        }
        return 0;
    }
    int MCBM() {
        int matchings = 0;
        for (int i = 0; i < A; ++i) {
            visited.resize(A, 0);
            matchings += Aug(i);
            visited.clear();
        }
        return matchings;
    }
    vector<pair<int, int> > GetMatchings() {
        vector<pair<int, int> > matchings;
        for (int i = 0; i < B; ++i) {
            if (P[i] != -1) matchings.emplace_back(P[i], i);
        }
        return matchings;
    }
};

int tc;

int d[7][7] = {
//     R O Y G B V
	{0,0,0,0,0,0,0},
	{0,0,0,1,1,1,0}, // R
	{0,0,0,0,0,1,0}, // O 
	{0,1,0,0,0,1,1}, // Y
	{0,1,0,0,0,0,0}, // G
	{0,1,1,1,0,0,0}, // B
	{0,0,0,1,0,0,0}, // V
};

char color_dict[7] = {
	'-','R','O','Y','G','B','V',
};

int next_node[MAX_N],visited[MAX_N];
int c[7];
int color[MAX_N],adj[MAX_N][MAX_N];
vector<string> stables;

string dfs(int node,string cur_string){
	if(visited[node] == 1){
		return cur_string;
	}
	visited[node] = 1;
	cur_string = cur_string + color_dict[color[node]];
	return dfs(next_node[node],cur_string);
}

string merge(string a, string b){
	bool found = false;
	int x = 0, y = 0;
	for(int i=0;i<a.size();i++){
		for(int j=0;j<b.size();j++){
			if(a[i]==b[j]){
				x = i;
				y = j;
				found = true;
				break;
			}
		}
		if(found){
			break;
		}
	}
	if(!found){
		return "";
	}
	// a[x] == b[y];
	string c = "";
	for(int i=0;i<b.size();i++){
		c += b[(y+i)% b.size()];
	}
	string rt = "";
	for(int i=0;i<x;i++){
		rt += a[i];
	}
	rt += c;
	for(int i=x;i<a.size();i++){
		rt += a[i];
	}
	return rt;
}
int main(){
	cin >> tc;
	for(int t=1;t<=tc;t++){
		int n; cin >> n;
		int counter = 0;
		c[0] = 0;
		for(int i=1;i<7;i++){
			cin >> c[i];
			c[i] += c[i-1];
			for(int j=c[i-1];j<c[i];j++){
				color[j] = i;
			}
		}
		AugPath mcbm(n,n);
		memset(adj,0,sizeof(adj));
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				adj[i][j] = d[color[i]][color[j]];
				if(adj[i][j]==1){
					mcbm.AddEdge(i,j);
				}
			}
		}
		auto matches = mcbm.MCBM();
		// cout << matches << " matches out of " << n << endl;
		if(matches!=n){
			cout << "Case #" << t << ": " << "IMPOSSIBLE" << endl;
			continue;
		}

		auto match = mcbm.GetMatchings();
		
		memset(next_node,-1,sizeof(next_node));
		memset(visited,-1,sizeof(visited));

		for(auto i:match){
			next_node[i.first] = i.second;
			// cout << i.first << " " << i.second << endl;
		}
		stables.clear();
		for(int i=0;i<n;i++){
			if(next_node[i]!=-1 && visited[i]==-1){
				stables.push_back(dfs(i,""));
			}
		}
		
		for(int i=0;i<stables.size();i++){
			for(int j=1;j<stables.size();j++){
				string test = merge(stables[0],stables[j]);
				if(test!=""){
					stables[0] = test;
					stables[j] = "";
				}
			}
		}
		cout << "Case #" << t << ": " << stables[0]  << endl;
	}
}
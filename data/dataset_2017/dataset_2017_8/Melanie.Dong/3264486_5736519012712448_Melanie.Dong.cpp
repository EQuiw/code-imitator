#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

bool ok(string s)
{
    for(int i=0;i<s.length();i++)
        if(s[i]=='-')
            return false;
    return true;
}
string s;
int n, m;
queue<pair<string, int> > q;
map<pair<string, int>, bool> vis;
int bfs()
{
    while(!q.empty())
        q.pop();
    vis.clear();
    if(ok(s))
        return 0;
    q.push(make_pair(s, 0));
    while(!q.empty())
    {
        pair<string, int> cur=q.front();
        q.pop();
        for(int i=0;i<=n-m;i++)
        {
            string tmp=cur.first;
            string str=tmp.substr(i, m);
//            cout<<tmp<<" "<<str<<" "<<vis[make_pair(tmp, i)]<<endl;
            if(ok(str) || vis[make_pair(tmp, i)])
                continue;
            vis[make_pair(tmp, i)]=1;
            for(int j=0;j<m;j++)
                tmp[i+j]=(tmp[i+j]=='-'? '+':'-');
            if(ok(tmp))
                return cur.second+1;
            q.push(make_pair(tmp, cur.second+1));
        }
    }
    return -1;
}
int main()
{
    freopen("A-small-attempt1.in", "r", stdin);
    freopen("A-small-attempt1.out", "w", stdout);
    int t, ca=1;
    scanf("%d", &t);
    while(t--)
    {
        printf("Case #%d: ", ca++);
        cin>>s>>m;
        n=s.length();
        int ans=bfs();
        if(ans==-1)
            puts("IMPOSSIBLE");
        else
            printf("%d\n", ans);
    }
    return 0;
}

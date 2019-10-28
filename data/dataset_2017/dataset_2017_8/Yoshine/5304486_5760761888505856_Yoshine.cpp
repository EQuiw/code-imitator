#include<bits/stdc++.h>

using namespace std;

char mp[28][28];
int r,c;
bool vis[128];
void work(int ca) {
    scanf("%d %d",&r,&c);
    for (int i = 1;i <= r;i++)
        for (int j = 1;j <= c;j++)
            scanf(" %c",&mp[i][j]);
    printf("Case #%d:\n",ca);
    int dl,dr;
    memset(vis,0,sizeof(vis));
    for (int j = 1;j <= c;j++)
        for (int i = 1;i <= r;i++) if (mp[i][j] != '?' && !vis[mp[i][j]]){
            vis[mp[i][j]] = 1;
            dl = dr = j;
            for (int jj = j - 1;jj > 0;jj--)
                if (mp[i][jj] == mp[i][j])
                    dl--;
                else
                    break;
            for (int jj = j + 1;jj <= c;jj++)
                if (mp[i][jj] == mp[i][j])
                    dr++;
                else
                    break;
            bool ok,ok1;
            int li1,li2;
            li1 = li2 = i;
            for (int ii = i - 1;ii > 0;ii--) {
                ok = 0;
                if (mp[ii][j] == mp[i][j] || mp[ii][j] == '?') {
                    ok1 = 1;
                    for (int jj = dl;jj <= dr;jj++)
                        if (mp[ii][jj] != mp[i][j] && mp[ii][jj] != '?') {
                            ok1 = 0;
                            break;
                        }
                    if (ok1) {
                        ok = 1;
                        li1 = ii;
                        for (int jj = dl;jj <= dr;jj++)
                            mp[ii][jj] = mp[i][j];
                    }
                }
                if (!ok)
                    break;
            }
            for (int ii = i + 1;ii <= r;ii++) {
                ok = 0;
                if (mp[ii][j] == mp[i][j] || mp[ii][j] == '?') {
                    ok1 = 1;
                    for (int jj = dl;jj <= dr;jj++)
                        if (mp[ii][jj] != mp[i][j] && mp[ii][jj] != '?') {
                            ok1 = 0;
                            break;
                        }
                    if (ok1) {
                        ok = 1;
                        li2 = ii;
                        for (int jj = dl;jj <= dr;jj++)
                            mp[ii][jj] = mp[i][j];
                    }
                }
                if (!ok)
                    break;
            }
            while (dl > 0) {
                ok = 1;
                for (int ii = li1;ii <= li2;ii++)
                    if (mp[ii][dl-1] != mp[i][j] && mp[ii][dl-1] != '?') {
                        ok = 0;
                        break;
                    }
                if (!ok)
                    break;
                dl--;
            }
            while (dr <= c) {
                ok = 1;
                for (int ii = li1;ii <= li2;ii++)
                    if (mp[ii][dr+1] != mp[i][j] && mp[ii][dr+1] != '?') {
                        ok = 0;
                        break;
                    }
                if (!ok)
                    break;
                dr++;
            }
            for (int ii = li1;ii <= li2;ii++)
                for (int jj = dl;jj <= dr;jj++)
                    mp[ii][jj] = mp[i][j];
        }
    for (int i = 1;i <= r;i++) {
        for (int j = 1;j <= c;j++)
            printf("%c",mp[i][j]);
        printf("\n");
    }
}

int main() {
    int tt;
    scanf("%d",&tt);
    for(int _ = 1;_ <= tt;_++)
        work(_);
    return 0;
}

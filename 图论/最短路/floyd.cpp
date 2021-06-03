//Luogu P1119 灾后重建
//floyd 城镇编号[0,n-1] t[i]<=t[i+1] 建成，询问时间不下降
#include <bits/stdc++.h>
using namespace std;
#define maxn 210
#define maxm 50010
#define inf 0x3f3f3f3f
int n, m, x, y, z, dis[maxn][maxn], ans[maxm], t[maxn];
bool vis[maxn];
tuple<int, int, int> q[maxm];
signed main() {
    scanf("%d%d", &n, &m);
    memset(dis, 0x3f, sizeof(dis));
    for (int i = 0; i < n; i++) scanf("%d", t + i);
    for (int i = 0; i < n; i++) dis[i][i] = 0;
    while (m--) {
        scanf("%d%d%d", &x, &y, &z);
        dis[x][y] = dis[y][x] = min(z, dis[x][y]);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &x, &y, &z);
        q[i] = make_tuple(z, x, y);
    }
    int p = 0;
    for (int k = 0; k < n; k++) {
        while (p < m && get<0>(q[p]) < t[k]) {
            if (vis[get<1>(q[p])] == false || vis[get<2>(q[p])] == false) ans[p] = inf;
            else ans[p] = dis[get<1>(q[p])][get<2>(q[p])];
            p++;
        }
        vis[k] = true;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                dis[i][j] = dis[j][i] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
    while (p < m) {
        ans[p] = dis[get<1>(q[p])][get<2>(q[p])];
        p++;
    }
    for (int i = 0; i < m; i++) printf("%d\n", ans[i] == inf ? -1 : ans[i]);
    return 0;
}
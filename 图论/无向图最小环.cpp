//Luogu P6175 无向图的最小环问题
//给定一张无向图，求图中一个至少包含 3 个点的环，环上的节点不重复，并且环上的边的长度之和最小。该问题称为无向图的最小环问题。在本题中，你需要输出最小的环的边权和。若无解，输出 No solution.。
#include <bits/stdc++.h>
using namespace std;
#define maxn 110
#define inf 600000000 //注意inf
int n, m, u, v, w, ans = inf;
int dis[maxn][maxn][2];
//dis[u][v][1]表示dis[u][v]的边长,而非最短路 dis[u][v][0]表示更新后dis[u][v]最短路
signed main() {
    scanf("%d%d", &n, &m);
    fill((int *) dis, (int *) dis + sizeof(dis) / sizeof(int), inf);
    for (int i = 1; i <= n; i++) dis[i][i][0] = dis[i][i][1] = 0;
    while (m--) {
        scanf("%d%d%d", &u, &v, &w);
        dis[u][v][0] = dis[v][u][0] = dis[u][v][1] = dis[v][u][1] = min(dis[v][u][1], w);//注意重边
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i < k; i++) {
            for (int j = i + 1; j < k; j++) {
                ans = min(ans, dis[i][j][0] + dis[j][k][1] + dis[k][i][1]);//三项加起来 inf!= 0x3f3f3f3f
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dis[i][j][0] = dis[j][i][0] = min(dis[i][j][0], dis[i][k][0] + dis[k][j][0]);
            }
        }
    }
    if (ans == inf) puts("No solution.");
    else printf("%d\n", ans);
    return 0;
}
//Luogu P4408 [NOI2003] 逃学的小孩
//找到三点A、B、C找到min(dis[A][C],dis[B][C])+dis[A][B]
//其中AB是直径，C进行枚举
#include <bits/stdc++.h>
using namespace std;
#define maxn 200100
int n, m, x, y, z, p, pa, pb;
long long dis[3][maxn], ans;
vector<pair<int, int> > e[maxn];
void dfs(int u, int fa, long long *dis) {
    if (ans < dis[u]) ans = dis[u], p = u;
    for (auto &[v, w]:e[u]) {
        if (v == fa)continue;
        dis[v] = dis[u] + w;
        dfs(v, u, dis);
    }
}
signed main() {
    scanf("%d%d", &n, &m);
    while (m--) {
        scanf("%d%d%d", &x, &y, &z);
        e[x].push_back(make_pair(y, z));
        e[y].push_back(make_pair(x, z));
    }
    //求直径部分
    dfs(1, 0, dis[0]);
    dis[0][p] = ans = 0;
    pa = p;
    dfs(p, 0, dis[0]);
    pb = p;
    //求直径部分 pa pb为点，ans为长度
    dfs(pa, 0, dis[1]);
    dfs(pb, 0, dis[2]);
    ans = 0;
    for (int i = 1; i <= n; i++) ans = max(ans, min(dis[1][i], dis[2][i]));
    printf("%lld", ans + dis[0][pb]);
    return 0;
}
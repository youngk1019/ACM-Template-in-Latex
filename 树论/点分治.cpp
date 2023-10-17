//Lougu P3806 【模板】点分治1
// 给定一棵有 n 个点的树，询问树上距离为 k 的点对是否存在, 存在输出AYE，否则输出NAY, 存在边权，有m次询问
#include <bits/stdc++.h>
using namespace std;
#define maxn 100100
#define maxm 10000100 //查询k的范围
int n, m, u, v, w;
int mx[maxn], sz[maxn], rt, S;//S为当前子树的大小
vector<pair<int, int>> e[maxn];
bool vis[maxn];
int dis[maxn], cnt, a[maxn], q[maxn];
bool ans[maxn], check[maxm];
int his[maxn];
void getrt(int u, int fa) { //找重心
    sz[u] = 1, mx[u] = 0;
    for (auto &[v, _]: e[u]) {
        if (v == fa || vis[v])continue;
        getrt(v, u), sz[u] += sz[v], mx[u] = max(mx[u], sz[v]);
    }
    mx[u] = max(mx[u], S - sz[u]);//每次计算一个子树的重心
    if (mx[u] < mx[rt]) rt = u;
}
void getdis(int u, int fa) {
    a[++cnt] = dis[u];
    for (auto &[v, w]: e[u]) {
        if (v == fa || vis[v]) continue;
        dis[v] = dis[u] + w;
        getdis(v, u);
    }
}
// 记忆化有哪些距离，然后拿当前子树的每一个距离查询每一个询问
void calc(int u) {
    int p = 0;
    for (auto &[v, w]: e[u]) {
        if (vis[v]) continue;
        cnt = 0, dis[v] = w;
        getdis(v, u);
        for (int i = 1; i <= cnt; i++) {
            for (int j = 1; j <= m; j++) {
                if (q[j] >= a[i])ans[j] |= check[q[j] - a[i]];
            }
        }
        for (int i = 1; i <= cnt; i++) if(a[i] < maxm) his[++p] = a[i], check[a[i]] = true;
    }
    for (int i = 1; i <= p; i++)check[his[i]] = false;
}
void solve(int u) {
    vis[u] = true, calc(u);
    for (auto &[v, _]: e[u]) {
        if (vis[v])continue;
        S = sz[v], mx[rt = 0] = n;
        getrt(v, 0), solve(rt);
    }
}
signed main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i++) {
        scanf("%d%d%d", &u, &v, &w);
        e[u].emplace_back(v, w), e[v].emplace_back(u, w);
    }
    for (int i = 1; i <= m; i++) scanf("%d", q + i);
    check[0] = true;//距离0为真
    S = n, mx[rt = 0] = n;
    getrt(1, 0); //找到重心
    solve(rt);
    for (int i = 1; i <= m; i++) printf("%s\n", ans[i] ? "AYE" : "NAY");
    return 0;
}
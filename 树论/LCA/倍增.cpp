//P3379 【模板】最近公共祖先（LCA）
//倍增预处理O(nlogn) 查询O(mlogn)
#include <bits/stdc++.h>
using namespace std;
#define maxn 500010
#define maxm 1000010
int n, m, s, x, y, depth[maxn], f[maxn][20], lg[maxn];
int head[maxn], nxt[maxm], to[maxm], cnt;
void add(int u, int v) { nxt[++cnt] = head[u], to[cnt] = v, head[u] = cnt; }
void lcadfs(int u, int fa) {
    depth[u] = depth[fa] + 1, f[u][0] = fa;
    for (int i = 1; (1 << i) <= depth[u]; i++) f[u][i] = f[f[u][i - 1]][i - 1];
    for (int i = head[u]; i; i = nxt[i]) if (to[i] != fa) lcadfs(to[i], u);
}
int lca(int x, int y) {
    if (depth[x] < depth[y]) swap(x, y);
    while (depth[x] > depth[y]) x = f[x][lg[depth[x] - depth[y]] - 1];
    if (x == y) return x;
    for (int i = lg[depth[x]]; i >= 0; i--) {
        if (f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
    }
    return f[x][0];
}
signed main() {
    scanf("%d%d%d", &n, &m, &s);
    for (int i = 1; i <= n; i++) lg[i] = lg[i - 1] + ((1 << lg[i - 1]) == i);
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        add(x, y), add(y, x);
    }
    lcadfs(s, 0);
    while (m--) {
        scanf("%d%d", &x, &y);
        printf("%d\n", lca(x, y));
    }
    return 0;
}
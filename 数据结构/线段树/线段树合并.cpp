//Luogu P4556 [Vani有约会]雨天的尾巴 /【模板】线段树合并
//首先村落里的一共有 n 座房屋，并形成一个树状结构。然后救济粮分 m 次发放，每次选择两个房屋(x, y)，然后对于 x 到 y 的路径上(含 x 和 y)每座房子里发放一袋 z 类型的救济粮。
//然后深绘里想知道，当所有的救济粮发放完毕后，每座房子里存放的最多的是哪种救济粮。
//时间复杂度O(nlogn) 空间复杂度O(nlogn)但要求较大
#include <bits/stdc++.h>
using namespace std;
#define maxn 100010
#define maxm 200010
int n, m, x, y, z, depth[maxn], f[maxn][18], lg[maxn], ans[maxn], L = 1, R = 1e5;
int cnt, head[maxn], nxt[maxm], to[maxm];
struct seqment_tree {
    int cnt, ls[maxn << 6], rs[maxn << 6], mx[maxn << 6], id[maxn << 6], rt[maxn];
    void pushup(int x) {
        if (mx[ls[x]] >= mx[rs[x]]) mx[x] = mx[ls[x]], id[x] = id[ls[x]];
        else mx[x] = mx[rs[x]], id[x] = id[rs[x]];
    }
    void merge(int &a, int b, int l, int r) {//树b合并到树a中
        if (!a || !b) return a = a + b, void();
        if (l == r) return mx[a] = mx[a] + mx[b], id[a] = l, void();
        int mid = (l + r) >> 1;
        merge(ls[a], ls[b], l, mid), merge(rs[a], rs[b], mid + 1, r);
        pushup(a);
    }
    void modify(int &p, int l, int r, int x, int k) {
        if (!p) p = ++cnt;
        if (l == r) return id[p] = l, mx[p] += k, void();
        int mid = (l + r) >> 1;
        if (x <= mid) modify(ls[p], l, mid, x, k);
        else modify(rs[p], mid + 1, r, x, k);
        pushup(p);
    }
} T;
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
void dfs(int u, int fa) {
    for (int i = head[u], v = to[i]; i; i = nxt[i], v = to[i]) {
        if (v == fa) continue;
        dfs(v, u);
        T.merge(T.rt[u], T.rt[v], L, R);
    }
    ans[u] = (T.mx[T.rt[u]] == 0) ? 0 : T.id[T.rt[u]];
}
signed main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) lg[i] = lg[i - 1] + ((1 << lg[i - 1]) == i);
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        add(x, y), add(y, x);
    }
    lcadfs(1, 0);
    while (m--) {
        scanf("%d%d%d", &x, &y, &z);
        int LCA = lca(x, y);
        T.modify(T.rt[x], L, R, z, 1), T.modify(T.rt[y], L, R, z, 1);
        T.modify(T.rt[LCA], L, R, z, -1), T.modify(T.rt[f[LCA][0]], L, R, z, -1);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
    return 0;
}
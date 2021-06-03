//Luogu P3384 【模板】轻重链剖分
//操作1：格式：1 x y z 表示将树从 x 到 y 结点最短路径上所有节点的值都加上 z
//操作2：格式：2 x y 表示求树从 xx 到 yy 结点最短路径上所有节点的值之和
//操作3：格式：3 x z 表示将以 x 为根节点的子树内所有节点值都加上 z
//操作4：格式：4 x 表示求以 x 为根节点的子树内所有节点值之和
#include <bits/stdc++.h>
using namespace std;
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
#define maxn 100100
int n, m, rt, op, x, y, z, a[maxn], b[maxn], mod;
vector<int> e[maxn];
int depth[maxn], f[maxn], sz[maxn], son[maxn], cnt, id[maxn], top[maxn];
struct segment_tree {
    int val[maxn << 2], tagadd[maxn << 2];
    void pushup(int p) { val[p] = (val[ls(p)] + val[rs(p)]) % mod; }
    void calcadd(int p, int l, int r, int add) {
        tagadd[p] = (tagadd[p] + add) % mod;
        val[p] = (val[p] + 1LL * add * (r - l + 1) % mod) % mod;
    }
    void pushdown(int p, int l, int r) {
        if (!tagadd[p]) return;
        int mid = (l + r) >> 1;
        calcadd(ls(p), l, mid, tagadd[p]);
        calcadd(rs(p), mid + 1, r, tagadd[p]);
        tagadd[p] = 0;
    }
    void build(int p, int l, int r) {
        if (l == r) return val[p] = b[l], void();
        int mid = (l + r) >> 1;
        build(ls(p), l, mid), build(rs(p), mid + 1, r);
        pushup(p);
    }
    void update(int p, int nl, int nr, int l, int r, int k) {
        if (nl <= l && r <= nr) {
            val[p] = (val[p] + 1LL * k * (r - l + 1) % mod) % mod;
            tagadd[p] = (tagadd[p] + k) % mod;
            return;
        }
        pushdown(p, l, r);
        int mid = (l + r) >> 1;
        if (nl <= mid) update(ls(p), nl, nr, l, mid, k);
        if (nr > mid) update(rs(p), nl, nr, mid + 1, r, k);
        pushup(p);
    }
    int query(int p, int ql, int qr, int l, int r) {
        if (ql <= l && r <= qr) return val[p];
        int ret = 0, mid = (l + r) >> 1;
        pushdown(p, l, r);
        if (ql <= mid) ret = (ret + query(ls(p), ql, qr, l, mid)) % mod;
        if (qr > mid) ret = (ret + query(rs(p), ql, qr, mid + 1, r)) % mod;
        return ret;
    }
} T;
void dfs1(int u, int fa) {
    depth[u] = depth[fa] + 1, f[u] = fa, sz[u] = 1;
    int mx = 0;
    for (auto &v:e[u]) {
        if (v == fa) continue;
        dfs1(v, u);
        sz[u] += sz[v];
        if (sz[v] > mx) son[u] = v, mx = sz[v];
    }
}
void dfs2(int u, int topf) {
    id[u] = ++cnt, b[cnt] = a[u], top[u] = topf;
    if (!son[u]) return;
    dfs2(son[u], topf);
    for (auto &v:e[u]) {
        if (v == f[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}
int query_range(int x, int y) {
    int ret = 0;
    while (top[x] != top[y]) {
        if (depth[top[x]] < depth[top[y]]) swap(x, y);
        ret = (ret + T.query(1, id[top[x]], id[x], 1, n)) % mod;
        x = f[top[x]];
    }
    if (depth[x] > depth[y]) swap(x, y);
    return (ret + T.query(1, id[x], id[y], 1, n)) % mod;
}
void update_range(int x, int y, int k) {
    k %= mod;
    while (top[x] != top[y]) {
        if (depth[top[x]] < depth[top[y]]) swap(x, y);
        T.update(1, id[top[x]], id[x], 1, n, k);
        x = f[top[x]];
    }
    if (depth[x] > depth[y]) swap(x, y);
    T.update(1, id[x], id[y], 1, n, k);
}
int query_son(int x) {
    return T.query(1, id[x], id[x] + sz[x] - 1, 1, n);
}
void update_son(int x, int k) {
    T.update(1, id[x], id[x] + sz[x] - 1, 1, n, k % mod);
}
signed main() {
    scanf("%d%d%d%d", &n, &m, &rt, &mod);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    T.build(1, 1, n);
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        e[x].push_back(y), e[y].push_back(x);
    }
    dfs1(rt, 0), dfs2(rt, rt), T.build(1, 1, n);
    while (m--) {
        scanf("%d", &op);
        if (op == 1) scanf("%d%d%d", &x, &y, &z), update_range(x, y, z);
        else if (op == 2)scanf("%d%d", &x, &y), printf("%d\n", query_range(x, y));
        else if (op == 3) scanf("%d%d", &x, &z), update_son(x, z);
        else if (op == 4) scanf("%d", &x), printf("%d\n", query_son(x));
    }
    return 0;
}
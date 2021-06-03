//Luogu P4074 [WC2013] 糖果公园
//树上 u,v之间的路径上的结点的不同颜色数
//树上莫队，欧拉序跑莫队，长度(vis)为2*n，访问过两次的节点不算
//如果u,v不在同一个子树需要单独算上lca(实际填入st[lca])，从ed->st 否则不算lca，从st->st
//第i种糖果美味值为V[i] 第j次吃提供贡献为V[i]*W[j]
//查询1:0 x y 将x的旅游点的糖果改为y
//查询2:1 x y x到y路径上的愉悦指数
//复杂度O(n^(5/3))
#include <bits/stdc++.h>
using namespace std;
#define maxn 100010
#define maxm 200010
int n, m, q, op, x, y, depth[maxn], f[maxn][20], lg[maxn];
int head[maxn], nxt[maxm], to[maxm], _cnt;
int block, a[maxn], dft, st[maxn], ed[maxn], vis[maxn << 1], cnt[maxn], tot, tim, W[maxn], V[maxn];
long long ans, _ans[maxn];
bool used[maxn];
struct query {
    int l, r, pos, lca, time;
} b[maxn];
struct change {
    int pos, val;//pos是位置下标,不是欧拉序
} c[maxn];
bool cmp(query x, query y) {
    if (x.l / block != y.l / block) return x.l / block < y.l / block;
    if (x.r / block != y.r / block) {
        if ((x.l / block) & 1) return x.r / block < y.r / block;
        else return x.r / block > y.r / block;
    }
    return x.time < y.time;
}
void add(int u, int v) { nxt[++_cnt] = head[u], to[_cnt] = v, head[u] = _cnt; }
void dfs(int u, int fa) {
    st[u] = ++dft, vis[dft] = u;
    depth[u] = depth[fa] + 1, f[u][0] = fa;
    for (int i = 1; (1 << i) <= depth[u]; i++) f[u][i] = f[f[u][i - 1]][i - 1];
    for (int i = head[u]; i; i = nxt[i]) if (to[i] != fa) dfs(to[i], u);
    ed[u] = ++dft, vis[dft] = u;
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
void add(int x) {
    if (used[x = vis[x]]) ans -= 1LL * W[(cnt[a[x]]--)] * V[a[x]];
    else ans += 1LL * W[(++cnt[a[x]])] * V[a[x]];
    used[x] ^= true;
}
signed main() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++) lg[i] = lg[i - 1] + ((1 << lg[i - 1]) == i);
    for (int i = 1; i <= m; i++) scanf("%d", V + i);
    for (int i = 1; i <= n; i++) scanf("%d", W + i);
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        add(x, y), add(y, x);
    }
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    dfs(1, 0);
    block = pow(2 * n, 2.0 / 3.0);
    while (q--) {
        scanf("%d%d%d", &op, &x, &y);
        if (op == 1) {
            tot++;
            if (st[x] > st[y]) swap(x, y);
            b[tot].pos = tot, b[tot].lca = lca(x, y), b[tot].time = tim;
            if (b[tot].lca == x) b[tot].l = st[x], b[tot].r = st[y], b[tot].lca = 0;
            else b[tot].l = ed[x], b[tot].r = st[y], b[tot].lca = st[b[tot].lca];
        } else {
            tim++;
            c[tim].pos = x, c[tim].val = y;
        }
    }
    sort(b + 1, b + tot + 1, cmp);
    for (int i = 1, ll, rr, tt, p, l = 1, r = 0, t = 0; i <= tot; i++) {
        ll = b[i].l, rr = b[i].r, tt = b[i].time;
        while (l < ll) add(l++);
        while (l > ll) add(--l);
        while (r < rr) add(++r);
        while (r > rr) add(r--);
        while (tt < t) {
            p = c[t].pos;
            if (used[p]) add(st[p]), swap(a[p], c[t].val), add(st[p]);
            else swap(a[p], c[t].val);
            t--;
        }
        while (tt > t) {
            p = c[++t].pos;
            if (used[p]) add(st[p]), swap(a[p], c[t].val), add(st[p]);
            else swap(a[p], c[t].val);
        }
        if (b[i].lca) add(b[i].lca);
        _ans[b[i].pos] = ans;
        if (b[i].lca) add(b[i].lca);
    }
    for (int i = 1; i <= tot; i++)printf("%lld\n", _ans[i]);
    return 0;
}
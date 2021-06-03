//SP10707 COT2 - Count on a tree II
//树上 u,v之间的路径上的结点的不同颜色数
//树上莫队，欧拉序跑莫队，长度(vis)为2*n，访问过两次的节点不算
//如果u,v不在同一个子树需要单独算上lca(实际填入st[lca])，从ed->st 否则不算lca，从st->st
//原题数据勘误n <= 100000
#include <bits/stdc++.h>
using namespace std;
#define maxn 100010
#define maxm 200010
int n, m, x, y, depth[maxn], f[maxn][20], lg[maxn];
int head[maxn], nxt[maxm], to[maxm], cnt;
vector<int> v;
int block, a[maxn], dft, st[maxn], ed[maxn], vis[maxn << 1], c[maxn], ans, _ans[maxn];
bool used[maxn];
struct node {
    int l, r, id, pos, lca;
} b[maxn];
bool cmp(node x, node y) {
    if (x.id == y.id) {
        if (x.id & 1) return x.r < y.r;
        else return x.r > y.r;
    } else return x.l < y.l;
}
void add(int u, int v) { nxt[++cnt] = head[u], to[cnt] = v, head[u] = cnt; }
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
    if (used[x = vis[x]]) ans -= (--c[a[x]] == 0);
    else ans += (++c[a[x]] == 1);
    used[x] ^= true;
}
signed main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) lg[i] = lg[i - 1] + ((1 << lg[i - 1]) == i);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), v.push_back(a[i]);
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    for (int i = 1; i <= n; i++) a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin();
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        add(x, y), add(y, x);
    }
    dfs(1, 0);
    block = sqrt(2 * n);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        if (st[x] > st[y]) swap(x, y);
        b[i].pos = i, b[i].lca = lca(x, y);
        if (b[i].lca == x) b[i].l = st[x], b[i].r = st[y], b[i].id = b[i].l / block, b[i].lca = 0;
        else b[i].l = ed[x], b[i].r = st[y], b[i].id = b[i].l / block, b[i].lca = st[b[i].lca];
    }
    sort(b + 1, b + m + 1, cmp);
    for (int i = 1, ll, rr, l = 1, r = 0; i <= m; i++) {
        ll = b[i].l, rr = b[i].r;
        while (l < ll) add(l++);
        while (l > ll) add(--l);
        while (r < rr) add(++r);
        while (r > rr) add(r--);
        if (b[i].lca) add(b[i].lca);
        _ans[b[i].pos] = ans;
        if (b[i].lca) add(b[i].lca);
    }
    for (int i = 1; i <= m; i++)printf("%d\n", _ans[i]);
    return 0;
}
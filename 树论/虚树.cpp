//Luogu P2495 [SDOI2011]消耗战
#include <bits/stdc++.h>
using namespace std;
#define maxn 250100
#define maxm 500100
#define inf 0x3f3f3f3f3f3f3f3f
int n, t, m, x, y, z, depth[maxn], f[maxn][20], lg[maxn], dfn[maxn], dfu, q[maxn];
long long mn[maxn];
bool query[maxn];
int head[maxn], nxt[maxm], to[maxm], val[maxm], cnt;
void add(int u, int v, int w) { nxt[++cnt] = head[u], to[cnt] = v, val[cnt] = w, head[u] = cnt; }
void dfs(int u, int fa) {
    dfn[u] = ++dfu, depth[u] = depth[fa] + 1, f[u][0] = fa;
    for (int i = 1; (1 << i) <= depth[u]; i++) f[u][i] = f[f[u][i - 1]][i - 1];
    for (int i = head[u]; i; i = nxt[i]) if (to[i] != fa) mn[to[i]] = min(mn[u], 1LL * val[i]), dfs(to[i], u);
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
vector<int> e[maxn];
int st[maxn], top;
void push(int u) {
    int LCA = lca(u, st[top]);
    if (LCA == st[top]) return st[++top] = u, void();
    while (dfn[st[top - 1]] > dfn[LCA]) e[st[top - 1]].push_back(st[top]), top--;
    if (dfn[LCA] > dfn[st[top - 1]]) e[LCA].push_back(st[top]), st[top] = LCA;
    else e[st[top - 1]].push_back(st[top]), top--;
    st[++top] = u;
}
long long dp(int u) {
    long long ret = 0;
    for (auto &v:e[u]) ret += dp(v);
    e[u].clear();
    if (query[u]) return query[u] = false, mn[u];
    return min(mn[u], ret);
}
signed main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) lg[i] = lg[i - 1] + ((1 << lg[i - 1]) == i);
    for (int i = 1; i < n; i++) {
        scanf("%d%d%d", &x, &y, &z);
        add(x, y, z), add(y, x, z);
    }
    mn[1] = inf, dfs(1, 0);
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &m);
        for (int i = 1; i <= m; i++) scanf("%d", q + i), query[q[i]] = true;
        sort(q + 1, q + m + 1, [&](int &x, int &y) { return dfn[x] < dfn[y]; });
        st[top = 1] = 1;
        for (int i = 1; i <= m; i++) push(q[i]);
        while (top > 0) e[st[top - 1]].push_back(st[top]), top--;
        printf("%lld\n", dp(1));
    }
    return 0;
}
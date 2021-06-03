//Luogu P4897 【模板】最小割树（Gomory-Hu Tree）
//Gomory-Hu Tree
#include <bits/stdc++.h>
using namespace std;
#define maxn 510
#define maxm 6010 //四倍的边长
#define maxlog 10
#define inf 0x3f3f3f3f
struct dinic {
    int cnt = 1, head[maxn], to[maxm], w[maxm], nxt[maxm], h[maxn];
    int s, t, dis[maxn], cur[maxn], maxflow;
    void init(int _s, int _t) {
        s = _s, t = _t;
        for (int i = 2; i <= cnt; i += 2) w[i] += w[i ^ 1], w[i ^ 1] = 0;
        memcpy(head, h, sizeof(head));
    }
    void _add(int u, int v, int x) {
        to[++cnt] = v, w[cnt] = x, nxt[cnt] = h[u], h[u] = head[u] = cnt;
    }
    void add(int u, int v, int x) {
        _add(u, v, x), _add(v, u, 0);
    }
    bool bfs() {
        queue<int> q;
        memset(dis, 0, sizeof(dis));
        memcpy(cur, head, sizeof(head));
        dis[s] = 1, q.push(s);
        while (q.size()) {
            int u = q.front();
            q.pop();
            for (int i = head[u], v = to[i]; i; i = nxt[i], v = to[i]) {
                if (!dis[v] && w[i]) dis[v] = dis[u] + 1, q.push(v);
            }
        }
        return dis[t] != 0;
    }
    int dfs(int u, int flow) {
        if (u == t) return flow;
        int rlow, used = 0;
        for (int i = cur[u], v = to[i]; i; i = nxt[i], v = to[i]) {
            cur[u] = i;
            if (w[i] && dis[v] == dis[u] + 1 && (rlow = dfs(v, min(w[i], flow - used)))) {
                used += rlow, w[i] -= rlow, w[i ^ 1] += rlow;
                if (used == flow) break;
            }
        }
        return used;
    }
    int solve(int s, int t) {
        init(s, t);
        maxflow = 0;
        while (bfs()) maxflow += dfs(s, INT_MAX);
        return maxflow;
    }
};
struct mincut_tree {
    dinic D;
    int cnt, head[maxn], to[maxm], w[maxm], nxt[maxm];
    int n, node[maxn], lg[maxn];
    void _add(int u, int v, int x) {
        to[++cnt] = v, w[cnt] = x, nxt[cnt] = head[u], head[u] = cnt;
    }
    void add(int u, int v, int x) {
        _add(u, v, x), _add(v, u, x);
    }
    int tmp1[maxn], tmp2[maxn];
    void build(int l, int r) {
        if (l >= r) return;
        int s = node[l], t = node[l + 1], cut = D.solve(s, t);
        add(s, t, cut);
        int cnt1 = 0, cnt2 = 0;
        for (int i = l; i <= r; i++) {
            if (D.dis[node[i]]) tmp1[++cnt1] = node[i];
            else tmp2[++cnt2] = node[i];
        }
        for (int i = l; i <= l + cnt1 - 1; i++) node[i] = tmp1[i - l + 1];
        for (int i = l + cnt1; i <= r; i++) node[i] = tmp2[i - cnt1 - l + 1];
        build(l, l + cnt1 - 1), build(l + cnt1, r);
    }
    int depth[maxn], f[maxn][maxlog], mn[maxn][maxlog];
    void dfs(int u, int fa) {
        depth[u] = depth[fa] + 1;
        for (int i = 1; (1 << i) <= depth[u]; i++) {
            f[u][i] = f[f[u][i - 1]][i - 1];
            mn[u][i] = min(mn[u][i - 1], mn[f[u][i - 1]][i - 1]);
        }
        for (int i = head[u], v = to[i]; i; i = nxt[i], v = to[i]) {
            if (v == fa) continue;
            f[v][0] = u, mn[v][0] = w[i], dfs(v, u);
        }
    }
    void solve(int _n) {
        n = _n;
        for (int i = 1; i <= n; i++) node[i] = i, lg[i] = lg[i - 1] + ((1 << lg[i - 1]) == i);
        build(1, n), dfs(1, 0);
    }
    int query(int x, int y) {//x == y return inf
        int ans = inf;
        if (depth[x] < depth[y]) swap(x, y);
        while (depth[x] > depth[y]) {
            ans = min(ans, mn[x][lg[depth[x] - depth[y]] - 1]);
            x = f[x][lg[depth[x] - depth[y]] - 1];
        }
        if (x == y) return ans;
        for (int i = lg[depth[x]]; i >= 0; i--) {
            if (f[x][i] != f[y][i]) ans = min({ans, mn[x][i], mn[y][i]}), x = f[x][i], y = f[y][i];
        }
        return min({ans, mn[y][0], mn[x][0]});
    }
} T;
int n, m, q, x, y, z;
signed main() {
    scanf("%d%d", &n, &m);
    while (m--) {
        scanf("%d%d%d", &x, &y, &z);
        T.D.add(x, y, z), T.D.add(y, x, z);
    }
    T.solve(n);
    scanf("%d", &q);
    while (q--) {
        scanf("%d%d", &x, &y);
        printf("%d\n", T.query(x, y));
    }
    return 0;
}
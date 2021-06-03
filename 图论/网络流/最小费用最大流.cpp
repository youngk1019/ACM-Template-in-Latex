//P3381 【模板】最小费用最大流
#include <bits/stdc++.h>
using namespace std;
#define maxn 5100
#define maxm 100100
#define inf 0x3f3f3f3f
struct mcmf {
    int cnt = 1, head[maxn], to[maxm], w[maxm], val[maxm], nxt[maxm];
    int n, s, t, maxflow, cost, dis[maxn];
    bool vis[maxn];
    void init(int _n) {
        n = _n, s = maxn - 1, t = maxn - 2, cnt = 1;
        memset(head + 1, 0, n * sizeof(int));
    }
    void init(int _n, int _s, int _t) {
        n = _n, s = _s, t = _t, cnt = 1;
        memset(head + 1, 0, n * sizeof(int));
    }
    void _add(int u, int v, int x, int y) {
        to[++cnt] = v, w[cnt] = x, val[cnt] = y, nxt[cnt] = head[u], head[u] = cnt;
    }
    void add(int u, int v, int x, int y) {
        _add(u, v, x, y), _add(v, u, 0, -y);
    }
    bool spfa() {
        queue<int> q;
        memset(vis, 0, sizeof(vis));
        memset(dis, 0x3f, sizeof(dis));
        dis[s] = 0, q.push(s);
        while (q.size()) {
            int u = q.front();
            q.pop();
            vis[u] = false;
            for (int i = head[u], v = to[i]; i; i = nxt[i], v = to[i]) {
                if (dis[v] > dis[u] + val[i] && w[i]) {
                    dis[v] = dis[u] + val[i];
                    if (!vis[v]) q.push(v), vis[v] = true;
                }
            }
        }
        return dis[t] != inf;
    }
    int dfs(int u, int flow) {
        if (u == t) return flow;
        int used = 0;
        vis[u] = true;
        for (int i = head[u], v = to[i]; i; i = nxt[i], v = to[i]) {
            if ((!vis[v] || v == t) && w[i] && dis[v] == dis[u] + val[i]) {
                int minflow = dfs(v, min(flow - used, w[i]));
                if (minflow) {
                    cost += val[i] * minflow, w[i] -= minflow, w[i ^ 1] += minflow, used += minflow;
                    if (used == flow) break;
                }
            }
        }
        return used;
    }
    void solve() {
        while (spfa()) {
            vis[t] = true;
            while (vis[t]) {
                memset(vis, 0, sizeof(vis));
                maxflow += dfs(s, INT_MAX);
            }
        }
    }
} T;
int n, m, s, t, u, v, w, c;
signed main() {
    scanf("%d%d%d%d", &n, &m, &s, &t);
    T.init(n, s, t);
    while (m--) {
        scanf("%d%d%d%d", &u, &v, &w, &c);
        T.add(u, v, w, c);
    }
    T.solve();
    printf("%d %d", T.maxflow, T.cost);
    return 0;
}
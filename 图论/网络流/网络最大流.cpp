//Luogu P3376 【模板】网络最大流
//dinic O(n^2m)
#include <bits/stdc++.h>
using namespace std;
#define maxn 210
#define maxm 10100
#define inf 0x3f3f3f3f
struct dinic {
    int cnt = 1, head[maxn], to[maxm], w[maxm], nxt[maxm];
    int n, s, t, dis[maxn], cur[maxn];
    long long maxflow;
    void init(int _n) {
        n = _n, s = maxn - 1, t = maxn - 2, cnt = 1;
        memset(head + 1, 0, n * sizeof(int));
    }
    void init(int _n, int _s, int _t) {
        n = _n, s = _s, t = _t, cnt = 1;
        memset(head + 1, 0, n * sizeof(int));
    }
    void _add(int u, int v, int x) {
        to[++cnt] = v, w[cnt] = x, nxt[cnt] = head[u], head[u] = cnt;
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
    void solve() {
        maxflow = 0;
        while (bfs()) maxflow += dfs(s, INT_MAX);
    }
} T;
int n, m, s, t, x, y, z;
signed main() {
    scanf("%d%d%d%d", &n, &m, &s, &t);
    T.init(n, s, t);
    while (m--) {
        scanf("%d%d%d", &x, &y, &z);
        T.add(x, y, z);
    }
    T.solve();
    printf("%lld", T.maxflow);
    return 0;
}
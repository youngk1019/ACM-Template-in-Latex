//P3381 【模板】最小费用最大流
#include <bits/stdc++.h>
using namespace std;
#define maxn 5100
#define maxm 100100
#define inf 0x3f3f3f3f
struct dijkstra_mcmf {
    int cnt = 1, head[maxn], to[maxm], val[maxm], w[maxm], nxt[maxm];
    int n, s, t, maxflow, cost, dis[maxn], h[maxn], last[maxn], ledge[maxn];
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
    void init(int _n) {
        n = _n, s = maxn - 1, t = maxn - 2, cnt = 1;
        memset(head + 1, 0, n * sizeof(int));
    }
    void init(int _n, int _s, int _t) {
        n = _n, s = _s, t = _t, cnt = 1;
        memset(head + 1, 0, n * sizeof(int));
    }
    void _add(int u, int v, int x, int y) {
        to[++cnt] = v, val[cnt] = x, w[cnt] = y, nxt[cnt] = head[u], head[u] = cnt;
    }
    void add(int u, int v, int x, int y) {
        _add(u, v, x, y), _add(v, u, 0, -y);
    }
    bool dijkstra() {
        for (int i = 1; i <= n; i++) h[i] += dis[i];
        memset(dis + 1, 0x3f, n * sizeof(int));
        dis[s] = 0, dis[t] = inf;
        q.push(make_pair(0, s));
        while (q.size()) {
            auto[W, u] =q.top();
            q.pop();
            if (W > dis[u]) continue;
            for (int i = head[u], v = to[i]; i; i = nxt[i], v = to[i]) {
                if (val[i] && dis[v] > dis[u] + w[i] + h[u] - h[v]) {
                    dis[v] = dis[u] + w[i] + h[u] - h[v], last[v] = u, ledge[v] = i;
                    q.push(make_pair(dis[v], v));
                }
            }
        }
        return dis[t] != inf;
    }
    void solve() {
        memset(dis + 1, 0, n * sizeof(int));
        memset(h + 1, 0, n * sizeof(int));
        h[s] = h[t] = maxflow = cost = 0;
        while (dijkstra()) {
            int f = inf, k = 0;
            for (int i = t; i != s; i = last[i]) f = min(f, val[ledge[i]]), k += w[ledge[i]];
            maxflow += f, cost += k * f;
            for (int i = t; i != s; i = last[i]) val[ledge[i]] -= f, val[ledge[i] ^ 1] += f;
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
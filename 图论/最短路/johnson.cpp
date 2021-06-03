//Luogu P5905 【模板】Johnson 全源最短路
//无边长度为1e9
#include <bits/stdc++.h>
using namespace std;
#define maxn 3100
#define inf 0x3f3f3f3f
const int INF = 1e9;
int n, m, x, y, w, dis[maxn], h[maxn], cnt[maxn];
vector<pair<int, int> > e[maxn];
bool vis[maxn];
bool spfa(int s) {
    queue<int> q;
    memset(h, 0x3f, sizeof(h));
    h[s] = 0, vis[s] = true, q.push(s);
    while (q.size()) {
        auto u = q.front();
        q.pop();
        vis[u] = false;
        for (auto &[v, w]:e[u]) {
            if (h[v] > h[u] + w) {
                h[v] = h[u] + w;
                if (vis[v] == false) {
                    vis[v] = true;
                    cnt[v]++;
                    if (cnt[v] == n) return false;
                    q.push(v);
                }
            }
        }
    }
    return true;
}
void dijkstra(int s) {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0, q.emplace(0, s);
    while (q.size()) {
        auto[W, u] = q.top();
        q.pop();
        if (W > dis[u]) continue;
        for (auto &[v, w]:e[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                q.emplace(dis[v], v);
            }
        }
    }
}
signed main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) e[0].emplace_back(i, 0);
    while (m--) {
        scanf("%d%d%d", &x, &y, &w);
        e[x].emplace_back(y, w);
    }
    if (!spfa(0)) return puts("-1"), 0;
    for (int i = 1; i <= n; i++) {
        for (auto &[v, w]:e[i]) w += h[i] - h[v];
    }
    for (int i = 1; i <= n; i++) {
        dijkstra(i);
        long long ans = 0;
        for (int j = 1; j <= n; j++) {
            if (dis[j] == inf) ans += 1LL * INF * j;
            else ans += 1LL * (dis[j] - h[i] + h[j]) * j;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
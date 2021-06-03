//Luogu P4779 【模板】单源最短路径（标准版）
//dijkstra
#include <bits/stdc++.h>
using namespace std;
#define maxn 100100
#define inf 0x3f3f3f3f
int n, m, s, x, y, w, dis[maxn];
vector<pair<int, int> > e[maxn];
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
    scanf("%d%d%d", &n, &m, &s);
    while (m--) {
        scanf("%d%d%d", &x, &y, &w);
        e[x].emplace_back(y, w);
    }
    dijkstra(s);
    for (int i = 1; i <= n; i++) printf("%d ", dis[i]);
    return 0;
}
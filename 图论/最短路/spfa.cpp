//Luogu P3371 【模板】单源最短路径（弱化版）
//spfa
#include <bits/stdc++.h>
using namespace std;
#define maxn 10100
int n, m, s, x, y, w, dis[maxn];
vector<pair<int, int> > e[maxn];
bool vis[maxn];
void spfa(int s) {
    queue<int> q;
    fill(dis + 1, dis + n + 1, INT_MAX);//不建议直接设置成INT_MAX，这题输出无法到达为INT_MAX
    dis[s] = 0, q.emplace(s);
    while (q.size()) {
        auto u = q.front();
        q.pop();
        vis[u] = false;
        for (auto &[v, w]:e[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                if (vis[v] == false) vis[v] = true, q.emplace(v);
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
    spfa(s);
    for (int i = 1; i <= n; i++) printf("%d ", dis[i]);
    return 0;
}
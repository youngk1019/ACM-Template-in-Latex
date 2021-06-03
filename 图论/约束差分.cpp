//Luogu P5960 【模板】差分约束算法
//连边方式 x - y <= w。
#include <bits/stdc++.h>
using namespace std;
#define maxn 5010
int n, m, x, y, w, cnt[maxn], dis[maxn];
bool vis[maxn];
vector<pair<int, int> > e[maxn];
bool spfa(int s) {
    queue<int> q;
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0, vis[s] = true, q.push(s);
    while (q.size()) {
        auto u = q.front();
        q.pop();
        vis[u] = false;
        for (auto &[v, w]:e[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
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
signed main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) e[0].emplace_back(i, 0);
    while (m--) {
        scanf("%d%d%d", &x, &y, &w);
        e[y].emplace_back(x, w);
    }
    if (!spfa(0)) puts("NO");
    else for (int i = 1; i <= n; i++) printf("%d ", dis[i]);
    return 0;
}
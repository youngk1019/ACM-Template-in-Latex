//Luogu P6699 【模板】一般图最大权匹配
//第二行输出匹配结果 如果未匹配则输出0
#include <bits/stdc++.h>
using namespace std;
#define maxn 410
int e[maxn][maxn], dis[maxn], match[maxn];
bool vis[maxn];
int sta[maxn], top;//堆栈
int n, m, x, y, z;
bool dfs(int u) {
    sta[top++] = u;
    if (vis[u]) return true;
    vis[u] = true;
    for (int i = 1; i <= n; i++)
        if (i != u && i != match[u] && !vis[i]) {
            int t = match[i];
            if (dis[t] < dis[u] + e[u][i] - e[i][t]) {
                dis[t] = dis[u] + e[u][i] - e[i][t];
                if (dfs(t)) return true;
            }
        }
    top--;
    vis[u] = false;
    return false;
}
int P[maxn];
//返回最大匹配权值
long long get_match() {
    for (int i = 1; i <= n; i++) P[i] = i;
    for (int i = 1; i <= n; i += 2) match[i] = i + 1, match[i + 1] = i;
    int cnt = 0;
    while (true) {
        memset(dis, 0, sizeof(dis));
        memset(vis, false, sizeof(vis));
        top = 0;
        bool update = false;
        for (int i = 1; i <= n; i++)
            if (dfs(P[i])) {
                update = true;
                int tmp = match[sta[top - 1]];
                int j = top - 2;
                while (sta[j] != sta[top - 1]) match[tmp] = sta[j], swap(tmp, match[sta[j--]]);
                match[tmp] = sta[j], match[sta[j]] = tmp;
                break;
            }
        if (!update) {
            if (++cnt >= 3) break;
            random_shuffle(P + 1, P + n + 1);
        }
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        if (i < match[i]) ans += e[i][match[i]];
    }
    return ans;
}
signed main() {
    scanf("%d%d", &n, &m);
    while (m--) {
        scanf("%d%d%d", &x, &y, &z);
        e[x][y] = e[y][x] = max(e[x][y], z);
    }
    printf("%lld\n", get_match());
    for (int i = 1; i <= n; i++)printf("%d ", e[i][match[i]] == 0 ? 0 : match[i]);
}
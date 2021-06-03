//Luogu P3386 【模板】二分图最大匹配
//匈牙利算法 左部n个点 右部m个点 复杂度O(n*E+m)
#include<bits/stdc++.h>
using namespace std;
#define maxn 510
int n, m, E, x, y, match[maxn];
vector<int> e[maxn];
bool vis[maxn];
bool find(int u) {
    for (auto &v:e[u]) {
        if (!vis[v]) {
            vis[v] = true;
            if (!match[v] || find(match[v])) return match[v] = u, true;
        }
    }
    return false;
}
int Hungarian() {
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        memset(vis, 0, sizeof(vis));
        ans += find(i);
    }
    return ans;
}
signed main() {
    scanf("%d%d%d", &n, &m, &E);
    while (E--) {
        scanf("%d%d", &x, &y);
        e[x].push_back(y);
    }
    printf("%d", Hungarian());
    return 0;
}
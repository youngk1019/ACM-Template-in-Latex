//codeforces CF600E Lomsat gelral
//复杂度O(nlogn) (实际用map复杂度O(nlognlogn))
#include <bits/stdc++.h>
using namespace std;
#define maxn 250100
int n, x, y, a[maxn], mx[maxn];
long long ans[maxn];
vector<int> e[maxn];
map<int, int> mp[maxn];
void merge(int x, int y) {
    if (mp[x].size() < mp[y].size()) swap(mp[x], mp[y]), mx[x] = mx[y], ans[x] = ans[y];
    for (auto &[u, v]:mp[y]) {
        mp[x][u] += v, v = mp[x][u];
        if (v > mx[x]) mx[x] = v, ans[x] = 0;
        if (v == mx[x]) ans[x] += u;
    }
}
void dfs(int u, int fa) {
    mx[u] = 1, ans[u] = a[u], mp[u][a[u]] = 1;
    for (auto &v:e[u]) {
        if (v == fa)continue;
        dfs(v, u);
        merge(u, v);
    }
}
signed main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        e[x].push_back(y), e[y].push_back(x);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++)printf("%lld ", ans[i]);
    return 0;
}
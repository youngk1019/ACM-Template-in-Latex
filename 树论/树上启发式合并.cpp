//codeforces CF600E Lomsat gelral
//复杂度O(nlogn) (实际用map复杂度O(nlognlogn))
// 有一棵 n 个结点的以 1 号结点为根的有根树。每个结点都有一个颜色，颜色是以编号表示的， i 号结点的颜色编号为 c_{i}。
// 如果一种颜色在以 x 为根的子树内出现次数最多，称其在以 x 为根的子树中占主导地位。显然，同一子树中可能有多种颜色占主导地位。
// 你的任务是对于每一个 i ∈ [1,n]，求出以 i 为根的子树中，占主导地位的颜色的编号和。
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
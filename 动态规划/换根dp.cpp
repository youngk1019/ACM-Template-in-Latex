//codeforces CF1187E Tree Painting
//给定一棵n个点的树 初始全是白点
//要求你做n步操作，每一次选定一个与一个黑点相隔一条边的白点，将它染成黑点，然后获得该白点被染色前所在的白色联通块大小的权值
//第一次操作可以任意选点
//求可获得的最大权值
//dp为总贡献, f为子贡献
// dp[y] = n + (n - size_y) + sum_{i in son_x && i != y}f[i] + sum_{i in son_y}f[i] 
// = n + (n - size_y) + sum_{i in son_x && i != y}f[i] + f[y] - size_y
// = dp[x] + n - 2 * size_y
// 第一次dfs计算出当1为根的dp结果，和中间变量
// 第二次dfs先考虑计算所有的完整的中间变量的状态，然后变成从v为根的状态的中间变量，然后减去从v->u的代价 加上从u->v的代价
#include <bits/stdc++.h>
using namespace std;
#define maxn 200100
int n, x, y, size[maxn];
long long dp[maxn];
vector<int> e[maxn];
long long dfs1(int u, int fa) {
    long long ret = 0;
    size[u] = 1;
    for (auto &v:e[u]) {
        if (v == fa)continue;
        ret += dfs1(v, u), size[u] += size[v];
    }
    return ret + size[u];
}
void dfs2(int u, int fa) {
    for (auto &v:e[u]) {
        if (v == fa)continue;
        dp[v] = dp[u] + n - 2 * size[v];
        dfs2(v, u);
    }
}
signed main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        e[x].push_back(y), e[y].push_back(x);
    }
    dp[1] = dfs1(1, 0);
    dfs2(1, 0);
    printf("%lld", *max_element(dp + 1, dp + n + 1));
    return 0;
}
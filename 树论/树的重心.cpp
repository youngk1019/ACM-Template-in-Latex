//Luogu P1395 会议
//树的重心和其他所有点到该点距离和 提供两种算法，也可以直接找到最小距离和找到重心
// 树中所有点到某个点的距离和中，到重心的距离和是最小的，如果有两个重心，他们的距离和一样。
// 把两棵树通过一条边相连，新的树的重心在原来两棵树重心的连线上。
// 一棵树添加或者删除一个节点，树的重心最多只移动一条边的位置。
// 一棵树最多有两个重心，且相邻。
// 树的重心, 其所有的子树中最大的子树节点数最少.
#include <bits/stdc++.h>
using namespace std;
#define maxn 50100
int n, x, y;
vector<int> e[maxn];
int size[maxn], weight[maxn], sum[maxn], centroid[2]; // 用于记录树的重心（存的是节点编号）
int dfs(int u, int fa) {
    int sum = 0;
    size[u] = 1, weight[u] = 0;
    for (auto &v:e[u]) {
        if (v == fa)continue;
        sum += dfs(v, u), size[u] += size[v], weight[u] = max(weight[u], size[v]);
    }
    weight[u] = max(weight[u], n - size[u]);
    if (weight[u] <= n / 2) centroid[centroid[0] != 0] = u;
    return sum + size[u] - 1;
}
void calc(int u, int fa) {
    for (auto &v:e[u]) {
        if (v == fa) continue;
        sum[v] = sum[u] + n - 2 * size[v], calc(v, u);
    }
}
signed main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        e[x].push_back(y), e[y].push_back(x);
    }
    sum[1] = dfs(1, 0);
    calc(1, 0);
    printf("%d %d", centroid[1] != 0 ? min(centroid[0], centroid[1]) : centroid[0],sum[centroid[0]]);
    return 0;
}
//Luogu P1395 会议
//树的重心和其他所有点到该点距离和 提供两种算法，也可以直接找到最小距离和找到重心
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
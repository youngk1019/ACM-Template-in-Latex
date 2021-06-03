//Lougu P6178 【模板】Matrix-Tree 定理
//A为邻接矩阵，D为度数矩阵（D[i][i] = 节点i的度数，其余为0）
//基尔霍夫矩阵K = D - A, K'为K的n-1阶主子式
//det(K')为该图生成树的个数
//带权则变为A变为权值和，D变为相邻边的权值和
//有向图：
//外向树（从根向外） D[i][i] = \sum{A[j][i]}
//内向树（从外向根） D[i][i] = \sum{A[i][j]}
#include <bits/stdc++.h>
using namespace std;
#define maxn 310
const int mod = 1e9 + 7;
int n, m, t, u, v, w, a[maxn][maxn];
int qpow(int a, int b) {
    int ret = 1;
    while (b) {
        if (b & 1)ret = 1LL * a * ret % mod;
        a = 1LL * a * a % mod, b >>= 1;
    }
    return ret;
}
//有向图以u为根
int det(int u) {
    int ret = 1;
    bool tr = false;
    for (int i = 1; i <= n; i++) {
        if (i == u) continue;
        int mx = i;
        for (int j = i + 1; j <= n; j++) {
            if (a[j][i] && j != u) {
                mx = j;
                break;
            }
        }
        if (mx != i) {
            for (int j = i; j <= n; j++)swap(a[i][j], a[mx][j]);
            tr ^= true;
        }
        if (a[i][i] == 0) return 0;
        ret = 1LL * ret * a[i][i] % mod;
        int inv = qpow(a[i][i], mod - 2);
        for (int j = i + 1; j <= n; j++) {
            int x = 1LL * a[j][i] * inv % mod;
            for (int k = i + 1; k <= n; k++)a[j][k] = (a[j][k] - 1LL * a[i][k] * x % mod + mod) % mod;
        }
    }
    return tr ? (mod - ret) % mod : ret;
}
signed main() {
    scanf("%d%d%d", &n, &m, &t);
    while (m--) {
        scanf("%d%d%d", &u, &v, &w);
        if (t == 1) {
            a[u][v] = (a[u][v] - w + mod) % mod;
            a[v][v] = (a[v][v] + w) % mod;
        } else {
            a[v][u] = (a[v][u] - w + mod) % mod;
            a[u][v] = (a[u][v] - w + mod) % mod;
            a[u][u] = (a[u][u] + w) % mod;
            a[v][v] = (a[v][v] + w) % mod;
        }
    }
    printf("%d", det(1));
    return 0;
}
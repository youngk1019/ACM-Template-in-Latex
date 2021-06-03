//Luogu P3386 【模板】二分图最大匹配
//KM 复杂度O(n^3)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define inf 0x3f3f3f3f3f3f3f3f
#define maxn 510
int n, m, x, y, z, mat[maxn], pre[maxn];
ll e[maxn][maxn], slack[maxn], ex[maxn], ey[maxn];
bool visy[maxn];
void bfs(int u) {
    memset(visy, 0, sizeof(visy));
    memset(pre, 0, sizeof(pre));
    memset(slack, 0x3f, sizeof(slack));
    int x, y = 0;
    mat[y] = u;
    while (true) {
        x = mat[y], visy[y] = true;
        int tmp = 0;
        ll delta = inf;
        for (int i = 1; i <= n; i++) {
            if (visy[i])continue;
            if (slack[i] > ex[x] + ey[i] - e[x][i]) slack[i] = ex[x] + ey[i] - e[x][i], pre[i] = y;
            if (slack[i] < delta) delta = slack[i], tmp = i;
        }
        for (int i = 0; i <= n; i++)
            if (visy[i]) ex[mat[i]] -= delta, ey[i] += delta;
            else slack[i] -= delta;
        y = tmp;
        if (!mat[y]) break;
    }
    while (y) mat[y] = mat[pre[y]], y = pre[y];
}
ll km() {
    memset(mat, 0, sizeof(mat));
    memset(ex, 0, sizeof(ex));
    memset(ey, 0, sizeof(ey));
    for (int i = 1; i <= n; i++) bfs(i);
    ll res = 0;
    for (int i = 1; i <= n; ++i) if (mat[i]) res += e[mat[i]][i];
    return res;
}

signed main() {
    scanf("%d%d", &n, &m);
    memset(e, 0xcf, sizeof(e));
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &z);
        e[x][y] = max(e[x][y], 1LL * z);
    }
    printf("%lld\n", km());
    for (int i = 1; i <= n; i++) printf("%d ", mat[i]);
    return 0;
}
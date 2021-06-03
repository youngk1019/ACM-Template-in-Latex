//Luogu P4551 最长异或路径
#include <bits/stdc++.h>
using namespace std;
#define maxn 100100
struct trie {
    int cnt, t[maxn << 5][2];
    void insert(int x) {
        int p = 0;
        for (int i = 30; i >= 0; i--) {
            bool y = (x >> i) & 1;
            if (!t[p][y]) t[p][y] = ++cnt;
            p = t[p][y];
        }
    }
    int query(int x) {
        int p = 0, ret = 0;
        for (int i = 30; i >= 0; i--) {
            bool y = (x >> i) & 1;
            if (t[p][y ^ 1]) ret += (1 << i), p = t[p][y ^ 1];
            else p = t[p][y];
        }
        return ret;
    }
} T;
int n, m, x, y, z, a[maxn], ans;
vector<pair<int, int> > e[maxn];
void dfs(int u, int fa, int now) {
    for (auto &[v, w]:e[u]) {
        if (v == fa) continue;
        a[++m] = now ^ w;
        dfs(v, u, a[m]);
    }
}
signed main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        scanf("%d%d%d", &x, &y, &z);
        e[x].emplace_back(y, z), e[y].emplace_back(x, z);
    }
    dfs(1, 0, 0);
    for (int i = 0; i <= m; i++) T.insert(a[i]);
    for (int i = 0; i <= m; i++) ans = max(ans, T.query(a[i]));
    printf("%d", ans);
    return 0;
}
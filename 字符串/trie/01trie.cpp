//Luogu P4551 最长异或路径
//给定一棵 /n 个点的带权树，结点下标从 1 开始到n。寻找树中找两个结点，求最长的异或路径。
//异或路径指的是指两个结点之间唯一路径上的所有边权的异或。
#include <bits/stdc++.h>
using namespace std;
struct trie {
    vector<array<int, 2>> t;
    int hbp = 31;
    trie() { t.push_back({}); }
    trie(int mx) {
        t.push_back({});
        hbp = 31 - __builtin_clz(mx);
    }
    void insert(int x) {
        int p = 0;
        for (int i = hbp; i >= 0; i--) {
            bool y = (x >> i) & 1;
            if (!t[p][y]) t[p][y] = t.size(), t.push_back({});
            p = t[p][y];
        }
    }
    int query(int x) {
        int p = 0, ret = 0;
        for (int i = hbp; i >= 0; i--) {
            bool y = (x >> i) & 1;
            if (t[p][y ^ 1]) ret += (1 << i), p = t[p][y ^ 1];
            else p = t[p][y];
        }
        return ret;
    }
} T((1LL << 31) - 1);
int n, m, x, y, z, ans;
vector<vector<pair<int, int> >> e;
vector<int> a;
void dfs(int u, int fa, int now) {
    for (auto &[v, w]: e[u]) {
        if (v == fa) continue;
        a[++m] = now ^ w;
        dfs(v, u, a[m]);
    }
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    e.resize(n + 1), a.resize(n + 1);
    for (int i = 1; i < n; i++) {
        cin >> x >> y >> z;
        e[x].emplace_back(y, z), e[y].emplace_back(x, z);
    }
    dfs(1, 0, 0);
    for (int i = 0; i <= m; i++) T.insert(a[i]);
    for (int i = 0; i <= m; i++) ans = max(ans, T.query(a[i]));
    cout << ans << '\n';
    return 0;
}
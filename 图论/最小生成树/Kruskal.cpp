//Lougu P3366 【模板】最小生成树
//Kruskal
#include <bits/stdc++.h>
using namespace std;
#define maxn 2000100
struct dsu {
    int f[maxn];
    void init(int n) { for (int i = 1; i <= n; i++) f[i] = i; }
    int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }
    bool merge(int x, int y) {//x为父亲，如果返回true则原本不为同一并查集
        int fx = find(x), fy = find(y);
        return f[fy] = fx, fx != fy;
    }
} D;
int n, m, x, y, w, cnt, ans;
vector<tuple<int, int, int> > v;
signed main() {
    scanf("%d%d", &n, &m);
    D.init(n);
    while (m--) {
        scanf("%d%d%d", &x, &y, &w), v.push_back(make_tuple(w, x, y));
    }
    sort(v.begin(), v.end());
    for (auto &u:v) {
        if (D.merge(get<1>(u), get<2>(u))) {
            ans += get<0>(u), cnt++;
        }
        if (cnt == n - 1) break;
    }
    if (cnt == n - 1) printf("%d\n", ans);
    else puts("orz");
    return 0;
}
//Luogu P3865 【模板】ST表
#include<bits/stdc++.h>
using namespace std;
#define maxn 100100
struct st {
    int n, a[maxn][18];
    void build(int *f, int _n) {
        n = _n;
        for (int i = 1; i <= n; i++) a[i][0] = f[i];
        for (int i = 1; i <= 17; i++)
            for (int j = 1; j + (1 << i) - 1 <= n; j++)
                a[j][i] = max(a[j][i - 1], a[j + (1 << (i - 1))][i - 1]);
    }
    int query(int l, int r) {
        int lg = log2(r - l + 1);
        return max(a[l][lg], a[r - (1 << lg) + 1][lg]);
    }
} T;
int n, m, l, r, a[maxn];
signed main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    T.build(a, n);
    while (m--) {
        scanf("%d%d", &l, &r);
        printf("%d\n", T.query(l, r));
    }
    return 0;
}
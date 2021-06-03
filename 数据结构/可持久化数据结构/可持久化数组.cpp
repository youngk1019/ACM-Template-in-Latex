//Lougu P3919 【模板】可持久化线段树 1 (可持久化数组)
//操作1：格式：v 1 loc value 含义：在版本v的基础上，将a[loc]修改为value
//操作2：格式：v 2 loc 含义：访问版本v中的a[loc]的值，生成一样版本的对象应为v
#include <bits/stdc++.h>
using namespace std;
#define maxn 1000100
int n, m, v, op, loc, val, a[maxn];
struct persistable_array {
    int ls[maxn << 5], rs[maxn << 5], val[maxn << 5], rt[maxn], cnt;
    void build(int &cur, int l, int r) {
        cur = ++cnt;
        if (l == r) return val[cur] = a[l], void();
        int mid = (l + r) >> 1;
        build(ls[cur], l, mid), build(rs[cur], mid + 1, r);
    }
    void updata(int &cur, int pre, int l, int r, int x, int v) {
        cur = ++cnt;
        ls[cur] = ls[pre], rs[cur] = rs[pre], val[cur] = val[pre];
        if (l == r) return val[cur] = v, void();
        int mid = (l + r) >> 1;
        if (x <= mid) updata(ls[cur], ls[pre], l, mid, x, v);
        else updata(rs[cur], rs[pre], mid + 1, r, x, v);
    }
    int query(int cur, int l, int r, int x) {
        if (l == r) return val[cur];
        int mid = (l + r) >> 1;
        if (x <= mid) return query(ls[cur], l, mid, x);
        else return query(rs[cur], mid + 1, r, x);
    }
} T;
signed main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    T.build(T.rt[0], 1, n);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &v, &op, &loc);
        if (op == 1) {
            scanf("%d", &val);
            T.updata(T.rt[i], T.rt[v], 1, n, loc, val);
        } else {
            printf("%d\n", T.query(T.rt[v], 1, n, loc));
            T.rt[i] = T.rt[v];
        }
    }
    return 0;
}
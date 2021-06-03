//Lougu P3402 可持久化并查集
//操作1：格式：1 x y 含义：合并 x,y 所在集合
//操作2：格式：2 k   含义：回到第 k 次操作(执行三种操作中的任意一种都记为一次操作)之后的状态
//操作3：格式：3 x y 含义：询问 x,y 是否属于同一集合，如果是则输出 1 ，否则输出 0
//时间复杂度O(mlognlogn) 空间复杂度O(mlogn)
#include <bits/stdc++.h>
using namespace std;
#define maxn 200100
int n, m, op, x, y, k;
struct persistable_union_set {
    int ls[maxn << 5], rs[maxn << 5], fa[maxn << 5], dep[maxn << 5], rt[maxn], cnt;
    void build(int &cur, int l, int r) {
        cur = ++cnt;
        if (l == r) return fa[cur] = l, void();
        int mid = (l + r) >> 1;
        build(ls[cur], l, mid), build(rs[cur], mid + 1, r);
    }
    void _merge(int &cur, int pre, int l, int r, int x, int f) {
        cur = ++cnt;
        ls[cur] = ls[pre], rs[cur] = rs[pre];
        if (l == r) return fa[cur] = f, dep[cur] = dep[pre], void();
        int mid = (l + r) >> 1;
        if (x <= mid) _merge(ls[cur], ls[pre], l, mid, x, f);
        else _merge(rs[cur], rs[pre], mid + 1, r, x, f);
    }
    void updata(int cur, int l, int r, int x) {//更新深度
        if (l == r) return dep[cur]++, void();
        int mid = (l + r) >> 1;
        if (x <= mid) updata(ls[cur], l, mid, x);
        else updata(rs[cur], mid + 1, r, x);
    }
    void merge(int &cur, int pre, int l, int r, int x, int y) {//x，y为下标
        if (fa[x] != fa[y]) {
            if (dep[x] > dep[y])swap(x, y);
            _merge(cur, pre, l, r, fa[x], fa[y]);//y为父亲
            if (dep[x] == dep[y])updata(cur, l, r, fa[y]);
        }
    }
    int query(int cur, int l, int r, int x) {//返回下标
        if (l == r) return cur;
        int mid = (l + r) >> 1;
        if (x <= mid) return query(ls[cur], l, mid, x);
        else return query(rs[cur], mid + 1, r, x);
    }
    int find(int cur, int l, int r, int x) {//返回位置下标
        int p = query(cur, l, r, x);
        while (fa[p] ^ x) x = fa[p], p = query(cur, l, r, x);
        return p;
    }
} T;
signed main() {
    scanf("%d%d", &n, &m);
    T.build(T.rt[0], 1, n);
    for (int i = 1; i <= m; i++) {
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d%d", &x, &y);
            T.rt[i] = T.rt[i - 1];
            int fx = T.find(T.rt[i], 1, n, x), fy = T.find(T.rt[i], 1, n, y);
            T.merge(T.rt[i], T.rt[i - 1], 1, n, fx, fy);
        } else if (op == 2) {
            scanf("%d", &k);
            T.rt[i] = T.rt[k];
        } else {
            scanf("%d%d", &x, &y);
            T.rt[i] = T.rt[i - 1];
            int fx = T.find(T.rt[i], 1, n, x), fy = T.find(T.rt[i], 1, n, y);
            printf("%d\n", T.fa[fx] == T.fa[fy] ? 1 : 0);
        }
    }
    return 0;
}
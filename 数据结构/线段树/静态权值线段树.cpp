//Lougu P3369 【模板】普通平衡树
//1: 插入 x 数
//2: 删除 x 数(若有多个相同的数，因只删除一个)
//3: 查询 x 数的排名(排名定义为比当前数小的数的个数 +1 )
//4: 查询排名为 x 的数
//5: 求 x 的前驱(前驱定义为小于 x，且最大的数)
//6: 求 x 的后继(后继定义为大于 x，且最小的数)
//L是左边界 R是右边界 左边界需要-1
#include <bits/stdc++.h>
using namespace std;
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
#define maxn 100100
int n, op[maxn], x[maxn], L = -1, R = 1e5;
vector<int> v;
struct segment_tree {
    int val[maxn << 2];
    void pushup(int p) {
        val[p] = val[ls(p)] + val[rs(p)];
    }
    void modify(int p, int l, int r, int x, int k) {
        if (l == r) return val[p] += k, void();
        int mid = (l + r) >> 1;
        if (x <= mid) modify(ls(p), l, mid, x, k);
        else modify(rs(p), mid + 1, r, x, k);
        pushup(p);
    }
    int query(int p, int ql, int qr, int l, int r) {
        if (ql <= l && r <= qr)return val[p];
        int ret = 0, mid = (l + r) >> 1;
        if (ql <= mid) ret += query(ls(p), ql, qr, l, mid);
        if (qr > mid) ret += query(rs(p), ql, qr, mid + 1, r);
        return ret;
    }
    int kth(int p, int l, int r, int x) {
        if (l == r) return l;
        int mid = (l + r) >> 1;
        if (x <= val[ls(p)]) return kth(ls(p), l, mid, x);
        else return kth(rs(p), mid + 1, r, x - val[ls(p)]);
    }
} T;
signed main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", op + i, x + i);
        if (op[i] != 4) v.push_back(x[i]);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    for (int i = 1; i <= n; i++) {
        if (op[i] != 4) x[i] = lower_bound(v.begin(), v.end(), x[i]) - v.begin();
    }
    for (int i = 1; i <= n; i++) {
        if (op[i] == 1) T.modify(1, L, R, x[i], 1);
        else if (op[i] == 2) T.modify(1, L, R, x[i], -1);
        else if (op[i] == 3) printf("%d\n", T.query(1, L, x[i] - 1, L, R) + 1);
        else if (op[i] == 4) printf("%d\n", v[T.kth(1, L, R, x[i])]);
        else if (op[i] == 5) x[i] = T.query(1, L, x[i] - 1, L, R), printf("%d\n", v[T.kth(1, L, R, x[i])]);
        else x[i] = T.query(1, L, x[i], L, R) + 1, printf("%d\n", v[T.kth(1, L, R, x[i])]);
    }
    return 0;
}
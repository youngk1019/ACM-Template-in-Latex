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
#define maxn 100100 //动态开点的左右范围为1e7，不止4倍空间
int n, op, x, L = -1e7 - 1, R = 1e7, rt = 1;
struct segment_tree {
    int val[maxn << 5], ls[maxn << 5], rs[maxn << 5], cnt = 1;
    void pushup(int p) {
        val[p] = val[ls[p]] + val[rs[p]];
    }
    void modify(int &p, int l, int r, int x, int k) {
        if (!p) p = ++cnt;
        if (l == r) return val[p] += k, void();
        int mid = (l + r) >> 1;
        if (x <= mid) modify(ls[p], l, mid, x, k);
        else modify(rs[p], mid + 1, r, x, k);
        pushup(p);
    }
    int query(int p, int ql, int qr, int l, int r) {
        if (!p) return 0;
        if (ql <= l && r <= qr)return val[p];
        int ret = 0, mid = (l + r) >> 1;
        if (ql <= mid) ret += query(ls[p], ql, qr, l, mid);
        if (qr > mid) ret += query(rs[p], ql, qr, mid + 1, r);
        return ret;
    }
    int kth(int p, int l, int r, int x) {
        if (!p) return 0x3f3f3f3f;
        if (l == r) return l;
        int mid = (l + r) >> 1;
        if (x <= val[ls[p]]) return kth(ls[p], l, mid, x);
        else return kth(rs[p], mid + 1, r, x - val[ls[p]]);
    }
} T;
signed main() {
    scanf("%d", &n);
    while (n--) {
        scanf("%d%d", &op, &x);
        if (op == 1) T.modify(rt, L, R, x, 1);
        else if (op == 2) T.modify(rt, L, R, x, -1);
        else if (op == 3) printf("%d\n", T.query(1, L, x - 1, L, R) + 1);
        else if (op == 4) printf("%d\n", T.kth(1, L, R, x));
        else if (op == 5) x = T.query(1, L, x - 1, L, R), printf("%d\n", T.kth(1, L, R, x));
        else x = T.query(1, L, x, L, R) + 1, printf("%d\n", T.kth(1, L, R, x));
    }
    return 0;
}

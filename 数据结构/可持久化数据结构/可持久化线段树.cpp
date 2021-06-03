//Lougu P3834 【模板】可持久化线段树 2(主席树)
//l,r,k , 表示查询区间 [l, r] 内的第 k 小值
#include <bits/stdc++.h>
using namespace std;
#define maxn 200010
int n, m, l, r, k, a[maxn], b[maxn];
struct persistable_segment_tree {
    int ls[maxn << 5], rs[maxn << 5], sum[maxn << 5], rt[maxn], cnt;
    void build(int &cur, int l, int r) {
        cur = ++cnt;
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(ls[cur], l, mid), build(rs[cur], mid + 1, r);
    }
    void updata(int &cur, int pre, int l, int r, int x) {
        cur = ++cnt;
        ls[cur] = ls[pre], rs[cur] = rs[pre], sum[cur] = sum[pre] + 1;
        if (l == r) return;
        int mid = (l + r) >> 1;
        if (x <= mid) updata(ls[cur], ls[pre], l, mid, x);
        else updata(rs[cur], rs[pre], mid + 1, r, x);
    }
    int query(int pre, int cur, int l, int r, int k) {
        if (l == r) return l;
        int mid = (l + r) >> 1;
        int x = sum[ls[cur]] - sum[ls[pre]];
        if (x >= k) return query(ls[pre], ls[cur], l, mid, k);
        else return query(rs[pre], rs[cur], mid + 1, r, k - x);
    }
} T;
signed main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        b[i] = a[i];
    }
    sort(b + 1, b + n + 1);
    int N = unique(b + 1, b + 1 + n) - b - 1;
    //T.build(T.rt[0], 1, N); 可以不需要build
    for (int i = 1; i <= n; i++) T.updata(T.rt[i], T.rt[i - 1], 1, N, lower_bound(b + 1, b + N + 1, a[i]) - b);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", b[T.query(T.rt[l - 1], T.rt[r], 1, N, k)]);
    }
    return 0;
}
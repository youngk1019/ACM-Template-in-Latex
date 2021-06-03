//Luogu P3810 【模板】三维偏序（陌上花开）
//有n个元素，第i个元素有a[i] b[i] c[i]三个属性，设f(i)表示满足a[j]<=a[i]且b[j]<=b[i]且c[j]<=c[i]且j!=i的j的个数
//对于d属于[0,n) 求f(i)=d的个数
//tuple 0->a[i] 1->b[i] 2->c[i] 4->相同元素的个数 5->标号下标
//需要去重特殊处理
#include <bits/stdc++.h>
using namespace std;
#define lowbit(x) (x & -x)
#define maxn 200010
int n, k, tot, ans[maxn], f[maxn];
tuple<int, int, int, int, int> b[maxn], a[maxn];
struct bit {
    int tree[maxn];
    void add(int x, int k) {
        while (x < maxn) {
            tree[x] += k;
            x += lowbit(x);
        }
    }
    int query(int x) {
        int ret = 0;
        while (x) {
            ret += tree[x];
            x -= lowbit(x);
        }
        return ret;
    }
} T;
void cdq(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    cdq(l, mid), cdq(mid + 1, r);
    vector<pair<int, int> > v;
    for (int i = l, p = l, q = mid + 1; i <= r; i++) {
        if (p <= mid && get<1>(a[p]) <= get<1>(a[q]) || q > r) {
            T.add(get<2>(a[p]), get<3>(a[p]));
            v.push_back(make_pair(get<2>(a[p]), get<3>(a[p])));
            b[i] = a[p++];
        } else {
            ans[get<4>(a[q])] += T.query(get<2>(a[q]));
            b[i] = a[q++];
        }
    }
    for (auto u : v) T.add(u.first, -u.second);
    for (int i = l; i <= r; i++) a[i] = b[i];
}
signed main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) 
		scanf("%d%d%d", &get<0>(b[i]), &get<1>(b[i]), &get<2>(b[i]));
    sort(b + 1, b + 1 + n);
    for (int i = 1, j = i + 1; i <= n; i = j + 1, j = i + 1) {
        while (j <= n && b[i] == b[j]) j++;
        j--;
        a[++tot] = b[i];
        get<3>(a[tot]) = (j - i + 1);
        get<4>(a[tot]) = tot;
    }
    cdq(1, tot);
    for (int i = 1; i <= tot; i++) 
		f[ans[get<4>(a[i])] + get<3>(a[i]) - 1] += get<3>(a[i]);
    for (int i = 0; i < n; i++) printf("%d\n", f[i]);
    return 0;
}
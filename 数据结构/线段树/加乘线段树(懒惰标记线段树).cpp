//Lougu P3373 【模板】线段树2
//操作1：格式：1 x y k 含义：将区间 [x,y] 内每个数乘上 k
//操作2：格式：2 x y k 含义：将区间 [x,y] 内每个数加上 k
//操作3：格式：3 x y 含义：输出区间 [x,y] 内每个数的和对 mod 取模所得的结果
//先乘后加
#include <bits/stdc++.h>
using namespace std;

// S为最终存储的元素
// op为S需要支持的操作* 需要满足结合律 (a*b)*c = a*(b*c)
// e是幺元（基本元/单位元）a*e = e*a = a
// F一个映射的集合(即函数)，可以使得序列中的数发生变换。这个映射需要满足以下几个条件:
// 1.存在一个恒等的映射，即f(x)=x f \in F（存在一个操作，使得操作后x不变）
// 2.是闭包的，即f(g(x)) \in F f,g \in F (基本上所有的操作都是闭包的)
// 3.对于所有的f \in F满足 f(x*y)=f(x)*f(y) (注意这里的*是op)
// F为映射的类型
// mapping(F f,S x)为映射是如何改变元素x的，其实就是定义f(x)
// composition(F f,F g)返回函数的复合，就是返回f(g(x)) (注意顺序)
// id()返回的是恒等关系
template<class S, S (*op)(S, S), S (*e)(),
        class F, S (*mapping)(F, S), F (*composition)(F, F), F (*id)()>
struct lazy_segtree {
public:
    lazy_segtree() : lazy_segtree(0) {}
    explicit lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}
    explicit lazy_segtree(const std::vector<S> &v) : _n(int(v.size())) {
        size = bit_ceil(_n), log = __builtin_ctz(size);
        d = std::vector<S>(2 * size, e()), lz = std::vector<F>(size, id());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--)update(i);
    }
    void set(int p, S x) { //node[p] = x
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }
    S get(int p) { //获得node[p]
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }
    S prod(int l, int r) { //获得op(node[l],...,node[r-1])注意是[L,R)
        if (l == r) return e();
        l += size, r += size;
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        S sml = e(), smr = e();
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1, r >>= 1;
        }
        return op(sml, smr);
    }
    S all_prod() { return d[1]; } //获得op(node[0],...,node[n-1])
    void apply(int p, F f) { //对node[p]进行f操作
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = mapping(f, d[p]);
        for (int i = 1; i <= log; i++) update(p >> i);
    }
    void apply(int l, int r, F f) { //对node[l..r)进行f操作
        if (l == r) return;
        l += size, r += size;
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        int l2 = l, r2 = r;
        while (l < r) {
            if (l & 1) all_apply(l++, f);
            if (r & 1) all_apply(--r, f);
            l >>= 1, r >>= 1;
        }
        l = l2, r = r2;
        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

    template<bool (*g)(S)>
    int max_right(int l) { //返回一个r 满足f(op(node[l],...,node[l-1])) = true, f(op(node[l],...,node[r])) = false
        return max_right(l, [](S x) { return g(x); });
    }
    template<class G>
    int max_right(int l, G g) {
        if (l == _n) return _n;
        l += size;
        for (int i = log; i >= 1; i--) push(l >> i);
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!g(op(sm, d[l]))) {
                while (l < size) {
                    push(l);
                    l = (2 * l);
                    if (g(op(sm, d[l]))) {
                        sm = op(sm, d[l++]);
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l++]);
        } while ((l & -l) != l);
        return _n;
    }

    template<bool (*g)(S)>
    int min_left(int r) { //返回一个l 满足f(op(node[l],...,node[r-1])) = true, f(op(node[l+1],...,node[r-1])) = false
        return min_left(r, [](S x) { return g(x); });
    }
    template<class G>
    int min_left(int r, G g) {
        if (r == 0) return 0;
        r += size;
        for (int i = log; i >= 1; i--) push((r - 1) >> i);
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!g(op(d[r], sm))) {
                while (r < size) {
                    push(r);
                    r = (2 * r + 1);
                    if (g(op(d[r], sm))) {
                        sm = op(d[r--], sm);
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

private:
    int _n, size, log;
    vector<S> d;
    vector<F> lz;
    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, F f) {
        d[k] = mapping(f, d[k]);
        if (k < size) lz[k] = composition(f, lz[k]);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }
    unsigned int bit_ceil(unsigned int n) {
        unsigned int x = 1;
        while (x < n) x *= 2;
        return x;
    }
};

int n, m, mod;
struct node {
    int val, len;
};
auto op = [](node x, node y) { return (node) {.val = (x.val + y.val) % mod, .len = x.len + y.len,}; };
auto e = []() { return (node) {.val = 0, .len = 0,}; };
struct F {
    int add, mul;//先乘后加
};
auto mapping = [](F f, node x) {
    x.val = (1LL * f.mul * x.val % mod + 1LL * f.add * x.len % mod) % mod;
    return x;
};
auto composition = [](F f, F g) {
    return (F) {.add = (int) (f.add + 1LL * f.mul * g.add % mod) % mod, .mul = (int) (1LL * f.mul * g.mul % mod)};
};
auto id = []() { return (F) {.add= 0, .mul=1}; };
signed main() {
    int x, y, k, opt;
    scanf("%d%d%d", &n, &m, &mod);
    vector<node> v;
    for (int i = 1; i <= n; i++) scanf("%d", &x), v.push_back({.val=x, .len=1});
    lazy_segtree<node, op, e, F, mapping, composition, id> T(v);
    while (m--) {
        scanf("%d", &opt);
        if (opt == 1) scanf("%d%d%d", &x, &y, &k), T.apply(x - 1, y, {.add=0, .mul=k});
        else if (opt == 2) scanf("%d%d%d", &x, &y, &k), T.apply(x - 1, y, {.add=k, .mul=1});
        else scanf("%d%d", &x, &y), printf("%d\n", T.prod(x - 1, y).val);
    }
    return 0;
}
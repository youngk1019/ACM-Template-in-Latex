//Lougu P3793 由乃救爷爷
//m个询问，表示区间最大值,输出为每次询问的答案的和
//建树O(n) 查询随机平均O(1) 极限情况O(n)
#include <bits/stdc++.h>
using namespace std;
#define maxn 20000010
int n, m, sd, l, r, a[maxn];
unsigned long long ans;
struct cartesian_tree {
    int ls[maxn], rs[maxn], stk[maxn], top, rt, *val;//随机数据单调栈不需要开这么多空间
    void build(int n, int *a) {//a[1...n]
        val = a;
        for (int i = 1; i <= n; i++) {
            while (top && a[stk[top]] <= a[i]) ls[i] = stk[top--];
            rs[stk[top]] = i;
            stk[++top] = i;
        }
        rt = stk[1];
    }
    int query(int l, int r) {
        int x = rt;
        while (true) {
            if (l <= x && x <= r) return val[x];
            x = (r < x ? ls : rs)[x];
        }
    }
} T;
//题目数据生成器
namespace GenHelper {
    unsigned z1, z2, z3, z4, b;
    unsigned rand_() {
        b = ((z1 << 6) ^ z1) >> 13;
        z1 = ((z1 & 4294967294U) << 18) ^ b;
        b = ((z2 << 2) ^ z2) >> 27;
        z2 = ((z2 & 4294967288U) << 2) ^ b;
        b = ((z3 << 13) ^ z3) >> 21;
        z3 = ((z3 & 4294967280U) << 7) ^ b;
        b = ((z4 << 3) ^ z4) >> 12;
        z4 = ((z4 & 4294967168U) << 13) ^ b;
        return (z1 ^ z2 ^ z3 ^ z4);
    }
}
void srand(unsigned x) {
    using namespace GenHelper;
    z1 = x;
    z2 = (~x) ^ 0x233333333U;
    z3 = x ^ 0x1234598766U;
    z4 = (~x) + 51;
}
int read() {
    using namespace GenHelper;
    int a = rand_() & 32767;
    int b = rand_() & 32767;
    return a * 32768 + b;
}
signed main() {
    scanf("%d%d%d", &n, &m, &sd);
    srand(sd);
    for (int i = 1; i <= n; i++) a[i] = read();
    T.build(n, a);
    while (m--) {
        l = read() % n + 1, r = read() % n + 1;
        if (l > r) swap(l, r);
        ans += T.query(l, r);
    }
    printf("%llu\n", ans);
    return 0;
}
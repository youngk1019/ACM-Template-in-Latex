//codeforces CF1207F Remainder Problem
// 一个长度为 5×10^5 的序列，初值为 0，你要完成 q 次操作，操作有如下两种：
// 1 x y: 将下标为 x 的位置的值加上 y。
// 2 x y: 询问所有下标模 x 的结果为 y 的位置的值之和。
#include <bits/stdc++.h>
using namespace std;
#define maxn 500100
long long sum[750][750], a[maxn];// sum[模数][余数]
int q, op, x, y;
signed main() {
    scanf("%d", &q);
    while (q--) {
        scanf("%d%d%d", &op, &x, &y);
        if (op == 1) {
            for (int i = 1; i <= 700; i++)sum[i][x % i] += y;
            a[x] += y;
        } else {
            if (x <= 700) printf("%lld\n", sum[x][y]);
            else {
                long long ret = 0;
                for (int i = y; i <= 500000; i += x)ret += a[i];
                printf("%lld\n", ret);
            }
        }
    }
    return 0;
}
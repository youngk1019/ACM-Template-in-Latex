//Lougu P3369 【模板】普通平衡树
//1: 插入 x 数
//2: 删除 x 数(若有多个相同的数，因只删除一个)
//3: 查询 x 数的排名(排名定义为比当前数小的数的个数 +1 )
//4: 查询排名为 x 的数
//5: 求 x 的前驱(前驱定义为小于 x，且最大的数)
//6: 求 x 的后继(后继定义为大于 x，且最小的数)
#include<bits/stdc++.h>
using namespace std;
#define maxn 20000010
const int mx = 1e7 + 1;
struct bit {
    int t[maxn];
#define lowbit(x) x & -x
    void add(int x, int y) {
        while (x < maxn) t[x] += y, x += lowbit(x);
    }
    int query(int x) {
        int ret = 0;
        while (x) ret += t[x], x -= lowbit(x);
        return ret;
    }
    int kth(int x) {
        int ret = 0;
        for (int i = 25; i >= 0; i--) {
            if ((ret + (1 << i)) < maxn && x > t[ret + (1 << i)]) ret += (1 << i), x -= t[ret];
        }
        return ret + 1;
    }
} T;
int t, op, x;
signed main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &op, &x);
        if (op == 1) T.add(x + mx, 1);
        else if (op == 2) T.add(x + mx, -1);
        else if (op == 3) printf("%d\n", T.query(x + mx - 1) + 1);
        else if (op == 4) printf("%d\n", T.kth(x) - mx);
        else if (op == 5) printf("%d\n", T.kth(T.query(x + mx - 1)) - mx);
        else if (op == 6) printf("%d\n", T.kth(T.query(x + mx) + 1) - mx);
    }
    return 0;
}
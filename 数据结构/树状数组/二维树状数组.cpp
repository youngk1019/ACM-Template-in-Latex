//Lougu P4514 上帝造题的七分钟
//格式：L a b c d delta 含义：代表将(a,b),(c,d)为顶点的矩形区域内的所有数字加上delta
//格式：k a b c d 含义：代表求(a,b),(c,d)为顶点的矩形区域内所有数字的和
//二维前缀和可以变为\sum_{i=1}^{x} \sum_{j=1}^{y} d[i][j]*(x-i+1)*(y-i+1)
//需要维护d[i][j],d[i][j]*i,d[i][j]*j,d[i][j]*i*j
#include<bits/stdc++.h>
using namespace std;
#define maxn 2100
struct bit {
    int t[maxn][maxn][4];
#define lowbit(x) x & -x
    void add(int x, int y, int k) {
        int xx = x;
        while (xx < maxn) {
            int yy = y;
            while (yy < maxn) {
                t[xx][yy][0] += k;
                t[xx][yy][1] += k * x;
                t[xx][yy][2] += k * y;
                t[xx][yy][3] += k * x * y;
                yy += lowbit(yy);
            }
            xx += lowbit(xx);
        }
    }
    int query(int x, int y) {
        int ret[4] = {0};
        int xx = x;
        while (xx) {
            int yy = y;
            while (yy) {
                ret[0] += t[xx][yy][0];
                ret[1] += t[xx][yy][1];
                ret[2] += t[xx][yy][2];
                ret[3] += t[xx][yy][3];
                yy -= lowbit(yy);
            }
            xx -= lowbit(xx);
        }
        return ret[0] * (x * y + x + y + 1) - ret[1] * (y + 1) - ret[2] * (x + 1) + ret[3];
    }
} T;
int n, m, a, b, c, d, delta;
char op;
signed main() {
    scanf("X%d%d", &n, &m);
    while (~scanf(" %c", &op)) {
        if (op == 'L') {
            scanf("%d%d%d%d%d", &a, &b, &c, &d, &delta);
            T.add(a, b, delta);
            T.add(a, d + 1, -delta);
            T.add(c + 1, b, -delta);
            T.add(c + 1, d + 1, delta);
        } else {
            scanf("%d%d%d%d", &a, &b, &c, &d);
            printf("%d\n", T.query(c, d) - T.query(a - 1, d) - T.query(c, b - 1) + T.query(a - 1, b - 1));
        }
    }
    return 0;
}
//codeforces CF1194E Count The Rectangles
//计算矩形个数
#include <bits/stdc++.h>
using namespace std;
#define maxn 5010
struct node {
    int x1, y1, x2, y2;
} row[maxn], col[maxn];
int n, x, y, xx, yy, cntr, cntc;
bitset<maxn> f[maxn >> 1];
long long ans;
signed main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d%d", &x, &y, &xx, &yy);
        if (x > xx) swap(x, xx);
        if (y > yy) swap(y, yy);
        if (y == yy) row[++cntr] = (node) {x, y, xx, yy};
        else col[++cntc] = (node) {x, y, xx, yy};
    }
    if (cntc > cntr) {
        for (int i = 1; i <= cntr; i++) {
            for (int j = 1; j <= cntc; j++) {
                if (row[i].x1 <= col[j].x1 && row[i].x2 >= col[j].x1
                    && col[j].y1 <= row[i].y1 && col[j].y2 >= row[i].y1)
                    f[i][j] = true;
            }
        }
        for (int i = 1; i <= cntr; i++) {
            for (int j = i + 1; j <= cntr; j++) {
                x = (f[i] & f[j]).count();
                ans += ((1LL * x * (x - 1)) >> 1);
            }
        }
    } else {
        for (int i = 1; i <= cntr; i++) {
            for (int j = 1; j <= cntc; j++) {
                if (row[i].x1 <= col[j].x1 && row[i].x2 >= col[j].x1
                    && col[j].y1 <= row[i].y1 && col[j].y2 >= row[i].y1)
                    f[j][i] = true;
            }
        }
        for (int i = 1; i <= cntc; i++) {
            for (int j = i + 1; j <= cntc; j++) {
                x = (f[i] & f[j]).count();
                ans += ((1LL * x * (x - 1)) >> 1);
            }
        }
    }
    printf("%lld", ans);
    return 0;
}
//Lougu P1169 [ZJOI2007]棋盘制作
//棋盘黑白相邻格子不同色 第一行为可以找到的最大正方形棋盘的面积，第二行为可以找到的最大矩形棋盘的面积
#include <bits/stdc++.h>
using namespace std;
#define maxn 2010
int n, m, a[maxn][maxn], l[maxn][maxn], r[maxn][maxn], up[maxn][maxn], ans1, ans2;
signed main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", a[i] + j);
            l[i][j] = r[i][j] = j, up[i][j] = 1;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 2; j <= m; j++) {
            if (a[i][j] != a[i][j - 1]) l[i][j] = l[i][j - 1];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = m - 1; j >= 1; j--) {
            if (a[i][j] != a[i][j + 1]) r[i][j] = r[i][j + 1];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (i > 1 && a[i][j] != a[i - 1][j]) {
                l[i][j] = max(l[i][j], l[i - 1][j]);
                r[i][j] = min(r[i][j], r[i - 1][j]);
                up[i][j] = up[i - 1][j] + 1;
            }
            int x = r[i][j] - l[i][j] + 1, y = min(x, up[i][j]);
            ans1 = max(ans1, y * y);
            ans2 = max(ans2, x * up[i][j]);
        }
    }
    printf("%d\n%d", ans1, ans2);
    return 0;
}
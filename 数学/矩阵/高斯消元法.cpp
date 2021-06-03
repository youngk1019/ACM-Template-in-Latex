//Lougu P3389 【模板】高斯消元法
//高斯-约旦消元法
//如果需要无穷解的情况，所以我们要按当前未知数大于，之后的未知数小于来比较
//比如数据：
//2
//0 2 3
//0 0 0
#include <bits/stdc++.h>
using namespace std;
#define maxn 110
#define eps 1e-6
double a[maxn][maxn];
int n;
signed main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n + 1; j++) scanf("%lf", &a[i][j]);
    }
    for (int i = 1; i <= n; i++) {
        int mx = i;
        for (int j = i + 1; j <= n; j++)if (fabs(a[j][i]) > fabs(a[mx][i]))mx = j;
        for (int j = i; j <= n + 1; j++) swap(a[i][j], a[mx][j]);//如果未消去成对角矩阵，保证矩阵不变应该从1开始
        if (fabs(a[i][i]) < eps) return puts("No Solution"), 0;
        for (int j = 1; j <= n; j++) {
            if (j != i) {
                double x = a[j][i] / a[i][i];
                for (int k = i + 1; k <= n + 1; k++) a[j][k] -= a[i][k] * x;
                //起始位置把i+1变为i则可以实现消成对角矩阵
            }
        }
    }
    for (int i = 1; i <= n; i++) printf("%.2lf\n", a[i][n + 1] / a[i][i]);
    return 0;
}
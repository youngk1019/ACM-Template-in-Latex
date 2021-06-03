//Luogu P3382 【模板】三分法
//找到一个多项式函数的峰值(极大值)，输入为从高到低依次表示该n次函数各项的系数。
#include <bits/stdc++.h>
using namespace std;
#define maxn 20
#define eps 1e-7
int n;
double a[maxn], l, r;
double F(double x) {
    double ret = 0;
    for (int i = n; i >= 0; i--)ret = ret * x + a[i];
    return ret;
}
signed main() {
    scanf("%d%lf%lf", &n, &l, &r);
    for (int i = n; i >= 0; i--) scanf("%lf", a + i);
    while (fabs(l - r) >= eps) {
        double midl = (2 * l + r) / 3, midr = (l + 2 * r) / 3;
        if (F(midl) > F(midr))r = midr;
        else l = midl;
    }
    printf("%.5lf", l);
    return 0;
}
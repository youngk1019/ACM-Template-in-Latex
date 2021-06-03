//Luogu P1337 [JSOI2004]平衡点 / 吊打XXX
//注意clock优化只有提交的时候再添加，调试的时候需要clock()-输入时间
//成功率不高
#include <bits/stdc++.h>
using namespace std;
#define maxn 1010
#define eps 1e-14
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rd(RANDOM);
uniform_int_distribution<int> dis(0, UINT16_MAX);
int n, x, y, w, sumx, sumy;
tuple<int, int, int> a[maxn];
double ansx, ansy; //全局最优解的坐标
double ans = 1e18; //全局最优解、温度
const double delta = 0.993; //降温系数
double calc(double x, double y) {
    double ret = 0, deltax, deltay;
    for (int i = 1; i <= n; i++) {
        deltax = x - get<0>(a[i]), deltay = y - get<1>(a[i]);
        ret += sqrt(deltax * deltax + deltay * deltay) * get<2>(a[i]);
    }
    return ret;
}
void SA() {
    double x = ansx, y = ansy, X, Y, now, Delta, t = 10000;
    while (t > eps) {
        X = x + (dis(rd) - INT16_MAX) * t;
        Y = y + (dis(rd) - INT16_MAX) * t;
        now = calc(X, Y);
        Delta = now - ans;
        if (Delta < 0) {
            x = X, y = Y;
            ansx = x, ansy = y, ans = now;
        } else if (exp(-Delta / t) * UINT16_MAX > dis(rd))x = X, y = Y;
        t *= delta;
    }
}
void solve(double x, double y) {
    ansx = x, ansy = y;
    while ((double) clock() / CLOCKS_PER_SEC < 0.8) SA();
}
signed main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &x, &y, &w);
        a[i] = make_tuple(x, y, w);
        sumx += x, sumy += y;
    }
    solve((double) sumx / n, (double) (sumy) / n);
    printf("%.3lf %.3lf", ansx, ansy);
    return 0;
}
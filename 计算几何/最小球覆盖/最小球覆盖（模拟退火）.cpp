//CF gym101981 D Country Meow
#include <bits/stdc++.h>
using namespace std;
#define maxn 110
#define eps 1e-15
int n;
struct node {
    double x, y, z;
} a[maxn];
double sumx, sumy, sumz;
const double delta = 0.999; //降温系数
double calc(node a, node b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}
double SA() {
    double t = 1, mx, temp;
    node o = {sumx / n, sumy / n, sumz / n};
    int now;
    while (t > eps) {
        mx = -1, now = 1;
        for (int i = 1; i <= n; i++) {
            temp = calc(a[i], o);
            if (temp > mx) mx = temp, now = i;
        }
        o.x += (a[now].x - o.x) * t;
        o.y += (a[now].y - o.y) * t;
        o.z += (a[now].z - o.z) * t;
        t *= delta;
    }
    return calc(a[now], o);
}
signed main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lf%lf%lf", &a[i].x, &a[i].y, &a[i].z);
        sumx += a[i].x, sumy += a[i].y, sumz += a[i].z;
    }
    printf("%.15lf", SA());
    return 0;
}
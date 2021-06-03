//CF gym101981 D Country Meow
#include <bits/stdc++.h>
using namespace std;
#define maxn 110
#define eps 1e-5
int n;
struct node {
    double x, y, z;
} a[maxn];
double p[3];
double calc(node a, node b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}
double dfs(int now) {
    if (now == 3) {
        node o = {p[0], p[1], p[2]};
        double ans = 0;
        for (int i = 1; i <= n; i++)ans = max(ans, calc(a[i], o));
        return ans;
    }
    double l = -1e5, r = 1e5, r1, r2, ans = DBL_MAX;
    while (fabs(l - r) >= eps) {
        p[now] = (2 * l + r) / 3;
        r1 = dfs(now + 1);
        p[now] = (l + 2 * r) / 3;
        r2 = dfs(now + 1);
        (r1 > r2) ? l = (2 * l + r) / 3 : r = (l + 2 * r) / 3;
        ans = min(r1, r2);
    }
    return ans;
}
signed main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lf%lf%lf", &a[i].x, &a[i].y, &a[i].z);
    printf("%.15lf", dfs(0));
    return 0;
}
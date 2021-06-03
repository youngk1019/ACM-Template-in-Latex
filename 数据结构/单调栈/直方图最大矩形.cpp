//POJ2559 Largest Rectangle in a Histogram
//直方图最大矩形面积
#include <bits/stdc++.h> //POJ不能用bits
using namespace std;
#define maxn 3000010
int n, a[maxn], w[maxn];
long long ans;
signed main() {
    while (scanf("%d", &n) && n) {
        stack<int> s;
        ans = 0;
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        a[++n] = 0;
        s.push(0);
        for (int i = 1; i <= n; i++) {
            if (a[i] > a[s.top()]) s.push(i), w[i] = 1;
            else {
                int width = 0;
                while (a[s.top()] > a[i]) {
                    width += w[s.top()];
                    ans = max(ans, 1LL * width * a[s.top()]), s.pop();
                }
                s.push(i), w[i] = width + 1;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
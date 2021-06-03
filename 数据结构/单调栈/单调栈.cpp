//Lougu P5788 【模板】单调栈
//数列中第 i个元素之后第一个大于 a[i]的元素的下标 如果不存在为0
#include <bits/stdc++.h>
using namespace std;
#define maxn 3000010
int n, a[maxn], ans[maxn];
stack<int> s;
signed main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        while (s.size() && a[s.top()] < a[i]) ans[s.top()] = i, s.pop();
        s.push(i);
    }
    for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
    return 0;
}
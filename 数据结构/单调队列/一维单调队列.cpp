//Lougu P1886 滑动窗口 /【模板】单调队列
//有一个长为 n 的序列 a，以及一个大小为 k 的窗口。现在这个从左边开始向右滑动，每次滑动一个单位，求出每次滑动后窗口中的最大值和最小值
#include <bits/stdc++.h>
using namespace std;
#define maxn 1000010
int n, k, a[maxn];
void min_deque() {
    deque<int> q;
    for (int i = 1; i <= n; i++) {
        while (q.size() && q.front() + k <= i) q.pop_front();
        while (q.size() && a[q.back()] > a[i]) q.pop_back();
        q.push_back(i);
        if (i >= k)printf("%d ", a[q.front()]);
    }
    puts("");
}
void max_deque() {
    deque<int> q;
    for (int i = 1; i <= n; i++) {
        while (q.size() && q.front() + k <= i) q.pop_front();
        while (q.size() && a[q.back()] < a[i]) q.pop_back();
        q.push_back(i);
        if (i >= k)printf("%d ", a[q.front()]);
    }
    puts("");
}
signed main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    min_deque(), max_deque();
    return 0;
}
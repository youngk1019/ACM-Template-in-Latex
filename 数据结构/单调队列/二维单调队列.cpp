//Lougu P2216 [HAOI2007]理想的正方形
//a*b 矩阵中所有 n*n 正方形区域中的最大整数和最小整数的差值
#include <bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
#define maxn 1010
int n, m, k, a[maxn][maxn], temp[maxn][maxn], mx[maxn][maxn], mn[maxn][maxn], ans = inf;
void min_deque() {
    deque<int> q;
    for (int i = 1; i <= n; i++) {//求行的最值
        q.clear();
        for (int j = 1; j <= m; j++) {
            while (q.size() && q.front() + k <= j) q.pop_front();
            while (q.size() && a[i][q.back()] >= a[i][j]) q.pop_back();
            q.push_back(j);
            if (j >= k) temp[i][j] = a[i][q.front()];
        }
    }
    for (int j = k; j <= m; j++) {//求列的最值
        q.clear();
        for (int i = 1; i <= n; i++) {
            while (q.size() && q.front() + k <= i) q.pop_front();
            while (q.size() && temp[q.back()][j] >= temp[i][j]) q.pop_back();
            q.push_back(i);
            if (i >= k) mn[i][j] = temp[q.front()][j];
        }
    }
}
void max_deque() {
    deque<int> q;
    for (int i = 1; i <= n; i++) {//求行的最值
        q.clear();
        for (int j = 1; j <= m; j++) {
            while (q.size() && q.front() + k <= j) q.pop_front();
            while (q.size() && a[i][q.back()] <= a[i][j]) q.pop_back();
            q.push_back(j);
            if (j >= k) temp[i][j] = a[i][q.front()];
        }
    }
    for (int j = k; j <= m; j++) {//求列的最值
        q.clear();
        for (int i = 1; i <= n; i++) {
            while (q.size() && q.front() + k <= i) q.pop_front();
            while (q.size() && temp[q.back()][j] <= temp[i][j]) q.pop_back();
            q.push_back(i);
            if (i >= k) mx[i][j] = temp[q.front()][j];
        }
    }
}
signed main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) scanf("%d", a[i] + j);
    }
    min_deque(), max_deque();
    for (int i = k; i <= n; i++) {
        for (int j = k; j <= m; j++) ans = min(ans, mx[i][j] - mn[i][j]);
    }
    printf("%d\n", ans);
    return 0;
}
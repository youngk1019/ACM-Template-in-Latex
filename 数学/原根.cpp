//Luogu P6091 【模板】原根
//2,4,p^k,2*p^k p为奇质数 才有原根
//求最小原根，只需要验证g^(phi(n)) ≡ 1 (mod n) 且其余k ≠ phi(n) g^k ≠ 1 (mod n)，最小原根O(n^(1/4))
//其余原根均满足g^k 其中gcd(k,phi(n)) = 1
//复杂度O(nlogloglogn)
#include<bits/stdc++.h>
using namespace std;
#define maxn 1000100
int t, n, d, mnrt, cnt, tot, fc[maxn], prime[maxn], phi[maxn];
bool rt[maxn], flag[maxn], phiflag[maxn], ans[maxn];
void sieve() {
    phi[1] = 1;
    for (int i = 2; i < maxn; i++) {
        if (!flag[i]) prime[++cnt] = i, phi[i] = i - 1;
        for (int j = 1; j <= cnt && prime[j] * i < maxn; j++) {
            flag[i * prime[j]] = true;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        }
    }
    rt[2] = rt[4] = true;
    for (int i = 2; i <= cnt; i++) {
        for (int j = 1; 1LL * j * prime[i] < maxn; j *= prime[i]) { rt[j * prime[i]] = true; }
        for (int j = 2; 1LL * j * prime[i] < maxn; j *= prime[i]) { rt[j * prime[i]] = true; }
    }
}
int qpow(int a, int b, int mod) {
    int ret = 1;
    while (b) {
        if (b & 1) ret = 1LL * ret * a % mod;
        a = 1LL * a * a % mod, b >>= 1;
    }
    return ret;
}
void proc(int x) {
    int lim = sqrt(x), tmp = x;
    for (int i = 1, y = prime[i]; y <= lim; y = prime[++i]) {
        if (tmp % y == 0) {
            fc[++tot] = y;
            while (tmp % y == 0) tmp /= y;
            for (int j = y; j <= x; j += y) phiflag[j] = true;
        }
    }
    if (tmp > 1) {
        fc[++tot] = tmp;
        for (int j = tmp; j <= x; j += tmp) phiflag[j] = true;
    }
}
bool check(int x, int p) {
    int phip = phi[p];
    if (qpow(x, phip, p) != 1) return false;
    for (int i = 1; i <= tot; i++) if (qpow(x, phip / fc[i], p) == 1) return false;
    return true;
}
int findmnrt(int x) {
    for (int i = 1; i < x; i++) if (check(i, x)) return i;
    return 0;
}
void getrt(int x, int mnrt, int d) {
    int cnt = 0;
    for (int i = 1, prod = mnrt, phix = phi[x]; i <= phix; i++, prod = 1LL * prod * mnrt % x) {
        if (!phiflag[i]) ans[prod] = true, cnt++;
        else phiflag[i] = false;//清空
    }
    printf("%d\n", cnt);
    for (int i = 1, j = 0; i < n; i++) {
        if (ans[i]) {
            ans[i] = false;//清空
            if (++j == d)j = 0, printf("%d ", i);
        }

    }
}
signed main() {
    sieve();
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &d);
        if (!rt[n]) {
            puts("0\n");
            continue;
        }
        tot = 0, proc(phi[n]);
        mnrt = findmnrt(n), getrt(n, mnrt, d);
        puts("");
    }
    return 0;
}
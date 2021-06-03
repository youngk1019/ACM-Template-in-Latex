//Luogu P5091 【模板】扩展欧拉定理
//a,m无需互质
//b <  phi(m) a^b ≡ a^(b mod phi(m)) mod m
//b >= phi(m) a^b ≡ a^((b mod phi(m)) + phi(m)) mod m
#include<bits/stdc++.h>
using namespace std;
#define maxn 20000100
int a, m, b, phi, len;
bool flag;
char s[maxn];
int qpow(int a, int b, int mod) {
    int ret = 1;
    while (b) {
        if (b & 1) ret = 1LL * ret * a % mod;
        a = 1LL * a * a % mod, b >>= 1;
    }
    return ret;
}
int getphi(int x) {
    int lim = sqrt(x), tmp = x, phi = x;
    for (int i = 2; i <= lim; i++) {
        if (!(tmp % i)) {
            phi -= phi / i;
            while (!(tmp % i)) tmp /= i;
        }
    }
    if (tmp > 1) phi -= phi / tmp;
    return phi;
}
signed main() {
    scanf("%d%d%s", &a, &m, s);
    len = strlen(s), phi = getphi(m);
    for (int i = 0; i < len; i++) {
        b = (b << 3) + (b << 1) + (s[i] ^ 48);
        if (b > phi) b %= phi, flag = true;
    }
    printf("%d", qpow(a, b + (flag ? phi : 0), m));
    return 0;
}
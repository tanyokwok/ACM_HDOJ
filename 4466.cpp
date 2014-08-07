/*************************************************************************
    > File Name: 4466.cpp
    > Author: Jianpeng, Hou
    > Mail: peng_come_on@126.com 
    > Created Time: 一  8/ 4 19:57:59 2014
 ************************************************************************/

#include <cstdio>
#include <climits>

#define MOD (1000000000 + 7)
#define N (5000000)

int n;
int f[N + 5];
int pow2[N + 5];
long long ans;
int cas = 0;

int main() {
	// init
	f[0] = 0;
	pow2[0] = 1;
	for (int i = 1; i <= N; ++i) {
		pow2[i] = pow2[i - 1] << 1;
		if (pow2[i] >= MOD) { pow2[i] -= MOD; }
		f[i] = f[i - 1] + (i - 1) / 2 - i / 3 + ((i%3) ? 0 : 1);
		if (!(i & 1)) {
			f[i] -= i / 4;
		}
		if (f[i] >= MOD) { f[i] = f[i] - MOD; }
		if (f[i] < 0) { f[i] = f[i] + MOD; }
	}
	for (int i = 3; i <= N; ++i) {
		for (int j = i + i; j <= N; j += i) {
			f[j] -= f[i];
			if (f[j] < 0) { f[j] += MOD; }
		}
	}
	while (~scanf("%d", &n)) {
		++cas;
		ans = 0;
		for (int i = 1; i * i <= n; ++i) {
			if (n % i == 0) {
				ans = (ans + ((long long)f[i]) * pow2[n / i - 1]) % MOD;
				if (i * i != n) {
					ans = (ans + ((long long)f[n / i]) * pow2[i - 1]) % MOD;
				}
			}
		}
		printf("Case %d: %lld\n", cas, ans);
	}
	return 0;
}

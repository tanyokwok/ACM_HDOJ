/*************************************************************************
    > File Name: 4475.cpp
    > Author: Jianpeng, Hou
    > Mail: peng_come_on@126.com 
    > Created Time: 二  8/ 5 15:18:05 2014
 ************************************************************************/

#include <cstdio>

#define MOD (1000003)
#define N (1000003)

long long dp[N + 10];
int t;
long long n;

int main() {
	dp[1] = 2;
	for (int i = 2; i <= N; ++i) {
		dp[i] = ((dp[i - 1] * i) << 1) % MOD;
	}
	scanf("%d", &t);
	while(t--) {
		scanf("%lld", &n);
		if (n >= N) { printf("0\n"); }
		else { printf("%lld\n", dp[n]);  }
	}
	return 0;
}




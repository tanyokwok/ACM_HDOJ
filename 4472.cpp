/*************************************************************************
    > File Name: 4472.cpp
    > Author: Jianpeng, Hou
    > Mail: peng_come_on@126.com 
    > Created Time: 二  8/ 5 10:29:50 2014
 ************************************************************************/

#include <cstdio>

#define N (1000)
#define MOD (1000000000 + 7)

int dp[N + 10];
int cas;
int n;

int main() {
	dp[1] = 1;
	for (int i= 2; i <= N; ++i) {
		dp[i] = 0;
		for (int j = 1; j <= i - 1; ++j) {
			if ((i - 1) % j == 0) {
				dp[i] = (dp[i] + dp[(i - 1) / j]) % MOD;
			}
		}
	}
	cas = 0;
	while(~scanf("%d", &n)) {
		++cas;
		printf("Case %d: %d\n", cas, dp[n]);
	}
	return 0;
}

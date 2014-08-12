/*************************************************************************
    > File Name: 4430.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 五  8/ 8 10:03:50 2014
 ************************************************************************/

#include <cstdio>
#include <cstring>
#include <cmath>
#include <climits>

#define LL long long

LL n, k;
int r;

LL fast_pow(LL a, int b) {
	LL exp = 1;
	while (b) {
		if (b & 1) {
			exp *= a;
		}
		a =  a * a;
		b >>= 1;
	}
	return exp;
}

LL binary_find(int r, LL k_max, LL n) {
	LL k_l = 2, k_r = k_max, k_m, sum;
	while (k_l <= k_r) {
		k_m = (k_l + k_r) / 2;
		sum = k_m * ( 1 - fast_pow(k_m, r)) / (1 - k_m);
		if (sum == n) {
			return k_m;
		} else if (sum > n) {
			k_r = k_m - 1;
		} else if (sum < n) {
			k_l = k_m + 1;
		}
	}
	return -1;
}

int main() {
	while (~scanf("%lld", &n)) {
		k = n - 1;
		r = 1;
		for (int i = 2; i < 40; ++i) {
			LL kk;
			LL k_max = (LL)pow(n, 1.0 / i);
			kk = binary_find(i, k_max, n);
			if (-1 != kk) {
				if ((i * kk < r * k) || ((i * kk == r * k ) && (i < r))) {
					r = i;
					k = kk;
				}
			}
			kk = binary_find(i, k_max, n - 1);
			if (-1 != kk) {
				if ((i * kk < r * k) || ((i * kk == r * k) && (i < r))) {
					r = i;
					k = kk;
				}
			}
		}
		printf("%d %lld\n", r, k);
	}
	return 0;
}

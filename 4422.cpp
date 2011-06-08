/*************************************************************************
    > File Name: 4422.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 五  8/ 8 18:57:09 2014
 ************************************************************************/

#include <cstdio>
#include <cstring>

#define N 5

int n;
int w[N + 5];

int max(int a, int b) {
	return a > b ? a : b;
}

int main() {
	while (~scanf("%d", &n)) {
		for (int i = 0; i < n; ++i) {
			scanf("%d", &w[i]);
		}
		if (n <= 3) { printf("1024\n"); }
		if (n == 4) {
			bool is_true = false;
			for(int i = 0;i < 2; ++i) {
				for (int j = i + 1; j < 3; ++j) {
					for (int k = j + 1; k < 4; ++k) {
						if (((w[i] + w[j] + w[k]) % 1024) == 0) {
							is_true = true;
						}
					}
				}
			}
			if (is_true) { printf("1024\n"); }
			else {
				int sum_max = 0;
				for (int i = 0; i < 3; ++i) {
					for (int j = i + 1; j < 4; ++j) {
						int mod = w[i] + w[j];
						while (mod > 1024) { mod -= 1024; }
						sum_max = max(sum_max, mod);
					}
				}
				printf("%d\n", sum_max);
			}
		}
		if (n == 5) {
			int sum_max = -1;
			int sum = 0;
			for (int i = 0; i < 5; ++i) {
				sum += w[i];
			}
			for (int i = 0; i < 3; ++i) {
				for (int j = i + 1; j < 4; ++j) {
					for (int k = j + 1; k < 5; ++k) {
						if (((w[i] + w[j] + w[k]) % 1024) == 0) {
							int mod = sum - w[i] - w[j] - w[k];
							while (mod > 1024) {mod -= 1024; }
							sum_max = max(sum_max, mod);
						}
					}
				}
			}
			if (-1 != sum_max) { printf("%d\n", sum_max); }
			else { printf("0\n"); }
		}
	}
	return 0;
}


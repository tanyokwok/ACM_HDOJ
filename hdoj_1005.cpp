/*************************************************************************
    > File Name: hdoj_1005.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 五  9/12 18:05:08 2014
 ************************************************************************/

#include <cstdio>

#define MOD (7)

typedef struct {
	int a;
	int b;
	int c;
	int d;
} facter;

typedef struct {
	int a;
	int b;
} row;

int a, b, n;
facter f;
int index;
row ans;

row mul_1(facter aa, row bb) {
	row cc;
	cc.a = (aa.a * bb.a + aa.b * bb.b) % MOD;
	cc.b = (aa.c * bb.a + aa.d * bb.b) % MOD;
	return cc;
}

facter mul_2(facter aa, facter bb) {
	facter cc;
	cc.a = (aa.a * bb.a + aa.b * bb.c) % MOD;
	cc.b = (aa.a * bb.b + aa.b * bb.d) % MOD;
	cc.c = (aa.c * bb.a + aa.d * bb.c) % MOD;
	cc.d = (aa.c * bb.b + aa.d * bb.d) % MOD;
	return cc;
}

int main() {
	while ((~scanf("%d %d %d", &a, &b, &n)) && a) {
		f.a = a;
		f.b = b;
		f.c = 1;
		f.d = 0;
		ans.a = 1;
		ans.b = 1;
		index = n - 2;
		if (1 > index) {
			printf("1\n");
		} else {
			while (0 != index) {
				if (0 != (index % 2)) {
					ans = mul_1(f, ans);
				}
				index = index / 2;
				f = mul_2(f, f);
			}
			printf("%d\n", ans.a);
		}
	}
	return 0;
}

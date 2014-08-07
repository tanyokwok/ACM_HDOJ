/*************************************************************************
    > File Name: 4465.cpp
    > Author: Jianpeng, Hou
    > Mail: peng_come_on@126.com 
    > Created Time: 日  8/ 3 18:07:50 2014
 ************************************************************************/

#include <cstdio>
#include <cmath>

#define MIN (0.0001)

using namespace std;

int n;
double p, q;
double sum;
double pp, qq;
int id;
int N;

int main() {
	int i, j, k;
	id = 0;
	while(~scanf("%d %lf", &n, &p)) {
		N = n + 1;
		++id;
		sum = 0;
		q = 1 - p;
		pp = qq = 1;
		for (i = 0; i <= n; ++i) {
			while((pp + qq) * (n - i) > n) {
				pp *= p;
				qq *= q;
				--N;
			}
			sum += pp * (n - i) * pow(p, N) + qq * (n - i) * pow(q, N);
			pp *= (n + i + 1.0) / (i + 1) * q;
			qq *= (n + i + 1.0) / (i + 1) * p;
		}
		printf("Case %d: %.6lf\n", id, sum);
	}
	return 0;
}


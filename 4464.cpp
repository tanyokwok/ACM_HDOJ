/*************************************************************************
    > File Name: 4464.cpp
    > Author: Jianpeng, Hou
    > Mail: peng_come_on@126.com 
    > Created Time: 日  8/ 3 16:23:54 2014
 ************************************************************************/

#include <cstdio>
#include <string>

using namespace std;

int n;
char url[105];

int main() {
	freopen("input.dat", "r", stdin);

	int count = 0;
	int sum = 0;
	int max = 0;
	int i, j;
	while(~scanf("%d", &n)) {
		++count;
		max = 0;
		while(n--) {
			sum = 0;
			scanf("%s", url);
			for (i = 0; i < strlen(url); ++i) {
				sum += url[i];
			}
			if (sum > max) { max = sum; }
		}
		printf("Case %d: %d\n", count, max);
	}
	return 0;
}

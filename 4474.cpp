/*************************************************************************
    > File Name: 4474.cpp
    > Author: Jianpeng, Hou
    > Mail: peng_come_on@126.com 
    > Created Time: 三  8/ 6 09:55:12 2014
 ************************************************************************/

#include <cstdio>
#include <cstring>
#include <iostream>

#define N (10000)

using namespace std;

struct node {
	int pre;
	int mod;
	int num;
} queue[N + 10], queue_tmp;

int len_queue;

bool digits[10];
bool remainder[N + 10];

int n, m, cas, ans;

int bfs() {
	len_queue = 0;
	for (int i = 1; i < 10; ++i) {
		if (digits[i]) {
			queue_tmp.pre = -1;
			queue_tmp.num = i;
			queue_tmp.mod = i % n;
			if (!remainder[queue_tmp.mod]) {
				remainder[queue_tmp.mod] = true;
				queue[len_queue++] = queue_tmp;
				if (queue_tmp.mod == 0) {
					return len_queue - 1;
				}
			}
		}
	}
	for (int i = 0; i < len_queue; ++i) {
		for (int j = 0; j < 10; ++j) {
			if (digits[j]) {
				queue_tmp.pre = i;
				queue_tmp.num = j;
				queue_tmp.mod = ((queue[i].mod * 10) % n + j) % n;
				if (!remainder[queue_tmp.mod]) {
					remainder[queue_tmp.mod] = true;
					queue[len_queue++] = queue_tmp;
					if (queue_tmp.mod == 0) {
						return len_queue - 1;
					}
				}
			}
		}
	}
	return -1;
}

void print_ans() {
	if (-1 == ans) {
		printf("Case %d: %d\n", cas, ans);
	} else {
		printf("Case %d: ", cas);
		int ans_array[N + 10], index = 0;
		while(ans != -1) {
			ans_array[index++] = queue[ans].num;
			ans = queue[ans].pre;
		}
		for (int i = index - 1; i >= 0; --i) {
			printf("%d", ans_array[i]);
		}
		printf("\n");
	}
}

int main() {
	freopen("input.dat", "r", stdin);

	cas = 0;
	while (~scanf("%d %d", &n , &m)) {
		++cas;
		// init
		memset(digits, true, sizeof(digits));
		memset(remainder, false, sizeof(remainder));
		int mm;
		for (int i = 0; i < m; ++i) {
			scanf("%d", &mm);
			digits[mm] = false;
		}
		// bfs
		ans = bfs();
		print_ans();
	}
	return 0;
}

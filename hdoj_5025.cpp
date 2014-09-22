/*************************************************************************
    > File Name: hdoj_5025.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 一  9/22 15:15:16 2014
 ************************************************************************/

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>
#include <climits>
#include <cmath>

#define N (100)
#define M (9)

using std::vector;
using std::queue;

/**
 * 笔记
 *
 * bfs 数组存放的是以某种状态到达某个位置后所用的最少步数。
 * memset()不会超时吗？如何判断？
 **/

typedef struct {
	int x;
	int y;
} point;

typedef struct {
	point position;
	int snakes;
	int keys;
	int cost;
} state;

int n, m;
int bfs[N + 5][N + 5][M + 5][32];
char map[N + 5][N + 5];
point start, end;
point snake[5];
int num_snake;
int ans;

queue<state> states;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int min(int a, int b) {
	return a < b ? a : b;
}

void get_input() {
	for (int i = 0; i < n; ++i) {
		scanf("%s", map[i]);
	}
}

void init() {
	num_snake = 0;
	memset(bfs, -1, sizeof(bfs));
	while (!states.empty()) {
		states.pop();
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (map[i][j] == 'K') {
				start.x = i;
				start.y = j;
			} else if (map[i][j] == 'T') {
				end.x = i;
				end.y = j;
			} else if (map[i][j] == 'S') {
				snake[num_snake].x = i;
				snake[num_snake].y = j;
				++num_snake;
			}
		}
	}
}

state get_next_state(state pre, int direction) {
	state ret;

	ret.position.x = pre.position.x + dx[direction];
	ret.position.y = pre.position.y + dy[direction];
	if (!((ret.position.x >= 0) && (ret.position.x < n)
		&& (ret.position.y >= 0) && (ret.position.y < n))) {
		ret.cost = -1;
		return ret;
	}

	if (map[ret.position.x][ret.position.y] == '#') {
		ret.cost = -1;
		return ret;
	}

	ret.keys = map[ret.position.x][ret.position.y] - '0';
	if (1 != (ret.keys - pre.keys)) {
		ret.keys = pre.keys;
	}

	ret.cost = pre.cost + 1;
	ret.snakes = pre.snakes;
	if (map[ret.position.x][ret.position.y] == 'S') {
		int id;
		for (int i = 0; i < num_snake; ++i) {
			if ((snake[i].x == ret.position.x) && (snake[i].y == ret.position.y)) {
				id = i;
			}
		}
		if (((pre.snakes >> id) & 1) == 0) {
			ret.snakes = ret.snakes | (1 << id);
			++ret.cost;
		}
	}

	return ret;
}

bool judge(state now) {
	if (-1 == now.cost) return false;
	int cost_pre = bfs[now.position.x][now.position.y][now.keys][now.snakes];
	if ((cost_pre != -1) && (bfs[now.position.x][now.position.y][now.keys][now.snakes] <= now.cost)) return false;
	return true;
}

int get_min_step() {
	int ret = INT_MAX;

	for (int i = 0; i < pow(2, num_snake); ++i) {
		if (bfs[end.x][end.y][m][i] != -1) {
			ret = min(ret, bfs[end.x][end.y][m][i]);
		}
	}
	
	if (ret == INT_MAX) return -1;
	return ret;
}

void print(int direction, state pre, state ret) {
	printf("---------\n");
	printf("%d %d %d %d %d\n", pre.position.x, pre.position.y, pre.keys, pre.snakes, pre.cost);
	printf("%d %d %d %d %d\n", ret.position.x, ret.position.y, ret.keys, ret.snakes, ret.cost);
}

int bfs_f() {
	state state_now, state_next;
	state_now.position.x = start.x;
	state_now.position.y = start.y;
	state_now.keys = 0;
	state_now.snakes = 0;
	state_now.cost = 0;
	
	bfs[state_now.position.x][state_now.position.y][state_now.keys][state_now.snakes] = state_now.cost;
	states.push(state_now);

	while (!states.empty()) {
		state_now = states.front();
		states.pop();
		for (int i = 0; i < 4; ++i) {
			state_next = get_next_state(state_now, i);
			//print(i, state_now, state_next);
			if (judge(state_next)) {
				bfs[state_next.position.x][state_next.position.y][state_next.keys][state_next.snakes] = state_next.cost;
				states.push(state_next);
			}
		}
	}

	return get_min_step();
}
	
int main() {
	freopen("input.txt", "r", stdin);

	while ((~scanf("%d %d", &n, &m)) && (0 != n)) {
		get_input();
		init();
		ans = bfs_f();
		if (-1 == ans) {
			printf("impossible\n");
		} else {
			printf("%d\n", ans);
		}
	}

	return 0;
}


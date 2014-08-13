/*************************************************************************
    > File Name: hdoj_3622.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 三  8/13 11:08:30 2014
 ************************************************************************/

#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>

#define N (100)
#define M (40000)

using namespace std;

int n;

struct coordinate{
	int x;
	int y;
} point[2 * N + 10];

double ans;
double dis[2 * N + 10][2 * N + 10];
// tarjan
vector<vector<int> > adj;
int dindex, stop, bcnt;
int dfn[2 * N + 10], low[2 * N + 10], belong[2 * N + 10], stap[2 * N + 10];
bool instack[2 * N + 10];
// dag
vector<vector<int> > dag;
int indegree[2 * N + 10];
// topsort
queue<int> q_topsort, q_blue;
char color[2 * N + 10];

double cal_dis(int i, int j) {
	return pow((point[i].x - point[j].x) * (point[i].x - point[j].x) + (point[i].y - point[j].y) * (point[i].y - point[j].y), 0.5);
}

void make_adj(double radius) {
	adj.clear();
	adj.assign(2 * n, vector<int>());
	for (int i = 0; i < 2 * n; ++i) {
		for (int j = i + 1; j < 2 * n; ++j) {
			if ((i != (j ^ 1)) && (dis[i][j] < 2 * radius)) {
				adj[i].push_back(j ^ 1);
				adj[j].push_back(i ^ 1);
			}
		}
	}
}

void tarjan(int i) {
	int j;
	dfn[i] = low[i] = ++dindex;
	instack[i] = true;
	stap[++stop] = i;
	for (int k = 0; k < adj[i].size(); ++k) {
		j = adj[i][k];
		if (!dfn[j]) {
			tarjan(j);
			if (low[j] < low[i]) low[i] = low[j];
		}
		else if (instack[j] && dfn[j] < low[i]) {
			low[i] = low[j];
		}
	}
	if (dfn[i] == low[i]) {
		++bcnt;
		do {
			j = stap[stop--];
			instack[j] = false;
			belong[j] = bcnt - 1;
		} while (j != i); 
	}
}

void tarjan_solve() {
	stop = bcnt = dindex = 0;
	memset(dfn, 0, sizeof(dfn));
	memset(instack, false, sizeof(instack));
	for (int i = 0; i < 2 * n; ++i) {
		if (!dfn[i]) tarjan(i);
	}
}

bool tarjan_solvable() {
	for (int i = 0; i < n; ++i) {
		if (belong[2 * i] == belong[2 * i + 1]) return false;
	}
	return true;
}

double binary_search(double min, double max, double precision) {
	double mid;
	while (max - min > precision) {
		mid = (min + max) / 2;
		make_adj(mid);
		tarjan_solve();
		if (tarjan_solvable()) {
			min = mid;
		} else {
			max = mid;
		}
	}
	return min;
}

int main() {
	freopen("input.dat", "r", stdin);

	while (~scanf("%d", &n)) {
		for (int i = 0; i < n; ++i) {
			scanf("%d%d%d%d", &point[2 * i].x, &point[2 * i].y, &point[2 * i + 1].x, &point[2 * i + 1].y);
		}
		double max = 0, max_now;
		for (int i = 0; i < 2 * n; ++i) {
			for (int  j = i + 1; j < 2 * n; ++j) {
				dis[i][j] = dis[j][i] = cal_dis(i, j);
				if (dis[i][j] > max) max = dis[i][j];
			}
		}
		// binary search
		ans = binary_search(0, max, 0.00001);
		// print
		printf("%.2lf\n", ans);
	}
	return 0;
}

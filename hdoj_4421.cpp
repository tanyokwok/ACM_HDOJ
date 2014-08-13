/*************************************************************************
    > File Name: hdoj_4421.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 三  8/13 21:27:18 2014
 ************************************************************************/

#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>

#define N (500)

using namespace std;

int n, max_bits, tmp;
int matrix[N + 10][N + 10];
bool ans;
// tarjan
vector<vector<int> > adj;
int dindex, stop, bcnt;
int dfn[2 * N + 10], low[2 * N + 10], belong[2 * N + 10], stap[2 * N + 10];
bool instack[2 * N + 10];

int cal_bits(int n) {
	int bits = 0;
	while(n) {
		n >>= 1;
		++bits;
	}
	return bits;
}

void make_adj(int bit) {
	int num;
	adj.clear();
	adj.assign(2 * n, vector<int>());
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			num = matrix[i][j] & (1 << (bit - 1));
			if (((i & 1) == 1) && ((j & 1) == 1)) {
				if (num) {
					adj[2 * i].push_back(2 * j + 1);
					adj[2 * j].push_back(2 * i + 1);
				} else {
					adj[2 * i + 1].push_back(2 * i);
					adj[2 * j + 1].push_back(2 * j);
				}
			}
			if (((i & 1) == 0) && ((j & 1) == 0)) {
				if (num) {
					adj[2 * i].push_back(2 * i + 1);
					adj[2 * j].push_back(2 * j + 1);
				} else {
					adj[2 * i + 1].push_back(2 * j);
					adj[2 * j + 1].push_back(2 * i);
				}
			}
			else {
				if (num) {
					adj[2 * i].push_back(2 * j + 1);
					adj[2 * i + 1].push_back(2 * j);
					adj[2 * j].push_back(2 * i + 1);
					adj[2 * j + 1].push_back(2 * i);
				} else {
					adj[2 * i].push_back(2 * j);
					adj[2 * j].push_back(2 * i);
					adj[2 * i + 1].push_back(2 * j + 1);
					adj[2 * j + 1].push_back(2 * i + 1);
				}
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
			low[i] = dfn[j];
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

int main() {
	freopen("input.dat", "r", stdin);

	while (~scanf("%d", &n)) {
		max_bits = 0;
		ans = true;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				scanf("%d", &matrix[i][j]);
				tmp = cal_bits(matrix[i][j]);
				if (tmp > max_bits) max_bits = tmp;
			}
		}
		for (int i = 0; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				if (matrix[i][j] != matrix[j][i]) ans = false;
			}
		}
		// <WA>
		for (int i = 0; i < n; ++i) {
			if (matrix[i][i]) ans = false;
		}
		// </ WA>
		if (!ans) {
			printf("NO\n");
			continue;
		}
		for (int i = 1; i <= max_bits; ++i) {
			make_adj(i);
			tarjan_solve();
			if (!tarjan_solvable()) {
				ans = false;
				break;
			}
		}
		if (ans) {
			printf("YES\n");
		} else {
			printf("NO\n");
		}
	}
	return 0;
}

/*************************************************************************
    > File Name: hdoj_4115.cpp
    > Author: HouJP
    > Mail: peng_come_on@126.com 
    > Created Time: 四  8/14 16:16:24 2014
 ************************************************************************/

#include <cstdio>
#include <cstring>
#include <vector>

#define N (10000) 

using namespace std;

int n, m, t, cas, bob[N + 10];
// make adj
vector<vector<int> > adj;
// tarjan
int dindex, stop, bcnt;
int dfn[2 * N + 10], low[2 * N + 10], belong[2 * N + 10], stap[2 * N + 10];
bool instack[2 * N + 10];

int get_tie(int a) {
	return bob[a];
}

int get_win(int a) {
	return (bob[a]) % 3 + 1;
}

int what_same(int a, int b, int out_a) {
	int play_a, play_b, out_b;
	if (0 == out_a) play_a = get_tie(a);
	else play_a = get_win(a);
	play_b = get_tie(b);
	if (play_b == play_a) return 0;
	play_b = get_win(b);
	if (play_b == play_a) return 1;
	return 3;
}

void make_adj() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &bob[i]);
	}
	adj.clear();
	adj.assign(2 * n, vector<int>());
	int a, b, c, d;
	for (int i = 0; i < m; ++i) {
		scanf("%d %d %d", &a, &b, &c);
		--a;
		--b;
		if (a == b) {
			if (1 == c) {
				adj[2 * a].push_back(2 * a + 1);
				adj[2 * a + 1].push_back(2 * a);
			}
		}
		else {
			if (0 == c) {
				if (3 == (d = what_same(a, b, 0))) {
					adj[2 * a].push_back(2 * a + 1);
				} else {
					adj[2 * a].push_back(2 * b + d);
				}
				if (3 == (d = what_same(a, b, 1))) {
					adj[2 * a + 1].push_back(2 * a);
				} else {
					adj[2 * a + 1].push_back(2 * b + d);
				}
				if (3 == (d = what_same(b, a, 0))) {
					adj[2 * b].push_back(2 * b + 1);
				} else {
					adj[2 * b].push_back(2 * a + d);
				}
				if (3 == (d = what_same(b, a, 1))) {
					adj[2 * b + 1].push_back(2 * b);
				} else {
					adj[2 * b + 1].push_back(2 * a + d);
				}
			} else {
				if (3 == (d = what_same(a, b, 0))) {
				} else {
					adj[2 * a].push_back(2 * b + d ^ 1);
				}
				if (3 == (d = what_same(a, b, 1))) {
				} else {
					adj[2 * a + 1].push_back(2 * b + d ^ 1);
				}
				if (3 == (d = what_same(b, a, 0))) {
				} else {
					adj[2 * b].push_back(2 * a + d ^ 1);
				}
				if (3 == (d = what_same(b, a, 1))) {
				} else {
					adj[2 * b + 1].push_back(2 * a + d ^ 1);
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
	//freopen("input.dat", "r", stdin);

	scanf("%d", &t);
	cas = 0;
	while (t--) {
		++cas;
		make_adj();
		tarjan_solve();
		if (tarjan_solvable()) {
			printf("Case #%d: yes\n", cas);
		} else {
			printf("Case #%d: no\n", cas);
		}
	}
	return 0;
}

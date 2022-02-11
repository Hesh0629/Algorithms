// Template for PS
// Created by HeSH on 2022.01.26
// 앞으로 flow는 구조체로좀 
#include <bits/stdc++.h>
#define endl '\n'
#define n_ 10101
#define INF 9876543210
using namespace std;
typedef int ll;
ll n, k, tc = 1, cache[10101], vis[10101], cnt;
deque<ll>ans;
string s;
struct edge {
	int to, cap, flow;
	edge* rev;

	edge(int to, int cap) :to(to), cap(cap), flow(0) {};

	int rest() {
		return cap - flow;
	}
	void push(int f) {
		flow += f;
		rev->flow -= f;
	}
};
vector<edge*>v[n_];
void dfs(ll cur) {
	if (cnt == k)return;
	if (vis[cur] && cur != 1 + n && cur != 2)return;
	vis[cur] = 1;
	if (cur <= n)ans.push_back(cur);
	if (cur == 2) {
		for (auto i : ans)cout << i << " ";
		cout << endl;
		cnt++;
	}
	else {
		for (auto i : v[cur]) {
			if (i->flow > 0) {
				dfs(i->to);
			}
		}
	}
	if (cur <= n)ans.pop_back();
}
void add_edge(int from, int to, int c) {
	edge* e1 = new edge(to, c), * e2 = new edge(from, 0);
	e1->rev = e2;
	e2->rev = e1;
	v[from].push_back(e1);
	v[to].push_back(e2);
}
void Edmond_Karp(int source, int sink) {
	int max_flow = 0;
	while (1) {
		queue<int>q;
		memset(cache, -1, sizeof(cache));
		edge* path[n_];
		cache[source] = source;
		q.push(source);
		while (q.size()) {
			int cur = q.front();
			q.pop();
			for (auto e : v[cur]) {
				auto nxt = e->to;
				if (cache[nxt] == -1 && e->rest() > 0) {
					cache[nxt] = cur;
					path[nxt] = e;
					q.push(nxt);
					if (nxt == sink)break;
				}
			}
		}
		if (cache[sink] == -1)break;
		int min_cap = 1e9;
		for (int i = sink; i != source; i = cache[i])min_cap = min(min_cap, path[i]->rest());
		max_flow += min_cap;
		for (int i = sink; i != source; i = cache[i])path[i]->push(min_cap);
	}
	if (max_flow < k)cout << "Impossible" << endl;
	else {
		ans.push_back(1);
		dfs(1 + n);
		ans.pop_back();
	}
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	while (1) {
		memset(vis, 0, sizeof(vis));
		for (int i = 0; i < n_; i++)v[i].clear();
		ans.clear();
		cnt = 0;
		cin >> k >> n;
		if (n == 0 && k == 0)break;
		getline(cin, s);
		for (int i = 1; i <= n; i++) {
			getline(cin, s);
			string asdf;
			for (auto it : s) {
				if ('0' <= it && it <= '9')asdf.push_back(it);
				else {
					ll cur = stoi(asdf);
					asdf.clear();
					add_edge(i + n, cur, 1);
				}
			}
			if (!asdf.empty()) {
				ll cur = stoi(asdf);
				asdf.clear();
				add_edge(i + n, cur, 1);
			}
		}
		for (ll i = 1; i <= n; i++) {
			add_edge(i, i + n, 1);
		}
		cout << "Case " << tc++ << ":" << endl;
		Edmond_Karp(1 + n, 2);
		cout << endl;
	}
}

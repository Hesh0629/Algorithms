// Template for PS
// Created by HeSH on 2022.01.26
#include <bits/stdc++.h>
#define endl '\n'
#define INF 3*10e12
using namespace std;
typedef int ll;
ll n, k, tc = 1, cache[10101];
ll flow[10101][10101], cap[10101][10101];
vector<ll>adj[10101];
string s;
void edmond_karp(ll source, ll sink) {
	ll max_flow = 0;
	vector<vector<ll>>ans;
	while (1) {
		queue<ll>q;
		vector<ll>curans;
		q.push(source);
		memset(cache, -1, sizeof(cache));
		cache[source] = 0;
		while (!q.empty()) {
			ll cur = q.front(); q.pop();
			for (auto i : adj[cur]) {
				if (cache[i] == -1 && (cap[cur][i] - flow[cur][i]) > 0) {
					cache[i] = cur;
					q.push(i);
					if (i == sink)break;
				}
			}
		}
		if (cache[sink] == -1)break;
		ll min_cap = 1e9;
		for (ll i = sink; i != source; i = cache[i]) {
			ll bef = cache[i];
			min_cap = min(min_cap, cap[bef][i] - flow[bef][i]);
		}
		max_flow += min_cap;
		for (ll i = sink; i != source; i = cache[i]) {
			if (i <= n)curans.push_back(i);
			ll bef = cache[i];
			flow[bef][i] += min_cap;
			flow[i][bef] -= min_cap;
		}
		curans.push_back(1);
		reverse(curans.begin(), curans.end());
		ans.push_back(curans);
	}
	cout << "max flow is " << max_flow << endl;
	if (max_flow < k)cout << "Impossible" << endl;
	else {
		ll cnt = 0;
		for (auto v : ans) {
			cnt++;
			for (auto i : v)cout << i << " ";
			cout << endl;
			if (cnt == k)break;
		}
	}
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	while (1) {
		cin >> k >> n;
		if (n == 0 && k == 0)break;
		for (int i = 0; i < 10101; i++) adj[i].clear();
		getline(cin, s);
		for (int i = 1; i <= n; i++) {
			getline(cin, s);
			string asdf;
			for (auto it : s) {
				if ('0' <= it && it <= '9')asdf.push_back(it);
				else {
					ll cur = stoi(asdf);
					asdf.clear();
					adj[i + n].push_back(cur);
					adj[cur].push_back(i+n);
					cap[i + n][cur] = 1;
					cap[cur][i + n] = 1;
				}
			}
			if (!asdf.empty()) {
				ll cur = stoi(asdf);
				asdf.clear();
				adj[i + n].push_back(cur);
				adj[cur].push_back(i + n);
				cap[i + n][cur] = 1;
				cap[cur][i + n] = 1;
			}
		}
		cout << "Case " << tc++ << ":" << endl;
		for (ll i = 1; i <= n; i++) {
			adj[i].push_back(i + n);
			adj[i + n].push_back(i);
			if (i <= 2) continue;
			cap[i][i + n] = 1;
			cap[i + n][i] = 1;
		}
		edmond_karp(1 + n, 2);
		cout << endl;
	}
}

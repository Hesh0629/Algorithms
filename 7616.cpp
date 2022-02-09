// Template for PS
// Created by HeSH on 2022.01.26
#include <bits/stdc++.h>
#define endl '\n'
#define INF 3*10e12
using namespace std;
typedef int ll;
ll n, k, tc = 1, cache[10101];
bool flow[10101][10101], cap[10101][10101];
set<ll>adj[10101];
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
				if (cache[i] == -1 && cap[cur][i]&&!flow[cur][i]) {
					cache[i] = cur;
					q.push(i);
					if (i == sink)break;
				}
			}
		}
		if (cache[sink] == -1)break;
		max_flow += 1;
		for (ll i = sink; i != source; i = cache[i]) {
			if (i <= n)curans.push_back(i);
			ll bef = cache[i];
			flow[bef][i] = true;
			flow[i][bef] = false;
		}
		curans.push_back(1);
		reverse(curans.begin(), curans.end());
		ans.push_back(curans);
	}
	if (max_flow <k)cout << "Impossible" << endl;
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
		for (int i = 0; i < 5050; i++) adj[i].clear();
		memset(cache, 0, sizeof(cache));
		getline(cin, s);
		for (int i = 1; i <= n; i++) {
			getline(cin, s);
			string asdf;
			for (auto it : s) {
				if ('0' <= it && it <= '9')asdf.push_back(it);
				else {
					ll cur = stoi(asdf);
					asdf.clear();
					adj[i+n].insert(cur);
					adj[cur+n].insert(i);
					cap[i+n][cur] = true;
					cap[cur+n][i] = true;
				}
			}
			if (!asdf.empty()) {
				ll cur = stoi(asdf);
				asdf.clear();
				adj[i + n].insert(cur);
				adj[cur + n].insert(i);
				cap[i + n][cur] = true;
				cap[cur + n][i] = true;
			}
		}
		cout << "Case " << tc++ << ":" << endl;
		for (ll i = 1; i <= n; i++){
			adj[i].insert(i + n);
			adj[i + n].insert(i);
			if (i <= 2) continue;
			cap[i][i + n] = true;
			cap[i + n][i] = true;
		}
		edmond_karp(1 + n, 2);
		cout << endl;
	}
}

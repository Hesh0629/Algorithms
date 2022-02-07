// cap에는 간선의 가능한 용량, flow는 현재 흐르는 유량, cache는 이전 정점 저장
// forward edge에는 현재 capacity, backward edge에는 현재 flow가 저장된다.

ll flow[410][410], cap[410][410], cache[410];
ll n, m, ans, sr, sk, num, house;
vector<ll>adj[410];
void add_edge(ll from, ll to, ll c) {
	adj[from].push_back(to);
	adj[to].push_back(from);
	cap[from][to] = c;
}
ll edmond_karp(ll source, ll sink) {
	ll max_flow = 0;
	while (1) {
		queue<ll>q;
		q.push(source);
		memset(cache, -1, sizeof(cache));
		cache[source] = 0;
		while (!q.empty()) {
			ll cur = q.front();
			q.pop();
			for (auto i : adj[cur]) {
				if (cache[i] == -1 && (cap[cur][i]-flow[cur][i] > 0)) {
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
		for (int i = sink; i != source; i = cache[i]) {
			ll bef = cache[i];
			flow[bef][i] += min_cap;
			flow[i][bef] -= min_cap;
		}
	}
	return max_flow;
}

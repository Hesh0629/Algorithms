// d[]: 트리 정점의 레벨저장, par[x][i] = x의 2^i번째 조상 저장
void dfs(ll cur, ll pre) {
	d[cur] = d[pre] + 1;
	par[cur][0] = pre;
	for (auto i : adj[cur]) {
		if (i == pre)continue;
		par[i][0] = cur;
		dfs(i, cur);
	}
}

ll query(ll x, ll y) {
	if (d[x] < d[y])d(x, y);
	for (int i = 20; i >= 0; i--) {
		if (d[x] - d[y] >= (1 << i)) x = par[x][i];
	}
	if (x == y)return x;
	for (int i = 20; i >= 0; i--) {
		if (par[x][i] != par[y][i]) {
			x = par[x][i];
			y = par[y][i];
		}
	}
	return par[x][0];
}

// lev[]: 트리 정점의 레벨저장, lca[x][i] = x의 2^i번째 조상 저장
void dfs(ll cur, ll pre) {
	lev[cur] = lev[pre] + 1;
	lca[cur][0] = pre;
	for (auto i : adj[cur]) {
		if (i == pre)continue;
		lca[i][0] = cur;
		dfs(i, cur);
	}
}

ll query(ll x, ll y) {
	if (lev[x] < lev[y])swap(x, y);
	for (int i = 20; i >= 0; i--) {
		if (lev[x] - lev[y] >= (1 << i)) x = lca[x][i];
	}
	if (x == y)return x;
	for (int i = 20; i >= 0; i--) {
		if (lca[x][i] != lca[y][i]) {
			x = lca[x][i];
			y = lca[y][i];
		}
	}
	return lca[x][0];
}

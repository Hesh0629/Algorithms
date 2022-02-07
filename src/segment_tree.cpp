ll init(ll N, ll cx, ll cy) {
	if (cx == cy) return segtree[N] = v[cx];
	ll mid = (cx + cy) / 2;
	init(N * 2, cx, mid);
	init(N * 2 + 1, mid + 1, cy);
	return segtree[N] = segtree[N * 2] * segtree[N * 2 + 1];
}
ll query(ll N, ll cx, ll cy, ll tx, ll ty) {
	if (cy < tx || ty < cx)return 1;
	if (tx <= cx && cy <= ty)return segtree[N];
	ll mid = (cx + cy) / 2;
	return query(N * 2, cx, mid, tx, ty) * query(N * 2 + 1, mid + 1, cy, tx, ty);
}
void update(ll N, ll cx, ll cy, ll idx, ll val) {
	if (idx < cx || cy < idx)return;
	if (cx == cy && idx == cx) {
		segtree[N] = val;
		return;
	}
	ll mid = (cx + cy) / 2;
	update(N * 2, cx, mid, idx, val);
	update(N * 2 + 1, mid + 1, cy, idx, val);
	segtree[N] = segtree[N * 2] * segtree[N * 2 + 1];
}

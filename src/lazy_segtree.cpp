ll n, m, k, segtree[3030303], lazy[3030303], arr[1010101];

void init(ll N, ll cx, ll cy) {
	if (cx == cy) {
		segtree[N] = arr[cx];
		return;
	}
	ll mid = (cx + cy) / 2;
	init(N * 2, cx, mid);
	init(N * 2 + 1, mid + 1, cy);
	segtree[N] = segtree[2 * N] + segtree[2 * N + 1];
}

// 현재 update또는 query가 진행되던 노드에 lazy가 있다면 반영해주고 자식에 lazy를 넘기자
void update_lazy(ll N, ll l, ll r) {
	if (!lazy[N])return;
	segtree[N] += (r - l + 1) * lazy[N];
	if (l != r) {
		lazy[2 * N] += lazy[N];
		lazy[2 * N + 1] += lazy[N];
	}
	lazy[N] = 0;
}

// update연산 자체는 query연산과 동일하지않아도 된다.
void update(ll N, ll cx, ll cy, ll tx, ll ty, ll val) {
	update_lazy(N, cx, cy);
	if (cy < tx || ty < cx)return;
	if (tx <= cx && cy <= ty) {
		segtree[N] += (cy - cx + 1) * (val);
		if (cx != cy) {
			lazy[2 * N] += val;
			lazy[2 * N + 1] += val;
		}
		return;
	}
	ll mid = (cx + cy) / 2;
	update(N * 2, cx, mid, tx, ty, val);
	update(N * 2 + 1, mid + 1, cy, tx, ty, val);
	segtree[N] = segtree[N * 2] + segtree[N * 2 + 1];
}

ll query(ll N, ll cx, ll cy, ll tx, ll ty) {
	update_lazy(N, cx, cy);
	if (cy < tx || ty < cx)return 0;
	if (tx <= cx && cy <= ty) return segtree[N];
	ll mid = (cx + cy) / 2;
	return query(N * 2, cx, mid, tx, ty) + query(N * 2 + 1, mid + 1, cy, tx, ty);
}

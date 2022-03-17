// Template for PS
// Created by HeSH on 2022.02.17
#include <bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>
#define endl '\n'
#define INF 1e13
#define MAX 1000000
#define mod 1000000007
using namespace std;
typedef long long int ll;
ll segtree[4040404], v[1010101];
ll tc, n, idx = 2;
ll init(ll N, ll cx, ll cy) {
	if (cx == cy) return segtree[N] = v[cx];
	ll mid = (cx + cy) / 2;
	init(N * 2, cx, mid);
	init(N * 2 + 1, mid + 1, cy);
	return segtree[N] = segtree[N * 2] + segtree[N * 2 + 1];
}
ll squery(ll N, ll cx, ll cy, ll tx, ll ty) {
	if (cy < tx || ty < cx)return 0;
	if (tx <= cx && cy <= ty)return segtree[N];
	ll mid = (cx + cy) / 2;
	return squery(N * 2, cx, mid, tx, ty) + squery(N * 2 + 1, mid + 1, cy, tx, ty);
}
ll query(ll N, ll cx, ll cy, ll val) {
	if (cx == cy && segtree[N] == val)return cx;
	ll mid = (cx + cy) / 2;
	if (segtree[2 * N] >= val)return query(2 * N, cx, mid, val);
	else return query(2 * N + 1, mid + 1, cy, val - segtree[2 * N]);
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
	segtree[N] = segtree[N * 2] + segtree[N * 2 + 1];
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	for (ll i = 1; i <= MAX; i++)v[i] = 1;
	init(1, 1, MAX);
	while (1) {
		ll s = squery(1, 1, MAX, 1, MAX);
		if (idx > s)break;
		ll start = query(1, 1, MAX, idx);
		ll del = start;
		vector<ll>temp;
		while (del <= s) {
			ll tar = query(1, 1, MAX, del);
			temp.push_back(del);
			del += start;
		}
		for (auto i : temp)update(1, 1, MAX, i, 0);
		idx++;
	}
	cin >> tc;
	while (tc--) {
		cin >> n;
		if (squery(1, 1, MAX, n, n))cout << "lucky" << endl;
		else cout << "unlucky" << endl;
	}
}

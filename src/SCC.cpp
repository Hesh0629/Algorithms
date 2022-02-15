// 코사라주 멈춰!
// 타잔 알고리즘으로 SCC를 만들고 2-SAT을 풀어보자

ll n, m, a, b, idx, SN, sn[2020], fin[2020], dfsn[2020];
vector<ll>adj[2020];
vector<vector<ll>>scc;
stack<ll>st;

ll rev(ll N) {
	if (N > n)return N - n;
	else return N + n;
}

// dfs를 돌며 순서를 매기고 stack에 push를 해준다.
// 만약 현재 위치에서 얻을 수 있는 최소 순서가 자기 자신이라면 자식에서 자신의 부모쪽으로 간 적이 없음을 의미한다.
// 노드가 저장된 stack에서 자신이 나올 때까지 pop해가면서 scc로 묶어주자

ll dfs(ll cur) {
	dfsn[cur] = ++idx;
	st.push(cur);
	ll ret = dfsn[cur];
	for (auto i : adj[cur]) {
		if (!dfsn[i])ret = min(ret, dfs(i));
		else if (!fin[i])ret = min(ret, dfsn[i]);
	}
	if (ret == dfsn[cur]) {
		vector<ll>curscc;
		while (1) {
			ll asdf = st.top();
			st.pop();
			fin[asdf] = 1;
			curscc.push_back(asdf);
			if (asdf == cur)break;
		}
		for (auto i : curscc)sn[i] = SN;
    scc.push_back(curscc);
		SN++;
	}
	return ret;
}

// 2-SAT은 인접 리스트 관계를 잘 설정해주자. 둘중 하나가 거짓이면 나머지 한쪽이 참으로 되는 쪽으로!

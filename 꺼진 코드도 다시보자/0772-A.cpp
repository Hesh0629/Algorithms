// Template for PS
// Created by HeSH on 2022.02.17
#include <bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>
#define endl '\n'
#define INF 1e13
#define MAX 101010
#define mod 1000000007
using namespace std;
typedef long long int ll;
ll tc, n, arr[202020];
pair<ll, ll>y, z;
vector<pair<ll, pair<ll, ll>>>ans;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> tc;
	while (tc--) {
		ll flag = 0;
		ans.clear();
		cin >> n;
		for (int i = 1; i <= n; i++)
			cin >> arr[i];
		if (arr[n - 1] > arr[n]) { // arr[n-1], arr[n]의 경우 조작이 불가능 하므로 이 둘이 decreasing이면 -1
			cout << -1 << endl;
			continue;
		}
		else {
			y = { arr[n - 1],n - 1 }, z = { arr[n],n }; // 처음에 가능한 y,z값. 앞으로 y는 최소,z는 최대값을 가리키게 된다.
			for (int i = n - 2; i >= 1; i--) {
				if (arr[i] > y.first - z.first&&arr[i] > arr[i + 1]) { // 만약 지금보고 있는 값이 y-z를 통해 만들 수 있는 값(최소값과 동일)보다 크다면 갱신
					arr[i] = y.first - z.first;
					ans.push_back({ i,{ y.second,z.second } });
				}
				if (arr[i] - z.first >= -1e18 && arr[i] < y.first) // 만일 지금보고 있는 값이 y보다 작다면 y값을 갱신 (단 차가 -1e18보다 커야함)
					y = { arr[i],i };
				if (arr[i] > arr[i + 1]) { // 이랫는데도 arr[i]>arr[i+1]이면 -1
					flag = 1;
					break;
				}
			}
		}
		if (flag)cout << -1 << endl;
		else {
			cout << ans.size() << endl;
			for (auto i : ans)cout << i.first << " " << i.second.first << " " << i.second.second << endl;
		}
	}
}

// day: 11/06/2025
// 3607. Power Grid Maintenance
// note: easy dsu problem
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
	vector<int> par;
	vector<int> sz;
	vector<bool> on;
	int find(int x){
		if(x == par[x]){
			return x;
		} 
		return find(par[x]);
	}
	void merge(int a, int b){
		a = find(a);
		b = find(b);
		if(a != b){
			if(sz[a] < sz[b]){
				swap(a, b);
			}
			par[b] = a;
			sz[a] += sz[b];
		}
	}
	vector<int> processQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& q) {
		par.resize(n);
		for(int i = 0; i < n; i++){
			par[i] = i;
		}
		sz.resize(n, 1);
		on.resize(n, true);
		for(auto v : edges){
			int x = v[0], y = v[1];
			merge(x - 1, y - 1);
		}
		map<int, set<int>> me;
		for(int i = 0; i < n; i++){
			int x = find(i);
			me[x].insert(i);
		}
		vector<int> ans;
		for(auto qq : q){
			int c = qq[0];
			int x = qq[1] - 1;
			if(c == 2){
				on[x] = false;
				int pp = find(x);
				auto it = me[pp].find(x);
				if(it != me[pp].end()){
					me[pp].erase(it);
				}
			} else {
				if(on[x]){
					ans.push_back(x + 1);
				} else {
					int pp = find(x);
					if(me[pp].size() == 0){
						ans.push_back(-1);
					} else {
						ans.push_back(*me[pp].begin() + 1);
					}
				}
			}
		}
		return ans;
	}
	void solve(){
		int n, m, q;
		cin >> n >> m >> q;
		vector<vector<int>> edges;
		for(int i = 0; i < m; i++){
			int u, v;
			cin >> u >> v;
			vector<int> tt = {u, v};
			edges.push_back(tt);
		}
		vector<vector<int>> qq;
		while(q--){
			vector<int> tt(2);
			cin >> tt[0] >> tt[1];
			qq.push_back(tt);
		}
		vector<int> ans = processQueries(n, edges, qq);
		for(int x : ans){
			cout << x << ' ';
		}
	}
};
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	Solution x;
	x.solve();
}

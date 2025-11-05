// link: https://leetcode.com/problems/find-x-sum-of-all-k-long-subarrays-ii/description/
#include <bits/stdc++.h>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false); cin.tie(nullptr);
  int n, k, x;
  cin >> n >> k >> x;
  vector<int> a(n);
  for(int i = 0; i < n; i++){
    cin >> a[i];
  }
  set<pair<int,int>> fi, se;
  map<int,int> mp, mc;
  vector<pair<int,int>> tt;
  for(int i = 0; i < k; i++){
    mp[a[i]]++;
  }
  for(int i = k; i < n; i++){
    if(mp.find(a[i]) == mp.end()){
      mp[a[i]] = 0;
    }
  }
  for(auto [x, y] : mp){
    tt.emplace_back(y, x);
  }
  sort(tt.begin(), tt.end());
  reverse(tt.begin(), tt.end());
  long long sum = 0;
  for(int i = 0; i < (int)tt.size(); i++){
    if(i < x){
      mc[tt[i].second] = 0;
      sum += 1ll * tt[i].first * tt[i].second;
      fi.insert({-tt[i].first, -tt[i].second});
    } else {
      mc[tt[i].second] = 1;
      se.insert({-tt[i].first, -tt[i].second});
    }
  }
  cout << sum << endl;
  if((int)mp.size() <= x){
    for(int i = k; i < n; i++){
      sum += 1ll * a[i];
      sum -= 1ll * a[i - k];
      cout << sum << endl;
    }
    return 0;
  }
  for(int i = k; i < n; i++){
    int rem = a[i - k];
    if(mc[rem] == 1){
      int xx = mp[rem];
      se.erase(se.find({-xx, -rem}));
      xx--;
      mp[rem]--;
      se.insert({-xx, -rem});
    } else {
      int xx = mp[rem];
      auto it = fi.find({-xx, -rem});
      fi.erase(it);
      sum -= 1ll * xx * rem; 
      xx--;
      mp[rem]--;
      auto cc = se.begin();
      int tx = cc -> first; tx = -tx;
      int ty = cc -> second; ty = -ty;
      if(tx > xx || (tx == xx && ty > rem)){
        se.erase(cc); sum += 1ll * tx * ty;
        fi.insert({-tx, -ty});
        se.insert({-xx, -rem});
        mc[rem] = 1;
        mc[ty] = 0;
      } else {
        fi.insert({-xx, -rem});
        sum += 1ll * xx * rem;
      }
    }
    int add = a[i];
    if(mc[add] == 0){
      int xx = mp[add];
      sum = sum + add;
      fi.erase(fi.find({-xx, -add}));
      xx++; mp[add]++;
      fi.insert({-xx, -add});
    } else {
      int xx = mp[add];
      se.erase(se.find({-xx, -add}));
      xx++; mp[add]++;
      auto cc = prev(fi.end());
      int tx = cc -> first; tx = -tx;
      int ty = cc -> second; ty = -ty;
      if(xx > tx || (xx == tx && add > ty)){
        fi.erase(cc);
        sum -= 1ll * tx * ty;
        se.insert({-tx, -ty});
        fi.insert({-xx, -add});
        sum += 1ll * xx * add;
        mc[ty] = 1;
        mc[add] = 0;
      } else {
        se.insert({-xx, -add});
      }
    }
    cout << sum << endl;
  }
}

#include <bits/stdc++.h>

using namespace std;
#define int long long

struct SegTree{
	const int N = 4e5+5; 		//adjust according to the problem
	vector<int> t;;
	void build(vector<int>& a){
		int n = a.size();
		t.resize(2*n, 0);
		for(int i = 0; i < n; i++){
			t[n+i] = a[i];
		}
		for(int i = n - 1; i > 0; i--) t[i] = t[i<<1] + t[i<<1|1];
		// equivalent to t[i] = t[2*i] + t[2*i+1]
		// reason is: i << j = i * (2^j) . in this case i = i and j = 1 so it becomes i * 2^1 = i * 2
		// | is mathematically equivalent to +
	}

	void update(int pos, int value, int n){
		// we will have to build it from the back starting from pos += n
		for(t[pos += n] = value; pos > 1; pos >>= 1) t[pos>>1] = t[pos] + t[pos^1]; 
	}

	//query function takes [l, r) such that l is inclusive and r is exclusive 
	//so for inputs, do l-- only

	int query(int l, int r, int n){
		// in case you can't understand, just draw a segment tree and simulate the query operation, it will become clear.
		// blog at: https://codeforces.com/blog/entry/18051
		int res = 0;
		for(l += n, r += n; l < r; l >>= 1, r >>= 1){
			if(l&1) res += t[l++];
			if(r&1) res += t[--r];
		}
		return res;
	}

	void debug(int n){
		for(int i = 0; i <= 2*n; i++) cout << t[i] << " ";
		cout << "\n";
	}
};

signed main(){
	int n;
	cin >> n;
	vector<int> a(n);
	for(int i = 0; i < n; i++){
		cin >> a[i];
	}
	SegTree segtree;
	segtree.build(a);
}

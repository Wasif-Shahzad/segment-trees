#include <bits/stdc++.h>

using namespace std;
#define int int64_t

/*
NO_OPERATIONS = some neutral value for the update operation
we have to only merge and operate as per our requirements
*/
struct segtree{
    const int NO_OPERATIONS = 0, oo = (1ll << 62) - 1;
    int size;
    vector<int> tree, lazy;

    void init(int n){
        size = 1;
        while(size < n) size *= 2;
        tree.resize(2 * size, oo);
        lazy.resize(2 * size, 0);
    }

    void merge(int parent, int c1, int c2){
        tree[parent] = min(tree[c1], tree[c2]);
    }

    void build(vector<int>& a, int x, int lx, int rx){
        if(rx - lx == 1){
            if(lx < (int)a.size()){
                tree[x] = a[lx];
            }
            return;
        }
        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        merge(x, 2 * x + 1, 2 * x + 2);
    }

    void build(vector<int>& a){
        build(a, 0, 0, size);
    }

    void update(int i, int v, int x, int lx, int rx){
        push(x, lx, rx);
        if(rx - lx == 1){
            tree[x] = v;
            return;
        }
        int m = (lx + rx) / 2;
        if(i < m) update(i, v, 2 * x + 1, lx, m);
        else update(i, v, 2 * x + 2, m, rx);
        merge(x, 2 * x + 1, 2 * x + 2);
    }

    void update(int i, int v){
        update(i, v, 0, 0, size);
    }

    int query(int l, int r, int x, int lx, int rx){
        push(x, lx, rx);
        if(lx >= r || rx <= l) return oo;
        if(lx >= l && rx <= r) return tree[x];
        int m = (lx + rx) / 2;
        int s1 = query(l, r, 2 * x + 1, lx, m);
        int s2 = query(l, r, 2 * x + 2, m, rx);
        return min(s1, s2);
    }

    int query(int l, int r){
        return query(l, r, 0, 0, size);
    }

    int operate(int a, int b){
        if(b == NO_OPERATIONS) return a;
        return a + b;
    }

    void apply(int parent, int child){
        tree[child] = operate(tree[child], lazy[parent]);
        lazy[child] = operate(lazy[child], lazy[parent]);
    }

    void push(int x, int lx, int rx){
        if(rx - lx == 1) return;
        apply(x, 2 * x + 1);
        apply(x, 2 * x + 2);
        lazy[x] = NO_OPERATIONS;
    }

    void update(int l, int r, int v, int x, int lx, int rx){
        push(x, lx, rx);
        if(lx >= r || rx <= l) return;
        if(lx >= l && rx <= r) {
            tree[x] = operate(tree[x], v);
            lazy[x] = operate(lazy[x], v);
            return;
        }
        int m = (lx + rx) / 2;
        update(l, r, v, 2 * x + 1, lx, m);
        update(l, r, v, 2 * x + 2, m, rx);
        merge(x, 2 * x + 1, 2 * x + 2);
    }        

    void update(int l, int r, int v){
        update(l, r, v, 0, 0, size);
    }

    int query(int i, int x, int lx, int rx){
        push(x, lx, rx);
        if(rx - lx == 1){
            return tree[x];
        }
        int res = 0, m = (lx + rx) / 2;
        if(i < m){
            res = query(i, 2 * x + 1, lx, m);
        }
        else{
            res = query(i, 2 * x + 2, m, rx);
        }
        return res;
    }

    int query(int i){
        return query(i, 0, 0, size);
    }
};

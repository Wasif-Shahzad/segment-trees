#include <bits/stdc++.h>

using namespace std;
#define int int64_t

/*
initialization goes like
segtree<int, decltype(merge function), decltype(operation of lazy prop)>
we have to pass
NO_OPERATIONS, NEUTRAL, INIT_VALUE, merge function, operator function in order
*/
template <typename T, typename F1, typename F2>
struct segtree {
    T NO_OPERATIONS, NEUTRAL, INIT_VALUE;
    F1 merge_fn; 
    F2 opr_fn;
    int size;
    vector<T> tree, lazy;

    segtree(T no_opr, T neutral, T init_, F1 mrg, F2 opr)
        : NO_OPERATIONS(no_opr), NEUTRAL(neutral), INIT_VALUE(init_),
          merge_fn(mrg), opr_fn(opr) {}
    
    void init(int n) {
        size = 1;
        while(size < n) size *= 2;
        tree.resize(2 * size, INIT_VALUE);
        lazy.resize(2 * size, NO_OPERATIONS);
    }

    void merge(int parent, int c1, int c2) {
        tree[parent] = merge_fn(tree[c1], tree[c2]);
    }

    void build(vector<T>& a, int x, int lx, int rx) {
        if(rx - lx == 1) {
            if(lx < (int)a.size()) {
                tree[x] = a[lx];
            }
            return;
        }
        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        merge(x, 2 * x + 1, 2 * x + 2);
    }

    void build(vector<T>& a) {
        build(a, 0, 0, size);
    }

    T operate(T a, T b, int len) {
        return opr_fn(a, b, len);
    }

    void apply(int parent, int child, int l, int r) {
        tree[child] = operate(tree[child], lazy[parent], r - l);
        lazy[child] = operate(lazy[child], lazy[parent], 1);
    }

    void push(int x, int lx, int rx) {
        if(lazy[x] != NO_OPERATIONS) {
            if(rx - lx > 1) {
                int m = (lx + rx) / 2;
                apply(x, 2 * x + 1, lx, m);
                apply(x, 2 * x + 2, m, rx);
            }
            lazy[x] = NO_OPERATIONS;
        }
    }

    void update(int i, T v, int x, int lx, int rx) {
        push(x, lx, rx);
        if(rx - lx == 1) {
            tree[x] = v;
            return;
        }
        int m = (lx + rx) / 2;
        if(i < m) update(i, v, 2 * x + 1, lx, m);
        else update(i, v, 2 * x + 2, m, rx);
        merge(x, 2 * x + 1, 2 * x + 2);
    }

    void update(int i, T v) {
        update(i, v, 0, 0, size);
    }

    void update(int l, int r, T v, int x, int lx, int rx) {
        push(x, lx, rx);
        if(lx >= r || rx <= l) return;
        if(lx >= l && rx <= r) {
            tree[x] = operate(tree[x], v, rx - lx);
            lazy[x] = operate(lazy[x], v, 1);
            return;
        }
        int m = (lx + rx) / 2;
        update(l, r, v, 2 * x + 1, lx, m);
        update(l, r, v, 2 * x + 2, m, rx);
        merge(x, 2 * x + 1, 2 * x + 2);
    }

    void update(int l, int r, T v) {
        update(l, r, v, 0, 0, size);
    }

    T query(int l, int r, int x, int lx, int rx) {
        push(x, lx, rx);
        if(lx >= r || rx <= l) return NEUTRAL;
        if(lx >= l && rx <= r) return tree[x];
        int m = (lx + rx) / 2;
        T s1 = query(l, r, 2 * x + 1, lx, m);
        T s2 = query(l, r, 2 * x + 2, m, rx);
        return merge_fn(s1, s2);
    }

    T query(int l, int r) {
        return query(l, r, 0, 0, size);
    }

    T query(int i, int x, int lx, int rx) {
        push(x, lx, rx);
        if(rx - lx == 1) {
            return tree[x];
        }
        int m = (lx + rx) / 2;
        if(i < m) {
            return query(i, 2 * x + 1, lx, m);
        } else {
            return query(i, 2 * x + 2, m, rx);
        }
    }

    T query(int i) {
        return query(i, 0, 0, size);
    }
};

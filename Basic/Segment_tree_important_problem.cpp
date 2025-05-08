#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 9;
const int mini = -2e9; // Using a more negative value

struct Node {
    long long sum;       // Total sum of the segment
    long long max_sum;   // Maximum subarray sum within the segment
    long long prefix;    // Maximum prefix sum
    long long suffix;    // Maximum suffix sum
};

int a[N];
Node t[4 * N];

Node merge(Node left, Node right) {
    Node result;
    
    // Total sum of the combined segment
    result.sum = left.sum + right.sum;
    
    // Maximum prefix sum can be either the left prefix or left sum + right prefix
    result.prefix = max(left.prefix, left.sum + right.prefix);
    
    // Maximum suffix sum can be either the right suffix or right sum + left suffix
    result.suffix = max(right.suffix, right.sum + left.suffix);
    
    // Maximum subarray sum can be:
    // 1. Maximum subarray sum in the left segment
    // 2. Maximum subarray sum in the right segment
    // 3. Left suffix + Right prefix (crossing the boundary)
    result.max_sum = max({left.max_sum, right.max_sum, left.suffix + right.prefix});
    
    return result;
}

void build(int n, int b, int e) {
    if (b == e) {
        t[n].sum = a[b];
        t[n].max_sum = a[b];
        t[n].prefix = a[b];
        t[n].suffix = a[b];
        return;
    }
    
    int mid = (b + e) >> 1;
    build(n << 1, b, mid);
    build((n << 1) + 1, mid + 1, e);
    
    t[n] = merge(t[n << 1], t[(n << 1) + 1]);
}

void update(int n, int b, int e, int idx, int val) {
    if (b == e) {
        a[idx] = val;
        t[n].sum = val;
        t[n].max_sum = val;
        t[n].prefix = val;
        t[n].suffix = val;
        return;
    }
    
    int mid = (b + e) >> 1;
    if (idx <= mid) {
        update(n << 1, b, mid, idx, val);
    } else {
        update((n << 1) + 1, mid + 1, e, idx, val);
    }
    
    t[n] = merge(t[n << 1], t[(n << 1) + 1]);
}

Node query(int n, int b, int e, int i, int j) {
    if (i > e || b > j) {
        // Return identity element
        return {0, mini, mini, mini};
    }
    
    if (i <= b && e <= j) {
        return t[n];
    }
    
    int mid = (b + e) >> 1;
    Node left = query(n << 1, b, mid, i, j);
    Node right = query((n << 1) + 1, mid + 1, e, i, j);
    
    return merge(left, right);
}

int32_t main() {
    int n, q;
    cin >> n;
    
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    build(1, 1, n);
    
    cin >> q;
    while (q--) {
        int op;
        cin >> op;
        
        if (op == 0) {
            int idx, val;
            cin >> idx >> val;
            update(1, 1, n, idx, val);
        } else {
            int l, r;
            cin >> l >> r;
            Node result = query(1, 1, n, l, r);
            cout << result.max_sum << '\n';
        }
    }
    
    return 0;
}
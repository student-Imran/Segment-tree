#include<bits/stdc++.h>
using namespace std;
const int N = 5e5 + 9;
int a[N];
struct ST {
  #define lc (n << 1)
  #define rc ((n << 1) + 1)
  long long t[4 * N], lazy[4 * N];
  ST() {
    memset(t, 0, sizeof t);
    memset(lazy, 0, sizeof lazy);
  }
  inline void push(int n, int b, int e) { 
    if (lazy[n] == 0) return;
    t[n] =t[n]+1LL*lazy[n] * (e - b + 1);
    if (b != e) {
      lazy[lc] +=  lazy[n];
      lazy[rc] += lazy[n];
    }
    lazy[n] = 0;
  }
  inline long long combine(long long a,long long b) {
    return a+b;
  }
  inline void pull(int n) { 
    t[n] = t[lc] + t[rc];
  }
  void build(int n, int b, int e) {
    lazy[n] = 0; 
    if (b == e) {
      t[n] = a[b];
      return;
    }
    int mid = (b + e) >> 1;
    build(lc, b, mid);
    build(rc, mid + 1, e);
    pull(n);
  }
  void upd(int n, int b, int e, int i, int j, long long v) {
    push(n, b, e);
    if (j < b || e < i) return;
    if (i <= b && e <= j) {
      lazy[n] = v; 
      push(n, b, e);
      return;
    }
    int mid = (b + e) >> 1;
    upd(lc, b, mid, i, j, v);
    upd(rc, mid + 1, e, i, j, v);
    pull(n);
  }
  long long query(int n, int b, int e, int i, int j) {
    push(n, b, e);
    if (i > e || b > j) return 0; 
    if (i <= b && e <= j) return t[n];
    int mid = (b + e) >> 1;
    return combine(query(lc, b, mid, i, j), query(rc, mid + 1, e, i, j));
  }
}t;
int32_t main() {
  int n,q;cin>>n>>q;
  for (int i = 1; i <= n; i++) {
    a[i] = 0;
  }
  t.build(1, 1, n); 
  while(q--){
    int op;cin>>op;
    if(op==1){
      int ind1,ind2,v;cin>>ind1>>ind2>>v;
      t.upd(1,1,n,ind1+1,ind2,v);
    }
    else{
      int ind;cin>>ind;
      cout<<t.query(1,1,n,ind+1,ind+1)<<'\n';
    }
  }
  
  return 0;
}
#include<bits/stdc++.h>
using namespace std;
const int N = 3e5 + 9;
const long long int m=1e14+9;
int a[N];
struct ST {
  #define lc (n << 1)
  #define rc ((n << 1) + 1)
  long long int t[4 * N], lazy[4 * N];
  ST() {
    memset(t, 0, sizeof t);
    memset(lazy, 0, sizeof lazy);
  }
  inline void push(int n, int b, int e) { 
    if (lazy[n] == 0) return;
    t[n] +=lazy[n];
    if (b != e) {
      lazy[lc] +=lazy[n];
      lazy[rc] +=lazy[n];
    }
    lazy[n] = 0;
  }
  inline long long int combine(long long a,long long b) {
    return min(a,b);
  }
  inline void pull(int n) { 
    t[n] = min(t[lc],t[rc]);
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
  long long int query(int n, int b, int e, int i, int j) {
    push(n, b, e);
    if (i > e || b > j) return m; 
    if (i <= b && e <= j) return t[n];
    int mid = (b + e) >> 1;
    return combine(query(lc, b, mid, i, j),query(rc, mid + 1, e, i, j));
  }
}t;
int32_t main() {
  int n,q;cin>>n;
  for(int i=1;i<=n;i++){
    cin>>a[i];
  }
  t.build(1, 1, n);
  cin>>q;
  cin.ignore();

  while(q--){
    string op;
    getline(cin,op);
    stringstream ss(op);
    int l,r,v;
    ss>>l>>r;
    ++l,++r;
    if(ss>>v){
      if(l<=r){
        t.upd(1,1,n,l,r,v);
      }
      else{
        t.upd(1,1,n,1,r,v);
        t.upd(1,1,n,l,n,v);
      }
      
    }
    else{
      long long int ans=m;
      if(l<=r){
        ans= t.query(1,1,n,l,r);
        cout<<ans<<'\n';
      }
      else{
        long long int ans=m;
        ans= t.query(1,1,n,1,r);
        ans=min(ans,t.query(1,1,n,l,n));
        cout<<ans<<'\n';
      }
    }
  }
  
  return 0;
}
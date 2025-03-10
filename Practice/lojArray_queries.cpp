#include<bits/stdc++.h>
using namespace std;
const int N=1e5;
int a[N+9];
int t[4*N];
void build_tree(int node,int b,int e){
    if(b==e){
        t[node]=a[b];
        return;
    }
    int l=2*node;
    int r=2*node+1;
    int mid=(b+e)/2;
    build_tree(l,b,mid);
    build_tree(r,mid+1,e);
    t[node]=min(t[l],t[r]);
}
int query(int node,int b,int e,int i,int j){
    if(j<b or i>e)return INT_MAX;
    if(b>=i and e<=j){
        return t[node];
    }
    int le=2*node;
    int ri=2*node+1;
    int mid=(b+e)/2;
    int s1=query(le,b,mid,i,j);
    int s2=query(ri,mid+1,e,i,j);
    return min(s1,s2);
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;cin>>t;
    for(int i=1;i<=t;i++){
    int n,q;cin>>n>>q;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    build_tree(1,0,n-1);
    cout<<"Case "<<i<<":"<<'\n';
    while(q--){
        int x,y;cin>>x>>y;
        cout<<query(1,0,n-1,x-1,y-1)<<'\n';

    }
   }
    
    return 0;

}


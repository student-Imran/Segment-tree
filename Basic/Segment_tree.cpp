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
    t[node]=t[l]+t[r];
}
int query(int node,int b,int e,int i,int j){
    if(j<b or i>e)return 0;
    if(b>=i and e<=j){
        return t[node];
    }
    int le=2*node;
    int ri=2*node+1;
    int mid=(b+e)/2;
    int s1=query(le,b,mid,i,j);
    int s2=query(ri,mid+1,e,i,j);
    return s1+s2;
}
void update(int node,int b,int e,int i,int val){
    if(i<b or i>e)return;
    if(b==e){
        t[node]=val;
        return;
    }
    int l=2*node;
    int r=2*node+1;
    int mid=(b+e)/2;
    update(l,b,mid,i,val);
    update(r,mid+1,e,i,val);
    t[node]=t[l]+t[r];
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    build_tree(1,0,n-1);
    cout<<query(1,0,n-1,0,1)<<'\n';
    update(1,0,n-1,2,2);
    cout<<query(1,0,n-1,0,2)<<'\n';
    return 0;

}


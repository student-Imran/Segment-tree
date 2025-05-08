#include<bits/stdc++.h>
using namespace std;
const int N=1e5;
int a[N+9];
long long int t[4*N];
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
long long int query(int node,int b,int e,int i,int j){
    if(j<b or i>e)return 0;
    if(b>=i and e<=j){
        return t[node];
    }
    int le=2*node;
    int ri=2*node+1;
    int mid=(b+e)/2;
    long long int s1=query(le,b,mid,i,j);
    long long int s2=query(ri,mid+1,e,i,j);
    return s1+s2;
}
void update(int node,int b,int e,int ind,int val){
    if(ind<b or ind>e)return;
    if(b==e){
        t[node]=val;
        return;
    }
    int l=2*node;
    int r=2*node+1;
    int mid=(b+e)/2;
    update(l,b,mid,ind,val);
    update(r,mid+1,e,ind,val);
    t[node]=t[l]+t[r];
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int q,n;cin>>n>>q;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    build_tree(1,0,n-1);
    while(q--){
        int op;cin>>op;
        if(op==1){
            int ind,val;
            cin>>ind>>val;
            update(1,0,n-1,ind,val);
        }
        else{
            int i,j;cin>>i>>j;
            cout<<query(1,0,n-1,i,j-1)<<'\n';
        }
    }

}


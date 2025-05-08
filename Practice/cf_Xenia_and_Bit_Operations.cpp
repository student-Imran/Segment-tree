#include<bits/stdc++.h>
using namespace std;
const int N=(1<<17)+9;
int a[N];
int t[4*N];
int merge(int le_seg,int ri_seg,int be,int en){
    int seg_len=(en-be+1);
    int pw=__lg(seg_len);
    if(pw%2==0){
        return (le_seg^ri_seg);
    }
    else{
        return (le_seg|ri_seg);
    }
}
void build_tree(int n,int b,int e){
    if(b==e){
        t[n]=a[b];
        return;
    }
    int l=2*n;
    int r=2*n+1;
    int mid=(b+e)/2;
    build_tree(l,b,mid);
    build_tree(r,mid+1,e);
    t[n]=merge(t[l],t[r],b,e);
}
void update(int n,int b,int e,int ind,int val){
    if(ind<b or ind>e)return;
    if(b==e){
        t[n]=val;
        return;
    }
    int l=2*n;
    int r=2*n+1;
    int mid=(b+e)/2;
    update(l,b,mid,ind,val);
    update(r,mid+1,e,ind,val);
    t[n]=merge(t[l],t[r],b,e);
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,q;cin>>n>>q;
    for(int i=0;i<(1<<n);i++){
        cin>>a[i];
    }
    build_tree(1,0,(1<<n)-1);
    while(q--){
       int ind,val;
       cin>>ind>>val;
       update(1,0,(1<<n)-1,ind-1,val);
       cout<<t[1]<<'\n';
    }
}




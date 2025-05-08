#include<bits/stdc++.h>
using namespace std;
const int N=1e5+9;
int a[N];
int t[4*N];
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
    t[n]=t[l]+t[r];
}
long long int query(int n,int b,int e,int i,int j){
    if(j<b or i>e)return 0;
    if(b>=i and e<=j){
        return t[n];
    }
    int le=2*n;
    int ri=2*n+1;
    int mid=(b+e)/2;
    return query(le,b,mid,i,j)+query(ri,mid+1,e,i,j);
}
void update(int n,int b,int e,int ind,int val){
    if(ind<b or ind>e)return;
    if(b==e){
        t[n]+=val;
        return;
    }
    int l=2*n;
    int r=2*n+1;
    int mid=(b+e)/2;
    update(l,b,mid,ind,val);
    update(r,mid+1,e,ind,val);
    t[n]=t[l]+t[r];
}
void dlt(int n,int b,int e,int ind){
    if(ind<b or ind>e)return;
    if(b==e){
        t[n]=0;
        return;
    }
    int l=2*n;
    int r=2*n+1;
    int mid=(b+e)/2;
    dlt(l,b,mid,ind);
    dlt(r,mid+1,e,ind);
    t[n]=t[l]+t[r];
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;cin>>t;
    int test=1;
    while(t--){
    cout<<"Case "<<test<<":"<<'\n';
    test++;
    int q,n;cin>>n>>q;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    build_tree(1,0,n-1);
    while(q--){
        int op;cin>>op;
        if(op==2){
            int ind,val;
            cin>>ind>>val;
            update(1,0,n-1,ind,val);
        }
        else if(op==1){
            int ith;
            cin>>ith;
            long long int x;
            x=query(1,0,n-1,ith,ith);
            dlt(1,0,n-1,ith);
            cout<<x<<'\n';
        }
        else{
            int i,j;cin>>i>>j;
            cout<<query(1,0,n-1,i,j)<<'\n';
            
        }
    }
}

}


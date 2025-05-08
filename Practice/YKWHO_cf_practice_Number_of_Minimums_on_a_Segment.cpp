#include<bits/stdc++.h>
using namespace std;
const int N=1e5;
int maxint=1e9+9;
int a[N+9];
struct node{
    int mini,cnt;
};
node t[4*N];
node merge(node le,node re){
    node ans;
    ans.mini=min(le.mini,re.mini);
    ans.cnt=0;
    if(ans.mini==le.mini){
        ans.cnt+=le.cnt;
    }
    if(ans.mini==re.mini){
        ans.cnt+=re.cnt;
    }
    return ans;
}
void build_tree(int n,int b,int e){
    if(b==e){
        t[n].mini=a[b];
        t[n].cnt=1;
        return;
    }
    int l=2*n;
    int r=2*n+1;
    int mid=(b+e)/2;
    build_tree(l,b,mid);
    build_tree(r,mid+1,e);
    t[n]=merge(t[l],t[r]);
}
node query(int n,int b,int e,int i,int j){
    if(j<b or i>e)return {maxint,1};
    if(b>=i and e<=j){
        return t[n];
    }
    int le=2*n;
    int ri=2*n+1;
    int mid=(b+e)/2;
    return merge(query(le,b,mid,i,j),query(ri,mid+1,e,i,j));
}
void update(int n,int b,int e,int ind,int val){
    if(ind<b or ind>e)return;
    if(b==e){
        t[n].mini=val;
        t[n].cnt=1;
        return;
    }
    int l=2*n;
    int r=2*n+1;
    int mid=(b+e)/2;
    update(l,b,mid,ind,val);
    update(r,mid+1,e,ind,val);
    t[n]=merge(t[l],t[r]);
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
            node ans=query(1,0,n-1,i,j-1);
            cout<<ans.mini<<" "<<ans.cnt<<'\n';
        }
    }

}


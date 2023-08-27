#include<bits/stdc++.h> 
using namespace std ; 
using ll = long long ; 

struct lazy_node { 

    ll val ; 
    int counter ; 

} ; 

const int MAX = 2e5 + 10 ; 
const int MOD = 1e9 + 7 ; 
ll seg[4 * MAX] , input[MAX] , pls = 1 ;
lazy_node lazy[4 * MAX] = {0 , 0} ;  
void build (int , int , int) ; 
void update(int , int , int , int , int) ; 
void lazy_propogate(ll , int , int , int ) ; 
ll calculate_interval(ll , int , int) ; 
ll arithmetic_sum(ll , int , int) ;
ll query(int , int , int , int , int) ;
void solve(){

    int n , k ; 
        cin >> n >> k ; 
    for (int i = 0  ; i < n ; i++)
        cin >>  input[i] ;

    build(0 , n-1  , 1) ;  
    for (int i = 0 ; i < k ; i++){
        string opr ; 
            cin >> opr ; 
            if (opr == "add") {
                int a , b; 
                    cin >> a >> b ; 
                update(a - 1 , b - 1, 0 , n - 1 , 1) ; 
                pls = 1; 
            }
            else {
                int a , b; 
                    cin >> a >> b ; 
                                        
                cout << query(a - 1, b - 1 , 0 , n - 1 , 1) << endl ; 
            }
        } 

    
    }
int main() { 

    solve() ; 
} 

void build(int l , int r, int index){

    if(l == r)
        seg[index] = input[l] ; 
    else {
    int mid = (l + r) / 2 ; 
    build(l , mid , 2 * index) ;
    build(mid + 1 , r , 2 * index + 1) ; 
    seg[index] = (seg[2 * index] + seg[2 * index + 1]) % MOD ; 
    }
}

ll query(int start , int end , int l , int r , int index){

    if(lazy[index].val != 0){
        seg[index] += calculate_interval(lazy[index].val , lazy[index].counter , r - l + 1) ; 
        if(r != l)
            lazy_propogate(lazy[index].val , lazy[index].counter, index ,  r - l + 1) ; 
        lazy[index].val = 0 ;
        lazy[index].counter = 0 ;
    }

    if(r < start || l > end) 
        return 0 ; 

    else if(start <= l && end >= r)
        return seg[index] % MOD ; 

    else {

       int mid = (l + r) / 2  ;
       ll left_sum = query(start , end , l , mid , 2 * index) ; 
       ll right_sum =  query(start , end , mid + 1  , r  , 2 * index + 1) ;

       return  (left_sum + right_sum) % MOD; 
    }
}
void update(int start , int end , int l , int r , int index){

    if(lazy[index].val != 0){
        seg[index] += calculate_interval(lazy[index].val , lazy[index].counter , r - l + 1) ;  
        if(r != l)
            lazy_propogate(lazy[index].val , lazy[index].counter , index , r - l + 1) ; 
        lazy[index].val = 0 ;
        lazy[index].counter = 0 ;  
    }

    if(r < start || l > end)
        return ; 
    else if(start <= l && end >= r) {
        seg[index] += calculate_interval(pls , 1 ,  r - l + 1) ;  
        if(r != l) 
            lazy_propogate(pls , 1 , index , r - l + 1) ;  
        pls += (r-l) + 1 ; 
        return ;
    }
    else { 

        int mid = (l + r) / 2 ; 

        update(start , end , l , mid , 2 * index) ; 
        update(start , end , mid + 1 , r , 2 * index + 1) ;

        seg[index] = (seg[2*index] + seg[2 * index + 1]) % MOD ; 

    } 

}

ll calculate_interval(ll val , int count, int interval_length) {
    return arithmetic_sum(val , interval_length , count) ; 
}


void lazy_propogate(ll val , int count ,int index ,  int interval_length){

    val %= MOD ;  
    lazy[2 * index].val += val ;  

    ll temp = 0 ; 
    if(interval_length % 2 == 0) 
        temp = val + (interval_length / 2) * count  ; 
    else 
        temp = val + (interval_length / 2 + 1) * count ;  

    lazy[2 * index + 1].val += temp ; 

    lazy[2* index].counter += count ; 
    lazy[2* index + 1].counter += count ; 

}
ll arithmetic_sum(ll first_num , int n , int d){

    return (n * (2 * first_num + (n - 1) * d) / 2) % MOD ; 

}
